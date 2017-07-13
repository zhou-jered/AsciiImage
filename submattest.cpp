#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
using namespace cv;

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


int main(int, char**)
{
	Mat mm(500,600,CV_8U,Scalar(255,255,255));

	putText(mm,"Hello World",Point(0,100),FONT_HERSHEY_SIMPLEX, 2, Scalar(0));
	imwrite("mm.jpg",mm);

	Mat subm  =  submat(mm, 0,100, 100,100);
	imwrite("subm.jpg", subm);	
	cout<<"write completed"<<subm.rows<<" -- "<<subm.cols<<endl;
	system("open mm.jpg");
	system("open subm.jpg");


	return 0;
}
