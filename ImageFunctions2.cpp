#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////  Resize and Crop //////////////////////

int main()
{

    string path = "Resources/test.png";
    Mat img = imread(path);
    Mat imgResize, imgCrop;

    // cout << img.size() << endl;
    resize(img, imgResize, Size(340, 480));   // Resize the image to 340x480 exactly
    resize(img, imgResize, Size(), 0.5, 0.5); // Resize the image to half the size

    Rect roi(200, 100, 300, 300); // Region of Interest  (x, y, width, height)
    imgCrop = img(roi);           // Crop the image

    imshow("Image", img);
    imshow("Image Resize", imgResize);
    imshow("Image Crop", imgCrop);
    waitKey(0);
}
