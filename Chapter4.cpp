#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////  Resize and Crop //////////////////////

int main()
{
    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255)); // Create a white image for background

    circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);                   // Draw a filled circle
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED); // Draw a filled rectangle
    line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);           // Draw a line

    putText(img, "Hello World!", Point(137, 262), FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 69, 255), 2); // Add text

    imshow("Image", img);
    waitKey(0);
}