#ifndef __FILTERS_H_
#define __FILTERS_H_
#include<cmath>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp> 
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void filterGaussiano(Mat src);
void zoom(Mat src, int size);
void saltAndPepper(Mat src, int factor);
void filterLaplaciano(Mat src);
void filterPrewitt(Mat src);
void median(Mat src);
void filterSobel(Mat src);
//void filterCanny(Mat src);

#endif