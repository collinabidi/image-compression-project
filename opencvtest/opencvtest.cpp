// opencvtest.cpp : Defines the entry point for the console application.
//
//Uncomment the following line if you are compiling this code in Visual Studio
#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	//Open the default video camera
	VideoCapture cap(0);
	int lowThreshold;
	int const max_lowThreshold = 100;
	int ratio = 3;
	int kernel_size = 3;


	// if not success, exit program
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video camera" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

	string window_name = "My Camera Feed";
	namedWindow(window_name); //create a window called "My Camera Feed"

	createTrackbar("Min Threshold", window_name, &lowThreshold, max_lowThreshold);

	while (true)
	{
		Mat frame, greyFrame, dst, detected_edges;
		bool bSuccess = cap.read(frame); // read a new frame from video 

										 //Breaking the while loop if the frames cannot be captured
		if (bSuccess == false)
		{
			cout << "Video camera is disconnected" << endl;
			cin.get(); //Wait for any key press
			break;
		}
		//convert image to greyscale
		cvtColor(frame, greyFrame, CV_BGR2GRAY);

		/// Reduce noise with a kernel 3x3
		blur(greyFrame, detected_edges, Size(3,3));

		/// Canny detector
		Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

		/// Using Canny's output as a mask, we display our result
		dst = Scalar::all(0);

		frame.copyTo(dst, detected_edges);

		//show the frame in the created window
		imshow(window_name, dst);

		//wait for for 10 ms until any key is pressed.  
		//If the 'Esc' key is pressed, break the while loop.
		if (waitKey(10) == 27)
		{
			cout << "Esc key is pressed by user. Stoppig the video" << endl;
			break;
		}
	}

	return 0;

}