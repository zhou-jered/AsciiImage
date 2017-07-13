#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <string>
using namespace cv;
using namespace std;

Scalar getMSSIM(const Mat&, const Mat&);


int main(int, char**)
{
	char s[]="1";
	for(int i =0;i<10;i++)
	{
		for(int j =0;j<10;j++)
		{
			s[0]='0'+i;
			Mat m1(50,50,CV_8U,Scalar(255,255,255));
			Mat m2(50,50,CV_8U,Scalar(255,255,255));
			putText(m1, s, Point(0,40),FONT_HERSHEY_SIMPLEX,1,Scalar(0));
			s[0]='0'+j;
			putText(m2, s, Point(0,40),FONT_HERSHEY_SIMPLEX,1,Scalar(0));
			Scalar result = getMSSIM(m1,m2);
			cout<<i<<" - "<<j<<"  --> "<<result[0]<<endl;
			if( i ==7 && j==9) 
			{
				imwrite("ssim7.png",m1);
				imwrite("ssim9.png",m2);
			}
		}
	}
	return 0;
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
