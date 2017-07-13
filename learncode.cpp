#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
	if( argc<3) {
		cout<<"give a img  and divideWidth"<<endl;
		return 1;
	}		
	long tickCount = getTickCount();	
	char filename[8]="rr0.png";
	char opencmd[] = "open rr0.png";


	Mat img = imread(argv[1], 0);

	int channel = img.channels();
	cout<<"channel : "<<channel<<endl;
	cout<<"isContinuous: "<<img.isContinuous()<<endl;

	uchar table[256];
	int divideWidth = 0;
	stringstream  s ;
	s<<argv[2];
	s>>divideWidth;

	cout<<"got divideWidth: "<<divideWidth<<endl;
	if(!s || !divideWidth)  {
		cout<<"invalid divideWidth"<<endl;
		return 1;
	}
	

	int nRows = img.rows;
	int nCols = nRows * channel;

	if(img.isContinuous()) {
		nCols *=  nRows;
		nRows =1;
	}

	cout<<"-------\n";
	int i ,j;
	uchar * p;

	for(int i =0;i<256;i++) {
		table[i] = (uchar)(divideWidth * (i/divideWidth));
	}
	for(i =0;i<nRows ;i++) {
		p = img.ptr<uchar>(i);
		for(j=0;j<nCols;j++) {
			p[j] =  table[p[j]];
		}
	}
 
	imwrite(filename, img);
	system(opencmd);
	long endTick = getTickCount();
	cout<<"Fre: "<<getTickFrequency()<<endl;
	cout<<"cost count: "<<(endTick-tickCount)<<endl;
	return 0;	


}


