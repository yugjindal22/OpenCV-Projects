#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/////////////////  Warp Images(Bird eye view)  //////////////////////

int main()
{

    float w = 250, h = 350;
    string path = "Resources/cards.jpg";
    Mat img = imread(path);
    Mat matrix, imgWarp;

    Point2f src[4] = {{60, 325}, {341, 276}, {88, 635}, {405, 572}}; // Points of the card
    Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};   // Points of the final image

    matrix = getPerspectiveTransform(src, dst);

    warpPerspective(img, imgWarp, matrix, Point(w, h)); // Warp the image

    for (int i = 0; i < 4; i++)
    {
        circle(img, src[i], 10, Scalar(0, 0, 255), FILLED); // Draw a circle on the points of the card
    }

    imshow("Image", img);
    imshow("Image Warp", imgWarp);
    waitKey(0);
}
