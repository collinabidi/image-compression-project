// opencvtest.cpp : Defines the entry point for the console application.
//
//Uncomment the following line if you are compiling this code in Visual Studio
#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	vector<String> fn;
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
				// read and display the image
				images[i] = imread(fn[i]);
				imshow((String)fn[i], images[i]);
				cout << fn[i] << endl;

				// convert image to greyscale
				cvtColor(images[i], images[i], CV_BGR2GRAY);

				// save image to new file
				cout << name << endl;
				imwrite(directory + "/new_" + name, images[i]);
				cout << "Writing to " + directory + "/new_" + name << endl;

				// blur image
				//blur(grey, detected_edges, Size(3, 3));

				// apply Canny transform
				//Canny(detected_edges, detected_edges, 50, 50 * 3, 3);

				// create black image and copy image result to dst and detected_edges
				//dst = Scalar::all(0);
				//image.copyTo(dst, detected_edges);

				// display result
				//cout << i << endl;
				//String yes = fn[i];
				//namedWindow(yes);
				//imshow(yes, dst);
			}
		}
		waitKey(0);
		return 0;
	}