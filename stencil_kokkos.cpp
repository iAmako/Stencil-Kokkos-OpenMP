z#include <stdlib.h>
#include <sys/time.h> //TODO à remplacer 

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace cv;

#define NITERS 15

// Define output file name
#define OUTPUT_FILE "stencil.pgm"

// passage de double à float

inline uchar Clamp(int n)
{
    n = n>255 ? 255 : n;
    return n<0 ? 0 : n;
}

void stencil(Mat &image,Mat &tmp_image, int nx,int ny);

double wtime(void);

int main(int argc, char** argv)
{
  CommandLineParser parser(argc, argv,
                              "{@input   |image/lena.jpg|input image}");
  parser.printMessage();

  String imageName = parser.get<String>("@input");
  string image_path = samples::findFile(imageName);
  Mat image = imread(image_path, IMREAD_COLOR);
  Mat tmp_image(image.size(),image.type());

  if(image.empty())
  {
      std::cout << "Aucune image passé, utilisation d'une image par défaut" << std::endl;
      
      // Crée une image par défaut pour des tests rapides 
      init_image(nx, ny, width, height, image, tmp_image);
  }

  nx = image.cols;
  ny = image.rows;

  int width = nx + 2;
  int height = ny + 2;

  // Stencil
  double tic = wtime(); //TODO probablement à changer 
  for(int i = 0; i < NITERS; ++i)
    {
    stencil(nx, ny, width, height, image, tmp_image);
    stencil(nx, ny, width, height, tmp_image, image);
  }
  double toc = wtime();//TODO probablement à changer 

  // Output
  printf("------------------------------------\n");//TODO passer en cout 
  printf(" runtime: %lf s\n", toc - tic);
  printf("------------------------------------\n");

  output_image(OUTPUT_FILE, nx, ny, width, height, image);
  image.delete();
  tmp_image.delete();
  return EXIT_SUCCESS;
}

void stencil(const int nx, const int ny, Mat &image, Mat &tmp_image)
{
  Vec3b Source_Pixel;
  Vec3b &Des_Pixel;
  for (int i = 1; i < nx + 1; ++i)
  {
    for (int j = 1; j < ny + 1; ++j)
    {

      /* OLD C 
        
      tmp_image[j + i * height] = image[j + i * height] * 0.6f
        + (image[j + (i - 1) * height]
        + image[j + (i + 1) * height]
        + image[j - 1 + i * height]
        + image[j + 1 + i * height]) * 0.1f;
        */

      Vec3b Source_Pixel1= mSrc.at<Vec3b>(i-1,j);
      Vec3b Source_Pixel2= mSrc.at<Vec3b>(i,j-1);
      Vec3b Source_Pixel3= mSrc.at<Vec3b>(i,j);
      Vec3b Source_Pixel4= mSrc.at<Vec3b>(i,j+1);
      Vec3b Source_Pixel5= mSrc.at<Vec3b>(i+1,j);

      Vec3b &Des_Pixel= mDst.at<Vec3b>(i,j);
      for (int i = 0; k < 3; i++)
      {
          int Dest_Pixel_value = Source_Pixel3.val[k] * 0.6 + ((Source_Pixel1.val[k]+Source_Pixel2.val[k]+Source_Pixel4.val[k]+Source_Pixel5.val[k]) * 0.1);
          Des_Pixel.val[i] = Clamp(Dest_Pixel_value);
      }


    }
  }
}

// Read image from the path, output values in other parameters 
void read_image(const char* path, 
int* nx, int* ny, int* width, int* height, Mat &image, Mat tmp_image){

}

// Init a basic checkboard image # TODO A CHANGER EN CPP
void init_image(const int nx, const int ny, const int width, const int height,
                Mat &image, Mat &tmp_image)
{
  // Zero everything
  // Bordures à zero également 
  for (int i = 0; i < width; ++i)
  {
    for (int j = 0; j < height; ++j)
    {
      image[j + i * height] = 0.0f;
      tmp_image[j + i * height] = 0.0f;
    }
  }

  const int tile_size = 64;
  // checkerboard pattern
  // possibilité de passer d'une vérification avec % 2 vers une simple opération
  for (int ib = 1; ib < nx+1; ib += tile_size) // +1 
  {
    for (int jb = 1; jb < ny+1; jb += tile_size) // +1
    {
      if ((ib + jb) % (tile_size * 2))
      {
        const int jlim = (jb + tile_size > ny) ? ny : jb + tile_size;
        const int ilim = (ib + tile_size > nx) ? nx : ib + tile_size;
        for (int i = ib; i < ilim; ++i) //
        {
          for (int j = jb; j < jlim; ++j)
          {
            image[j + i * height] = 100.0f;
          }
        }
      }
    }
  }
}

// TODO CHANGER OUTPUT EN CPP
// Routine to output the image in Netpbm grayscale binary image format
void output_image(string file_name, const int nx, const int ny,
                  const int width, const int height, Mat image)
{
  // Open output file
  FILE *fp = fopen(file_name, "w");
  if (!fp)
  {
    fprintf(stderr, "Error: Could not open %s\n", OUTPUT_FILE);
    exit(EXIT_FAILURE);
  }

  // Ouptut image header
  fprintf(fp, "P5 %d %d 255\n", nx, ny);

  // Calculate maximum value of image
  // This is used to rescale the values
  // to a range of 0-255 for output
  float maximum = 0.0f;
  for (int i = 1; i < nx+1; ++i) //+1
  {
    for (int j = 1; j < ny+1; ++j) //+1
    {
      if (image[j + i * height] > maximum)
        maximum = image[j + i * height];
    }
  }

  // Output image, converting to numbers 0-255
  for (int i = 1; i < nx+1; ++i) //+1
  {
    for (int j = 1; j < ny+1; ++j) //+1
    {
      fputc((char)(255.0f * image[j + i * height] / maximum), fp);
    }
  }

  // Close the file
  fclose(fp);
}

// Get the current time in seconds since the Epoch
double wtime(void)
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}
