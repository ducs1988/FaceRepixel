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

typedef struct Color{
    double  rValue;
    double  gValue;
    double  bValue;
}Avg, Var;

typedef struct {
    char    path[512];
    Color	avg;
    Color	var;
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
    ReplaceInfo *head;
}RefillList;

// compute average & var
int computeAvgAndVar(char* path, Color* avg, Color* var);

// compute average
int computeAvg(Mat &cimg, int xstart, int ystart, int xend, int yend, Color* avg);

// compute variance
int computeVar(Mat &cimg, int xstart, int ystart, int xend, int yend, Color* avg, Color* var);

// preproc


#endif
