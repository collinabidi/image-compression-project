// opencvtest.cpp : Defines the entry point for the console application.
//
//Uncomment the following line if you are compiling this code in Visual Studio
#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	// define new variables
	int const max_lowThrehold = 100;
	int lowThreshold = 30, ratio = 3, kernel_size = 3;
	vector<String> fn;	// vector to hold locations of the files we want to transform
	String directory = "C:/Desktop/opencvtest/opencvtest/data";
	glob(directory + "/*.*", fn, false);

	size_t count = fn.size(); // number of images in folder

	vector<Mat> images(fn.size());

	// loop through images in folder
		for (size_t i = 0; i < count; i++)
		{
			// makes sure image isn't already converted
			String name = fn[i].substr(fn[i].find_last_of("\\") + 1, fn[i].length());	// get filename
			if (name.find("new_"))
			{
				// create new temp variables
				Mat detected_edges, dst;
				// read and display the image
				images[i] = imread(fn[i]);
				imshow((String)fn[i], images[i]);
				cout << fn[i] << endl;

				// convert image to greyscale
				cvtColor(images[i], images[i], CV_BGR2GRAY);

				//blur image
				blur(images[i], detected_edges, Size(3, 3));

				 //apply canny transform
				Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

				//create black image and copy image result to dst and detected_edges
				dst.create(images[i].size(), images[i].type());
				dst = Scalar::all(0);
				images[i].copyTo(dst, detected_edges);

				// save image to new file
				cout << name << endl;
				imwrite(directory + "/new_" + name, detected_edges);
				cout << "Writing to " + directory + "/new_" + name << endl;
			}
		}
		waitKey(0);
		return 0;
	}