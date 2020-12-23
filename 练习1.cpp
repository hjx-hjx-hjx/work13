#include<iostream>
#include<opencv.hpp>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened()) {
		cout << "打不开摄像头！" << endl;
	}
	int cnt = 0;
	Mat frame, tempMat, refMat, resultMat;
	while (1) {
		cap >> frame;
		if (cnt == 0) {
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
			cnt++;
		}

		matchTemplate(frame, refMat, resultMat, 0);
		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());
		double minVal, maxVal;
		Point minLoc, maxLoc;
		Point matchLoc;
		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
		Rect rect;
		rect.x = minLoc.x;
		rect.y = minLoc.y;
		rect.width = refMat.cols;
		rect.height = refMat.rows;
		rectangle(frame, rect, CV_RGB(255, 0, 0), 1, 8, 0);
		imshow("result", frame);
		waitKey(30);
	}
	return 0;
}