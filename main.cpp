#include <iostream>

#include "opencv2/opencv.hpp"

using namespace cv;

using namespace std;

int main(int argc, const char *argv[])
{

    // insert code here...

    cout << "OpenCV version : " << CV_VERSION << endl;

    cout << "Major version : " << CV_MAJOR_VERSION << endl;

    cout << "Minor version : " << CV_MINOR_VERSION << endl;

    cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;

    std::cout << "Hello, World!\n";

    return 0;
}