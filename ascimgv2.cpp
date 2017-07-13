#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include "aschelper.hpp"


using namespace cv;
using namespace std;

    
int main(int argc, char** argv) 
{
	if(argc < 4) {
		cout <<"give an image and sub image width and height"<<endl;
		return 1;
	}


	Mat templ = imread(argv[1], 0);
	if(templ.empty()) {
		cout<<"read image error!"<<endl;
		return 1;
	}
	cout<<"Read completed"<<endl;
	
	int width=0, height=0;
	sscanf(argv[2],"%d", &width);
	sscanf(argv[3],"%d", &height);
	
	cout<<"using subiamge: "<<width<<"x"<<height<<endl;

	Mat* mats = ascMats(width, height);
	for(int i  =0;i<templ.rows; i+= height)
	{
		for(int j =0; j<templ.cols ; j+=width)
		{
			char c =  findRectChar(templ, mats , i, j, width, height);
			cout<<c;			
		}
		cout<<endl;
	}	

	return 0;
}
