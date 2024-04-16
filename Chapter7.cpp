#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////  Images  //////////////////////

void getContours(Mat imgDil, Mat img)
{

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    // drawContours(img, contours, -1, Scalar(255, 0, 255), 2); // -1 means draw all contours
    int area;
    string ObjectType;
    vector<vector<Point>> conPoly(contours.size()); // to store the corner points
    vector<Rect> boundRect(contours.size());

    for (int i = 0; i < contours.size(); i++)
    {
        area = contourArea(contours[i]);
        cout << area << endl;

        if (area > 1000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            cout << conPoly[i].size() << endl;
            boundRect[i] = boundingRect(conPoly[i]); // to draw rectangle around the object

            int objCor = (int)conPoly[i].size();

            if (objCor == 3)
            {
                ObjectType = "Tri";
            }
            else if (objCor == 4)
            {
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
                cout << aspRatio << endl;
                if (aspRatio > 0.95 && aspRatio < 1.05)
                {
                    ObjectType = "Square";
                }
                else
                {
                    ObjectType = "Rectangle";
                }
            }
            else if (objCor > 4)
            {
                ObjectType = "Circle";
            }

            drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);                                                        // i means draw only that contour which has area > 1000
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);                                   // to draw rectangle around the object
            putText(img, ObjectType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2); // Add text
        }
    }
}

int main()
{
    Mat imgGray;
    Mat imgBlur;
    Mat imgCanny;
    Mat imgDil;

    string path = "Resources/shapes.png";
    Mat img = imread(path);

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(img, imgCanny, 50, 150);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);

    getContours(imgDil, img);

    imshow("Image", img);
    // imshow("Image Gray", imgGray);
    // imshow("Image Blur", imgBlur);
    // imshow("Image Canny", imgCanny);
    // imshow("Image Dilated", imgDil);

    waitKey(0);
}
