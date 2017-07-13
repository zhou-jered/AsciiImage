#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <string>
#include <cstdlib>



using namespace cv;
using namespace std;

int grayTable[256];
int cal_gray(Mat img) {
	int gc = 0;
	for(int r=0;r<img.rows; r++) {
		uchar* p  = img.ptr<uchar>(r);
		for(int c=0;c<img.cols;c++) {
			int val = (int)p[c];
			if(val< 1) {
				gc ++;
			}
		}
	}
	double gray = gc * 1.0 / 100 * 256;
	return (int) gray;
}

char find_char(int gray) {
	int bias = 0;
	while( bias < 127) {
		if(grayTable[gray + bias]>0) {
			return (char)grayTable[gray + bias];
		}
		if(grayTable[gray - bias]>0) {
			return (char)grayTable[gray - bias];
		}
		bias++;
	}
	return (char)32;
}

int min(int a,int b) {return a>b?b:a;}

int area_gray(Mat& m, int fromX, int fromY, int size) {
	double tot =0;
	int gridCount =0;
	for(int i =fromX; i<min(m.rows, fromX + size); i++) {
		uchar * p = m.ptr<uchar>(i);
		for(int j=fromY; j<min(m.cols, fromY + size); j++) {
			gridCount ++;
			tot += ((int)p[j]);
		}
	}
	double gray = tot / (gridCount * 255) * 256;
	return (int)gray;
}
    
int main(int argc, char** argv) 
{
	if(argc < 4) {
		cout <<"give an image and gap and jump row"<<endl;
		return 1;
	}
	char s[2]="0";
	memset(grayTable,0, sizeof(grayTable));
	for(int i=33;i<127;i++) {
		Mat img(100,100,CV_8U, Scalar(255,255,255));
		Point pos = Point(0,9);
		s[0]=i;
		putText(img,s,pos,FONT_HERSHEY_SIMPLEX,1,Scalar(0));
		int gray = cal_gray(img);
		int bias =0;
		while(bias < 128) {
			if(gray + bias < 256 && grayTable[gray + bias]==0) {
				grayTable[gray+bias] = i;
				break;
			}
			if(gray - bias>=0 && grayTable[gray - bias]==0) {
				grayTable[gray - bias] = i;
				break;
			}
			bias ++;
		}
	}

	Mat templ = imread(argv[1], 0);
	if(templ.empty()) {
		cout<<"read image error!"<<endl;
		return 1;
	}
	cout<<"Read completed"<<endl;
	int gap = 5;
	int rowGap = 0;
	stringstream gs;
	gs<<argv[2];
	gs>>gap;

	stringstream rs;
	rs<<argv[3];
	rs>>rowGap;
	for(int i =0;i<templ.rows;i+=gap + rowGap) {
		uchar* p = templ.ptr<uchar>(i);
		for(int j =0; j<templ.cols; j+=gap) {
			//cout<<i<<" "<<j<<endl;
			int ag = area_gray(templ, i,j, gap);
			cout<<find_char(ag);
		}
		cout<<endl;
	}
	return 0;
}
