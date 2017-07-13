#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if(argc<3) 
	{
		cout<<"input width and height"<<endl;
		return 0;
	}
	char filename[] = "char[0].png";
	char opencmd[] = "open char[0].png";
	char s[] = "0";
	int imgWidth = 10;
	int imgHeight= 10;		
	stringstream ss;
	ss<<argv[1];
	ss>>imgWidth;
	sscanf(argv[2], "%d", &imgHeight);
	for(int i = 33; i<128 ; i++)
	{
		s[0]=i;
		Mat cm(imgHeight, imgWidth*0.8,0,Scalar(255,255,255));
		putText(cm, s, Point(0, imgWidth * 0.75), FONT_HERSHEY_SIMPLEX,(imgWidth*1.0 / 35) * 1.0,Scalar(0));
		filename[5]=i;
		opencmd[10]=i;
		imwrite(filename, cm);
		system(opencmd);	
	}
	return 0;
}
