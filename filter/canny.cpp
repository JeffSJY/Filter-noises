#include<cmath>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int xGradient(Mat image, int x, int y)
{
    return image.at<uchar>(y-1, x-1) +
                2*image.at<uchar>(y, x-1) +
                 image.at<uchar>(y+1, x-1) -
                  image.at<uchar>(y-1, x+1) -
                   2*image.at<uchar>(y, x+1) -
                    image.at<uchar>(y+1, x+1);
}

int yGradient(Mat image, int x, int y)
{
    return image.at<uchar>(y-1, x-1) +
                2*image.at<uchar>(y-1, x) +
                 image.at<uchar>(y-1, x+1) -
                  image.at<uchar>(y+1, x-1) -
                   2*image.at<uchar>(y+1, x) -
                    image.at<uchar>(y+1, x+1);
}

void Filter(double Kernel[][5]) 
{ 
    double sigma = 1.0; 
    double r, s = 2.0 * sigma * sigma;  
    double sum = 0.0; 
   
    for (int x = -2; x <= 2; x++) { 
        for (int y = -2; y <= 2; y++) { 
            r = sqrt(x * x + y * y); 
            Kernel[x + 2][y + 2] = (exp(-(r * r) / s)) / (M_PI * s); 
            sum += Kernel[x + 2][y + 2]; 
        } 
    } 

    for (int i = 0; i < 5; ++i) 
        for (int j = 0; j < 5; ++j) 
            Kernel[i][j] /= sum; 
} 

int main(){
    double Kernel[5][5]; 
    Filter(Kernel);
    Mat img = imread("len_full.jpg",0);
    Mat gaus = img.clone();
    for(int i = 2 ; i < img.rows ; i++)
    {
        for(int j = 2; j < img.cols ; j++)
        {
            gaus.at<uchar>(i,j) = img.at<uchar>(i-2,j-2)*Kernel[0][0]
                                    +img.at<uchar>(i-2,j-1)*Kernel[0][1]
                                    +img.at<uchar>(i-2,j)*Kernel[0][2]
                                    +img.at<uchar>(i-2,j+1)*Kernel[0][3]
                                    +img.at<uchar>(i-2,j+2)*Kernel[0][4]
                                    +img.at<uchar>(i-1,j-2)*Kernel[1][0]
                                    +img.at<uchar>(i-1,j-1)*Kernel[1][1]
                                    +img.at<uchar>(i-1,j)*Kernel[1][2]
                                    +img.at<uchar>(i-1,j+1)*Kernel[1][3]
                                    +img.at<uchar>(i-1,j+2)*Kernel[1][4]
                                    +img.at<uchar>(i,j-2)*Kernel[2][0]
                                    +img.at<uchar>(i,j-1)*Kernel[2][1]
                                    +img.at<uchar>(i,j)*Kernel[2][2]
                                    +img.at<uchar>(i,j+1)*Kernel[2][3]
                                    +img.at<uchar>(i,j+2)*Kernel[2][4]
                                    +img.at<uchar>(i+1,j-2)*Kernel[3][0]
                                    +img.at<uchar>(i+1,j-1)*Kernel[3][1]
                                    +img.at<uchar>(i+1,j)*Kernel[3][2]
                                    +img.at<uchar>(i+1,j+1)*Kernel[3][3]
                                    +img.at<uchar>(i+1,j+2)*Kernel[3][4]
                                    +img.at<uchar>(i+2,j-2)*Kernel[4][0]
                                    +img.at<uchar>(i+2,j-1)*Kernel[4][1]
                                    +img.at<uchar>(i+2,j)*Kernel[4][2]
                                    +img.at<uchar>(i+2,j+1)*Kernel[4][3]
                                    +img.at<uchar>(i+2,j+2)*Kernel[4][4];

        }

    }
    Mat sobelOpertor = gaus.clone();
    int gx, gy, sum;
     for(int y = 1; y < img.rows - 1; y++){
            for(int x = 1; x < img.cols - 1; x++){
                gx = xGradient(gaus, x, y);
                gy = yGradient(gaus, x, y);
                sum = abs(gx) + abs(gy);
                sum = sum > 255 ? 255:sum;
                sum = sum < 0 ? 0 : sum;
                cout<<sum<<endl;
                sobelOpertor.at<uchar>(y,x) = sum;
            }
        }
    
    return 0;
}