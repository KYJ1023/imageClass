//#include "stdafx.h"
#include "pch.h"

#include "imageData.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// define class member functions
imageData::imageData()
{
	AfxMessageBox(_T("Default image constructor"));
}
imageData::imageData(CString fname)
{
	CString msg;
	ifstream infile(fname, ios::in | ios::binary);
	string inputLine = "";
	getline(infile, inputLine);
	if (inputLine.compare("P5") != 0)
	{
		//cerr << "Version error" << endl;
		msg.Format(_T("Version error"));
		AfxMessageBox(msg);
	}
	else
	{
		CA2CT str(inputLine.c_str()); // type conversion
		AfxMessageBox(str);
	}
	infile >> numcols >> numrows;
	infile >> max_val;
	pixelValues = new unsigned char[numrows*numcols]; // for data read
	infile.read(reinterpret_cast<char*>(pixelValues), numrows*numcols * sizeof(unsigned char));
	infile.close();
}

int imageData::imageLoad(CString fname)
{
	CString msg;
	ifstream infile(fname, ios::in | ios::binary);
	string inputLine = "";
	getline(infile, inputLine);
	if (inputLine.compare("P5") != 0)
	{
		//cerr << "Version error" << endl;
		msg.Format(_T("Version error"));
		AfxMessageBox(msg);
	}
	else
	{
		CA2CT str(inputLine.c_str()); // type conversion
		AfxMessageBox(str);
	}
	infile >> numcols >> numrows;
	infile >> max_val;
	pixelValues = new unsigned char[numrows*numcols]; // for data read
	infile.read(reinterpret_cast<char*>(pixelValues), numrows*numcols * sizeof(unsigned char));
	if(infile) //data load check
		AfxMessageBox(_T("Image data loaded successfully!"));
	infile.close();
	return(1);
}
int imageData::getImage(unsigned char* data) 
{
	// copy image data
	for (int i = 0; i < numcols*numrows; i++)
		data[i] = pixelValues[i];

	return(1);
}

int imageData::getWidth()
{
	return numcols;
}
int imageData::getHeight()
{
	return numrows;
}

// define a destructor function
imageData::~imageData()
{
	delete(pixelValues);
}
int imageData::imageProc(int Mode) {
	if (Mode == 1) {
		for (rows = 0; rows < numrows; ++rows) {
			for (cols = 0; cols < numcols; ++cols) {
				cout << (int)pixelValues[rows*numcols + cols] << ' ';
				pixelValues[rows*numcols + cols] = 255 - pixelValues[rows*numcols + cols];
			}
			cout << rows << endl;
		}
	}
	else if (Mode == 0) {
		for (rows = 0; rows < numrows; ++rows) {
			for (cols = 0; cols < numcols; ++cols) {
				cout << (int)pixelValues[rows*numcols + cols] << ' ';
				if (pixelValues[rows*numcols + cols] > 100) {
					pixelValues[rows*numcols + cols] = 255;
				}
				else {
					pixelValues[rows*numcols + cols] = 0;
				}
			}
			cout << rows << endl;
		}
	}
	else if (Mode == 2) {
		for (rows = 0; rows < numrows; ++rows) {
			for (cols = 0; cols < numcols; ++cols) {
				cout << (int)pixelValues[rows*numcols + cols] << ' ';
				if (pixelValues[rows*numcols + cols] > 200) {
					pixelValues[rows*numcols + cols] = 255;
				}
				else {
					pixelValues[rows*numcols + cols] = 0;
				}
			}
			cout << rows << endl;
		}
	}
	else if (Mode == 3) {
		for (rows = 0; rows < numrows; ++rows) {
			for (cols = 0; cols < numcols; ++cols) {
				cout << (int)pixelValues[rows * numcols + cols] << ' ';
				for (int i = 0; i < numrows; ++i) {
					for (int j = 0; j < numcols; ++j) {
						pixelValues[j * numrows + (numrows - 1 - i)] = pixelValues[i * numcols + j];
					}
				}
				int temp = numcols;
				numcols = numrows;
				numrows = temp;
			}
			cout << rows << endl;
		}
	}
	else {
		cout << "Wrong Mode" << endl;
	}
	pixelpProcessed = pixelValues; // pixelpProcessed can be allocated by new
	return 0;
}

int imageData::imageWrite(CString fname)
{
	ofstream ofp;
	ofp.open(fname, ios::binary);
	if (!ofp) {
		cout << "Can't open file: " << fname << endl;
		exit(1);
	}
	// write image header
	ofp << "P5 " << endl;
	ofp << numcols << " " << numrows << endl;
	ofp << max_val << endl;
	ofp.write(reinterpret_cast<const char*>(pixelpProcessed), numcols*numrows);
	if (ofp.fail()) {
		cout << "Can't write image " << fname << endl;
		exit(0);
	}
	ofp.close();
	return 0;
}