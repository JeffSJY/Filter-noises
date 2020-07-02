#include "filters.h"

/*

filter Gaussiano

*/

void operatorGaussiano(double Kernel[][5])
{
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;
    double sum = 0.0;

    for (int x = -2; x <= 2; x++)
    {
        for (int y = -2; y <= 2; y++)
        {
            r = sqrt(x * x + y * y);
            Kernel[x + 2][y + 2] = (exp(-(r * r) / s)) / (M_PI * s);
            sum += Kernel[x + 2][y + 2];
        }
    }

    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            Kernel[i][j] /= sum;
}

void filterGaussiano(Mat src)
{
    double Kernel[5][5];
    operatorGaussiano(Kernel);
    Mat copy = src.clone();
    for (int i = 2; i < src.rows; i++)
    {
        for (int j = 2; j < src.cols; j++)
        {
            copy.at<uchar>(i, j) = src.at<uchar>(i - 2, j - 2) * Kernel[0][0] + src.at<uchar>(i - 2, j - 1) * Kernel[0][1] + src.at<uchar>(i - 2, j) * Kernel[0][2] + src.at<uchar>(i - 2, j + 1) * Kernel[0][3] + src.at<uchar>(i - 2, j + 2) * Kernel[0][4] + src.at<uchar>(i - 1, j - 2) * Kernel[1][0] + src.at<uchar>(i - 1, j - 1) * Kernel[1][1] + src.at<uchar>(i - 1, j) * Kernel[1][2] + src.at<uchar>(i - 1, j + 1) * Kernel[1][3] + src.at<uchar>(i - 1, j + 2) * Kernel[1][4] + src.at<uchar>(i, j - 2) * Kernel[2][0] + src.at<uchar>(i, j - 1) * Kernel[2][1] + src.at<uchar>(i, j) * Kernel[2][2] + src.at<uchar>(i, j + 1) * Kernel[2][3] + src.at<uchar>(i, j + 2) * Kernel[2][4] + src.at<uchar>(i + 1, j - 2) * Kernel[3][0] + src.at<uchar>(i + 1, j - 1) * Kernel[3][1] + src.at<uchar>(i + 1, j) * Kernel[3][2] + src.at<uchar>(i + 1, j + 1) * Kernel[3][3] + src.at<uchar>(i + 1, j + 2) * Kernel[3][4] + src.at<uchar>(i + 2, j - 2) * Kernel[4][0] + src.at<uchar>(i + 2, j - 1) * Kernel[4][1] + src.at<uchar>(i + 2, j) * Kernel[4][2] + src.at<uchar>(i + 2, j + 1) * Kernel[4][3] + src.at<uchar>(i + 2, j + 2) * Kernel[4][4];
        }
    }
    namedWindow("Gaussiano", CV_WINDOW_AUTOSIZE);
    imshow("Gaussiano", copy);
    waitKey();
}

/*
    Zoom
*/

void zoom(Mat src, int size)
{

    Mat copy = src.clone();
    Mat imgZoom = Mat::zeros(src.rows * size, src.cols * size, CV_8UC3);
    for (int i = 0; i < src.cols; i++)
    {
        for (int j = 0; j < src.rows; j++)
        {
            Vec3b colorOne = src.at<Vec3b>(Point(i, j));
            for (int x = 0; x < size; x++)
            {
                for (int y = 0; y < size; y++)
                {
                    Vec3b colorTwo = imgZoom.at<Vec3b>(Point(i, j));
                    colorTwo.val[0] = colorOne.val[0];
                    colorTwo.val[1] = colorOne.val[1];
                    colorTwo.val[2] = colorOne.val[2];

                    imgZoom.at<Vec3b>(Point(i * size + x, j * size + y)) = colorTwo;
                }
            }
        }
    }

    namedWindow("Zoom", CV_WINDOW_AUTOSIZE);
    imshow("Zoom", imgZoom);
    waitKey();
}

/*
    Median

*/

void bubbleSort(int pixels[])
{
    int i, j, aux;

    for (i = 1; i < 9; i++)
    {
        for (j = 0; j < 9 - 1; j++)
        {
            if (pixels[j] > pixels[j + 1])
            {
                aux = pixels[j];
                pixels[j] = pixels[j + 1];
                pixels[j + 1] = aux;
            }
        }
    }
}

void median(Mat src)
{
    Mat img = src.clone();
    int pixels[9];
    for (int y = 1; y < src.rows - 1; y++)
    {
        for (int x = 1; x < src.cols - 1; x++)
        {
            pixels[0] = img.at<uchar>(y - 1, x - 1);
            pixels[1] = img.at<uchar>(y, x - 1);
            pixels[2] = img.at<uchar>(y + 1, x - 1);
            pixels[3] = img.at<uchar>(y - 1, x);
            pixels[4] = img.at<uchar>(y, x);
            pixels[5] = img.at<uchar>(y + 1, x);
            pixels[6] = img.at<uchar>(y - 1, x + 1);
            pixels[7] = img.at<uchar>(y, x + 1);
            pixels[8] = img.at<uchar>(y + 1, x + 1);
            bubbleSort(pixels);

            src.at<uchar>(y, x) = pixels[4];
        }
    }
    namedWindow("Mediana", CV_WINDOW_AUTOSIZE);
    imshow("Mediana", img);
    waitKey();
}

/*
    Sal & Pimenta
*/

void saltAndPepper(Mat src, int factor)
{
    Mat copy = src.clone();

    for (unsigned int i = 0; i < factor; i++)
    {
        int a = rand() % src.cols;
        int b = rand() % src.rows;
        int c = rand() % 2;
        // Escala de cinza
        if (c == 1)
            copy.at<uchar>(b, a) = 255;
        else
            copy.at<uchar>(b, a) = 0;
    }
    namedWindow("Sal e Pimenta", CV_WINDOW_AUTOSIZE);
    imshow("Sal e Pimenta", copy);
    waitKey();
}

/*

    laplaciano

*/

void filterLaplaciano(Mat src)
{

    int median;
    int gx, gy;
    Mat copy = src.clone();
    for (int y = 1; y < src.rows - 1; y++)
    {
        for (int x = 1; x < src.cols - 1; x++)
        {
            gx = src.at<uchar>(y - 1, x) - src.at<uchar>(y + 1, x);
            gy = src.at<uchar>(y, x - 1) - src.at<uchar>(y, x + 1);
            median = abs(gx) + abs(gy);
            median = median > 255 ? 255 : median;
            median = median < 0 ? 0 : median;
            copy.at<uchar>(y, x) = median;
        }
    }
    namedWindow("Laplaciano", CV_WINDOW_AUTOSIZE);
    imshow("Laplaciano", copy);
    waitKey();
}

/*
    Sobel 

*/

int xGradientSobel(Mat image, int x, int y)
{
    return image.at<uchar>(y - 1, x - 1) +
           2 * image.at<uchar>(y, x - 1) +
           image.at<uchar>(y + 1, x - 1) -
           image.at<uchar>(y - 1, x + 1) -
           2 * image.at<uchar>(y, x + 1) -
           image.at<uchar>(y + 1, x + 1);
}

int yGradientSobel(Mat image, int x, int y)
{
    return image.at<uchar>(y - 1, x - 1) +
           2 * image.at<uchar>(y - 1, x) +
           image.at<uchar>(y - 1, x + 1) -
           image.at<uchar>(y + 1, x - 1) -
           2 * image.at<uchar>(y + 1, x) -
           image.at<uchar>(y + 1, x + 1);
}

void filterSobel(Mat src)
{

    Mat copy = src.clone();
    int gx, gy, sum;
    for (int y = 1; y < src.rows - 1; y++)
    {
        for (int x = 1; x < src.cols - 1; x++)
        {
            gx = xGradientSobel(src, x, y);
            gy = yGradientSobel(src, x, y);
            sum = abs(gx) + abs(gy);
            sum = sum > 255 ? 255 : sum;
            copy.at<uchar>(y, x) = sum;
        }
    }

    namedWindow("Sobel", CV_WINDOW_AUTOSIZE);
    imshow("Sobel", copy);
    waitKey();
}

/*
    Prewitt
*/

int xGradientPrewitt(Mat image, int x, int y)
{
    return image.at<uchar>(y - 1, x - 1) +
           image.at<uchar>(y, x - 1) +
           image.at<uchar>(y + 1, x - 1) -
           image.at<uchar>(y - 1, x + 1) -
           image.at<uchar>(y, x + 1) -
           image.at<uchar>(y + 1, x + 1);
}

int yGradientPrewitt(Mat image, int x, int y)
{
    return image.at<uchar>(y - 1, x - 1) +
           image.at<uchar>(y - 1, x) +
           image.at<uchar>(y - 1, x + 1) -
           image.at<uchar>(y + 1, x - 1) -
           image.at<uchar>(y + 1, x) -
           image.at<uchar>(y + 1, x + 1);
}

void filterPrewitt(Mat src)
{

    Mat dst;
    int gx, gy, sum;
    dst = src.clone();

    for (int y = 1; y < src.rows - 1; y++)
    {
        for (int x = 1; x < src.cols - 1; x++)
        {
            gx = xGradientPrewitt(src, x, y);
            gy = yGradientPrewitt(src, x, y);
            sum = abs(gx) + abs(gy);
            sum = sum > 255 ? 255 : sum;
            sum = sum < 0 ? 0 : sum;
            dst.at<uchar>(y, x) = sum;
        }
    }

    namedWindow("Prewitt", CV_WINDOW_AUTOSIZE);
    imshow("Prewitt", dst);
    waitKey();
}