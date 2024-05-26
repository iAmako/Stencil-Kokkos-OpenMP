#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <Kokkos_Core.hpp>

#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace cv;

#define NITERS 100

// Define output file name
#define OUTPUT_FILE "stencil.pgm"

inline uchar Clamp(int n)
{
    n = n > 255 ? 255 : n;
    return n < 0 ? 0 : n;
}

void stencil(const int width, const int height, Kokkos::View<int ***, Kokkos::HostSpace> &h_src_image, Kokkos::View<int ***, Kokkos::HostSpace> &h_dst_image)
{

    Kokkos::MDRangePolicy<Kokkos::Rank<2>> policy({1, 1}, {width + 1, height + 1});

    Kokkos::parallel_for("Stencil Computation", policy, KOKKOS_LAMBDA(const int i, const int j) {
        int Source_Pixel1[3], Source_Pixel2[3], Source_Pixel3[3], Source_Pixel4[3], Source_Pixel5[3];
        int Des_Pixel[3];
        int Dest_Pixel_value;

        for (int k = 0; k < 3; k++) {
            Source_Pixel1[k] = h_src_image(i - 1, j, k);
            Source_Pixel2[k] = h_src_image(i, j - 1, k);
            Source_Pixel3[k] = h_src_image(i, j, k);
            Source_Pixel4[k] = h_src_image(i, j + 1, k);
            Source_Pixel5[k] = h_src_image(i + 1, j, k);

            Dest_Pixel_value = Source_Pixel3[k] * 0.6 +
                               ((Source_Pixel1[k] + Source_Pixel2[k] + Source_Pixel4[k] + Source_Pixel5[k]) * 0.1);
            Des_Pixel[k] = Clamp(Dest_Pixel_value);
        }

        for (int k = 0; k < 3; k++) {
            h_dst_image(i, j, k) = Des_Pixel[k];
        } });
}

int main(int argc, char **argv)
{
    Kokkos::initialize(argc, argv);
    {


        CommandLineParser parser(argc, argv,
                                 "{@input   |img/lena.jpg|input image}");
        parser.printMessage();

        String imageName = parser.get<String>("@input");
        string image_path = samples::findFile(imageName);
        Mat image = imread(image_path, IMREAD_COLOR);

        if (image.empty())
        {
            std::cout << "Aucune image passé, fermeture du programme" << std::endl;

            return -1;
        }

        int nx = image.cols;
        int ny = image.rows;

        int width = nx + 2;
        int height = ny + 2;

        // Create a new image with the specified dimensions, filled with zeros
        Mat image_w_border(height, width, image.type(), cv::Scalar(0, 0, 0));

        // Define the region where the original image will be copied
        Rect roi(cv::Point(1, 1), image.size());

        // Copy the original image onto the new image, leaving a border of zeros
        image.copyTo(image_w_border(roi));

        // Create a buffer image with the specified dimensions, filled with zeros
        Mat tmp_image(height, width, image.type(), cv::Scalar(0, 0, 0));

        // Convert cv::Mat to Kokkos view
        Kokkos::View<int ***, Kokkos::HostSpace> h_src_image("h_src_image", height + 2, width + 2, 3);
        Kokkos::View<int ***, Kokkos::HostSpace> h_dst_image("h_dst_image", height + 2, width + 2, 3);

        Kokkos::View<int ***, Kokkos::CudaSpace> d_src_image("d_src_image", height + 2, width + 2, 3);
        Kokkos::View<int ***, Kokkos::CudaSpace> d_dst_image("d_dst_image", height + 2, width + 2, 3);

        for (int i = 0; i < height + 2; ++i)
        {
            for (int j = 0; j < width + 2; ++j)
            {
                Vec3b pixel = image_w_border.at<Vec3b>(i, j);
                for (int k = 0; k < 3; ++k)
                {
                    h_src_image(i, j, k) = pixel[k];
                }
            }
        }

        // Start measuring time
        auto start = std::chrono::high_resolution_clock::now();

        Kokkos::deep_copy(d_src_image, h_src_image); // first destination THEN source

        // Stencil
        for (int i = 0; i < NITERS; ++i)
        {
            stencil(ny, nx, d_src_image, d_dst_image);

            stencil(ny, nx, d_dst_image, d_src_image);
        }

        if (NITERS % 2 == 1)
        {
            std::swap(d_src_image, d_dst_image);
        }

        Kokkos::deep_copy(h_src_image, d_src_image);

        // Copy data from Kokkos view to cv::Mat
        for (int i = 1; i < height + 1; ++i)
        {
            for (int j = 1; j < width + 1; ++j)
            {
                Vec3b &pixel = image_w_border.at<Vec3b>(i, j);
                for (int k = 0; k < 3; ++k)
                {
                    pixel[k] = h_dst_image(i, j, k);
                }
            }
        }

        // Stop measuring time
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate duration
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        // Output the duration
        cout << "------------------------------------" << std::endl;
        std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
        cout << "------------------------------------" << std::endl;

        // Define the ROI coordinates to exclude the outer layer
        cv::Rect roi_rect(1, 1, image_w_border.cols - 2, image_w_border.rows - 2);

        // Extract the ROI
        cv::Mat new_image = image_w_border(roi_rect);

        // Write the image to a file
        bool success = cv::imwrite("output_image.jpg", new_image);

        if (!success)
        {
            std::cerr << "Failed to write image to file." << std::endl;
            return -1;
        }

        std::cout << "Image successfully written to output_image.jpg" << std::endl;

        /*
        delete(image);
        delete(image_w_border);
        delete(tmp_image);
        */

        Kokkos::finalize();
    }
    return 0;
}