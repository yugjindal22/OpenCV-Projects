#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////  Basic Functions  //////////////////////

int main()
{

    string path = "Resources/test.png";
    Mat img = imread(path);
    Mat imgGray;
    Mat imgBlur;
    Mat imgCanny;
    Mat imgDil;
    Mat imgErode;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(img, imgCanny, 50, 150);
    dilate(imgCanny, imgDil, kernel);
    erode(imgDil, imgErode, kernel);

    imshow("Image", img);
    imshow("Image Gray", imgGray);
    imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny);
    imshow("Image Dilation", imgDil);
    imshow("Image Erode", imgErode);
    waitKey(0);
}
