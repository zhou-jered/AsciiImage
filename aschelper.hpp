#include  "opencv2/core.hpp"
using namespace cv;

#ifndef ASC_HELPER
#define ASC_HELPER


Mat* ascMats(int , int );
char findRectChar(Mat& origin, Mat* mats, int sx, int st, int width, int height);

#endif
