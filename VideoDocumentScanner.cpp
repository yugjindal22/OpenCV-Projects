// Use your phone's camera to scan the document,
// and disconnect the phone's camera after aligning
// the document in the frame. Then it will automatically
// be saved in "Scans" folder.

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////  Images  //////////////////////

float w = 420, h = 596;

Mat imgOriginal, imgGray, imgBlur, imgCanny, imgDil, imgErode, imgthre, imgWarp, imgCrop;

vector<Point> initialPoints, docPoints;

Mat preProcessing(Mat img)
{
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel);
    // erode(imgDil, imgErode, kernel);

    return imgDil;
}

vector<Point> getContours(Mat imgDil)
{
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Point> biggest;

    int maxArea = 0;

    for (int i = 0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        if (area > 1000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

            if (area > maxArea && conPoly[i].size() == 4)
            {
                // drawContours(imgOriginal, conPoly, i, Scalar(255, 0, 255), 5); // Draw lines around the paper
                biggest = {conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3]};
                maxArea = area;
            }
        }
    }

    return biggest;
}

void drawPoints(vector<Point> points, Scalar color)
{
    for (int i = 0; i < points.size(); i++)
    {
        circle(imgOriginal, points[i], 30, color, FILLED);
        putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 5, color, 5);
    }
}

vector<Point> reorder(vector<Point> points)
{
    vector<Point> newPoints;
    vector<int> sumPoints, subPoints;

    for (int i = 0; i < points.size(); i++)
    {
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }

    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0 //NOTE: min_element returns the address(&) of the smallest number in the array, so we subtract the address of the first element to get the index of the smallest number
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 1
    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // 2
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 3

    return newPoints;
}

Mat getWarp(Mat img, vector<Point> points, float w, float h)
{
    Point2f src[4] = {points[0], points[1], points[2], points[3]};
    Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

    Mat matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    return imgWarp;
}

int main()
{
    VideoCapture cap(1);
    Mat img;
    while (true)
    {
        cap.read(img);

        if (img.empty())
        {

            imshow("Image original", imgOriginal);
            imgthre = preProcessing(imgOriginal);
            initialPoints = getContours(imgthre);
            if (!initialPoints.empty())
            {
                docPoints = reorder(initialPoints);
                imgWarp = getWarp(imgOriginal, docPoints, w, h);
                drawPoints(docPoints, Scalar(0, 255, 255));
                imshow("Corner Points", imgOriginal);
                imshow("Image warp", imgWarp);
                imwrite("Resources/Scans/1.png", imgWarp);
                cout << "Document Saved" << endl;
                waitKey(0);
                break; // Break the loop after saving the image
                return 0;
            }
        }
        imshow("image", img);
        imgOriginal = img.clone();
        waitKey(1);
    }
}
