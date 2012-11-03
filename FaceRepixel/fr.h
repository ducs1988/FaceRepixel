//
//  fr.h
//  FaceRepixel
//
//  Created by Chenshi Du on 11/2/12.
//  Copyright (c) 2012 IIT. All rights reserved.
//

#ifndef FaceRepixel_fr_h
#define FaceRepixel_fr_h

#include <math.h>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <cxcore.h>
#include <fstream>
#include <iterator>
#include <vector>

using namespace cv;
using namespace std;

typedef struct {
    char    path[512];
    double  avg;
    double  variance;
}PicNode;

typedef struct {
    int     numOfImgs;
    PicNode *picNode;
}PicNodeList;

typedef struct ReplaceInfo{
    int     xstart;
    int     ystart;
    int     xend;
    int     yend;
    ReplaceInfo *pNext;
    PicNode     *picNode;
}ReplaceInfo;

typedef struct {
    int         numOfInfo;
    ReplaceInfo *replaceInfo;
}RefillList;

// compute average & var
int computeAvgAndVar(char* path, double* avg, double* var);

// compute average
double computeAvg(Mat &cimg, int xstart, int ystart, int xend, int yend);

// compute variance
double computeVar(Mat &cimg, int xstart, int ystart, int xend, int yend, double avg);

// preproc


#endif
