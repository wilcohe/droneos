#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
#include "opencv2/videoio.hpp"


int main(){
	cv::VideoCapture cap; 
	if (!cap.open(0)){
		std::cout << "No cam found\n";
		return 0;
	}
	std::deque<std::vector<uchar>> toSVD;
	for (int i = 1; i < 10;i++){
		std::cout << "testing\n";
		std::vector<uchar> arr1d;
		cv::Mat frame; 
		cap >> frame; 
		if (frame.isContinuous()){
			arr1d.assign(frame.data, frame.data + frame.total()*frame.channels());
		}
		else{
			for (int idx = 0; i < frame.rows; ++i){
				arr1d.insert(arr1d.end(), frame.ptr<uchar>(i), frame.ptr<uchar>(i) + frame.cols*frame.channels());
			}
		}
		//if (frame.empty()) break;
		//std::cout << frame << "\n";
		//cv::imwrite(std::to_string(i) + ".jpeg", frame);
		if (toSVD.size() < 10){
			toSVD.push_back(arr1d);
		}	
		else{
			toSVD.pop_front(); 
			toSVD.push_back(arr1d); 
		}
	}
	cap.release(); 
	return 0;
}
