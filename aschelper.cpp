#include "aschelper.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <cstring>
#include <iostream>

using namespace std;
using namespace cv;

Mat submat(Mat&, int, int, int, int);

Scalar getMSSIM(const Mat&, const Mat&);

Mat* ascMats(int width, int height)
{
	Mat* mats = new Mat[128];
	char s[]="1";
	for(int i = 33; i<128 ; i++)
	{
		s[0]=i;
		Mat cm(height, width,0,Scalar(255,255,255));
		putText(cm, s, Point(0, height * 0.75), FONT_HERSHEY_SIMPLEX,(width*1.0 / 35) * 1.0,Scalar(0));
		mats[i] = cm;
	}
	return mats;
}


char findRectChar(Mat& origin, Mat* mats, int sx, int sy,int width, int height) 
{
	Mat target = submat(origin, sx, height, sy, width);
	double maxSame = -1;
	int maxMatchChar = 0;
	for(int i = 33;i<128;i++)
	{
		Scalar result = getMSSIM(target, mats[i]);
		if(result[0] >  maxSame) 
		{
			maxSame = result[0];
			maxMatchChar =i;
		}
	}
	return (char) maxMatchChar;
}



Mat submat(Mat& m, int sx, int xl, int sy, int yl)
{
        Mat subm(xl,yl,CV_8U);
        int sr=0,sc=0; //submat_row, submat_col
        for(int i =sx;i<sx+xl;i++)
        {
                sc=0;
                uchar* op = m.ptr<uchar>(i);
                uchar* sp = subm.ptr<uchar>(sr);
                for(int j=sy;j<sy+yl;j++)
                {
                        sp[sc++]=op[j];
                }
                sr++;
        }
        return subm;

}



Scalar getMSSIM( const Mat& i1, const Mat& i2)
{
    const double C1 = 6.5025, C2 = 58.5225;
    /***************************** INITS **********************************/
    int d     = CV_32F;
    Mat I1, I2;
    i1.convertTo(I1, d);           // cannot calculate on one byte large values
    i2.convertTo(I2, d);
    Mat I2_2   = I2.mul(I2);        // I2^2
    Mat I1_2   = I1.mul(I1);        // I1^2
    Mat I1_I2  = I1.mul(I2);        // I1 * I2
    /*************************** END INITS **********************************/
    Mat mu1, mu2;   // PRELIMINARY COMPUTING
    GaussianBlur(I1, mu1, Size(11, 11), 1.5);
    GaussianBlur(I2, mu2, Size(11, 11), 1.5);
    Mat mu1_2   =   mu1.mul(mu1);
    Mat mu2_2   =   mu2.mul(mu2);
    Mat mu1_mu2 =   mu1.mul(mu2);
    Mat sigma1_2, sigma2_2, sigma12;
    GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
    sigma1_2 -= mu1_2;
    GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
    sigma2_2 -= mu2_2;
    GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
    sigma12 -= mu1_mu2;
    Mat t1, t2, t3;
    t1 = 2 * mu1_mu2 + C1;
    t2 = 2 * sigma12 + C2;
    t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
    t1 = mu1_2 + mu2_2 + C1;
    t2 = sigma1_2 + sigma2_2 + C2;
    t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
    Mat ssim_map;
    divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;
    Scalar mssim = mean( ssim_map ); // mssim = average of ssim map
    return mssim;
}
