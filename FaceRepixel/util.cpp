//
//  util.cpp
//  FaceRepixel
//
//  Created by Chenshi Du on 11/2/12.
//  Copyright (c) 2012 IIT. All rights reserved.
//

#include "fr.h"

int computeAvgAndVar(char* path, Color* avg, Color* var) {
    
    Mat cimg = imread(path);
    
    int cAvg=computeAvg(cimg, 0, 0, cimg.rows-1, cimg.cols-1, avg);
    int cVar=computeVar(cimg, 0, 0, cimg.rows-1, cimg.cols-1, avg, var);
    
    if (cAvg==0 && cVar==0)
        return 0;
    else
        return -1;
}

int computeAvg(Mat &cimg, int xstart, int ystart, int xend, int yend, Color* avg) {
    
    double sumB = 0.0;
    double sumG = 0.0;
    double sumR = 0.0;
    
    double numPixel = (xend-xstart+1)*(yend-ystart+1);
    
    for (int i=xstart; i<=xend; i++) {
        for (int j=ystart; j<yend; j++) {
            sumB += cimg.at<Vec3b>(i,j)[0];
            sumG += cimg.at<Vec3b>(i,j)[1];
            sumR += cimg.at<Vec3b>(i,j)[2];
        }
    }
    
    avg->bValue=sumB/numPixel;
    avg->gValue=sumG/numPixel;
    avg->rValue=sumR/numPixel;
    
    return 0;
}

int computeVar(Mat &cimg, int xstart, int ystart, int xend, int yend, Color* avg, Color* var) {

    double sumB = 0.0;
    double sumG = 0.0;
    double sumR = 0.0;
    double numPixel = (xend-xstart+1)*(yend-ystart+1);
    
    for (int i=xstart; i<=xend; i++) {
        for (int j=ystart; j<yend; j++) {
            sumB += pow(cimg.at<Vec3b>(i,j)[0]-avg->bValue,2);
            sumG += pow(cimg.at<Vec3b>(i,j)[1]-avg->gValue,2);
            sumR += pow(cimg.at<Vec3b>(i,j)[2]-avg->rValue,2);
        }
    }
    
    var->bValue=sqrt(sumB/numPixel);
    var->gValue=sqrt(sumG/numPixel);
    var->rValue=sqrt(sumR/numPixel);
        
    return 0;
}