// CMakeProject1.cpp: 定义应用程序的入口点。
//

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/tracking.hpp>
#include <iostream>

//#include <thread>
#include <chrono>
//#include <time.h>
using namespace std;
using namespace cv;
int main()
{
	String video_filename = R"(C:/3.webm)";
	cv::VideoCapture Cap;
	Cap.open(video_filename);
	double interval_time = 1/Cap.get(CAP_PROP_FPS);
	cout << interval_time*1000 ;
	Mat frame;
	Rect2d bbox;
	Ptr<Tracker> tck=TrackerKCF::create();
	bool track_success;
	int count=0;
	auto t_stamp=chrono::system_clock::now();
	int fps = -1;
	while (true) {

		Cap >> frame;
		if (frame.empty())
			break;
		track_success = tck->update(frame, bbox);
		/*if (!track_success) {
			cout << "fail";
		}
		else {
			cout << "success";
		}*/
		if (!bbox.empty() &&track_success) {
			rectangle(frame, bbox, Scalar(0, 255, 0));
		}
		if (fps != -1) {
			putText(frame, "FPS:  "+to_string(fps), Point(20, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50),2);
		}
		if (!track_success) {
			putText(frame, "trakcer fail" , Point(20, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);
		}
		imshow("scanner", frame);

		if (waitKey((int)(interval_time * 1000)) == 's') {
			bbox=selectROI("scanner", frame);
			tck->clear();
			tck = TrackerKCF::create();
			tck->init(frame,bbox);
		}
		if (count == 19) {
			fps =20*1000/chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - t_stamp).count();
			t_stamp = chrono::system_clock::now();
		}
		//cout << fps << endl;
		count = (count + 1) % 20;
		//waitKey(0);
	}
	return 0;
}
