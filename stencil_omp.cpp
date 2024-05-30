#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>
#include <chrono>
#include <omp.h>
using namespace std;
using namespace cv;

#define NITERS 100

#define TASK_WIDTH 100
#define TASK_HEIGHT 100

inline uchar Clamp(int n)
{
    n = n>255 ? 255 : n;
    return n<0 ? 0 : n;
}

void jabobi_task(const int width, const int height, Mat &image, Mat &tmp_image)
{
  Vec3b Source_Pixel;
  Vec3b Des_Pixel;
  int Dest_Pixel_value;
  int borne_height_up,borne_height_down;
  


 #pragma omp parallel 
 {
  //Génération des tâches

    #pragma omp single nowait
    {
      //printf("Hello from %d \n",omp_get_thread_num());
      for(int l = 0 ; l <= floor(height / TASK_HEIGHT) ; l++ ){
        //printf("Hello from %d, creating task l = %d \n",omp_get_thread_num(),l);

        //Gestion de la dernière tâche
          borne_height_up =  l == floor(height / TASK_HEIGHT)?height+1:(l+1) * TASK_HEIGHT;

          //Gestion de la première tâche
          borne_height_down = l == 0 ?1: l * TASK_HEIGHT;

        #pragma omp task shared(image,width,height,tmp_image) firstprivate(borne_height_up,borne_height_down)
        {
          //printf("Hello from %d l = %d \n",omp_get_thread_num(),l);
          

          for (int i = 1; i <  width +1; ++i){
            
            for (int j = borne_height_down; j < borne_height_up; ++j){

              Vec3b Source_Pixel1 = image.at<Vec3b>(i-1,j);
              Vec3b Source_Pixel2 = image.at<Vec3b>(i,j-1);
              Vec3b Source_Pixel3 = image.at<Vec3b>(i,j);
              Vec3b Source_Pixel4 = image.at<Vec3b>(i,j+1);
              Vec3b Source_Pixel5 = image.at<Vec3b>(i+1,j);
              
              //Calcul pour R G et B 
              for (int k = 0; k < 3; k++){
                  Dest_Pixel_value = Source_Pixel3.val[k] * 0.6 + ((Source_Pixel1.val[k]+Source_Pixel2.val[k]+Source_Pixel4.val[k]+Source_Pixel5.val[k]) * 0.1);
                  Des_Pixel[k] = Clamp(Dest_Pixel_value);
                  
              }
              tmp_image.at<Vec3b>(i,j) = Des_Pixel;

            }
          }
        }
      }
      #pragma omp taskwait
    }
    
  }
  
}

void jabobi_target(const int width, const int height, Mat &image, Mat &tmp_image)
{
  //Lancement sur un GPU
  #pragma omp target
  {
      printf("Test \n");
      Vec3b Source_Pixel;
      Vec3b Des_Pixel;
      int Dest_Pixel_value;


        for (int i = 1; i <  width +1; ++i){
          
          for (int j = 1; j < height + 1; ++j){

            Vec3b Source_Pixel1 = image.at<Vec3b>(i-1,j);
            Vec3b Source_Pixel2 = image.at<Vec3b>(i,j-1);
            Vec3b Source_Pixel3 = image.at<Vec3b>(i,j);
            Vec3b Source_Pixel4 = image.at<Vec3b>(i,j+1);
            Vec3b Source_Pixel5 = image.at<Vec3b>(i+1,j);
            
            for (int k = 0; k < 3; k++){
                Dest_Pixel_value = Source_Pixel3.val[k] * 0.6 + ((Source_Pixel1.val[k]+Source_Pixel2.val[k]+Source_Pixel4.val[k]+Source_Pixel5.val[k]) * 0.1);
                Des_Pixel[k] = Clamp(Dest_Pixel_value);
                
            }
            tmp_image.at<Vec3b>(i,j) = Des_Pixel;

        }
      }
    }
}



int main(int argc, char** argv)
{
  //Init d l'image en lecture
  CommandLineParser parser(argc, argv,
                              "{@input   |img/lena.jpg|input image}");
  parser.printMessage();

  String imageName = parser.get<String>("@input");
  string image_path = samples::findFile(imageName);
  Mat image = imread(image_path, IMREAD_COLOR);

  if(image.empty())
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



  // Stencil
  // Start measuring time
  auto start = std::chrono::high_resolution_clock::now();
  for(int i = 0; i < NITERS; ++i)
    {
    jabobi_task(ny, nx, image_w_border, tmp_image);
    jabobi_task(ny, nx, tmp_image, image_w_border);

  }



  // Stop measuring time
  auto end = std::chrono::high_resolution_clock::now();
  
  // Calculate duration
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  
  // Output the duration
  cout << "------------------------------------"<< std::endl;
  std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
  cout << "------------------------------------"<< std::endl;

  // Define the ROI coordinates to exclude the outer layer
  cv::Rect roi_rect(1, 1, image_w_border.cols - 2, image_w_border.rows - 2);

  // Extract the ROI
  cv::Mat new_image = image_w_border(roi_rect);
    
  // Write the image to a file
  bool success = cv::imwrite("output_image.jpg", new_image);
    
  if (!success) {
      std::cerr << "Failed to write image to file." << std::endl;
      return -1;
  }
    
    
    /*
    delete(image);
    delete(image_w_border);
    delete(tmp_image);
    */
  return 0;
}