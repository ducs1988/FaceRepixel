//
//  util.cpp
//  FaceRepixel
//
//  Created by Chenshi Du on 11/2/12.
//  Copyright (c) 2012 IIT. All rights reserved.
//

#include "fr.h"

double computeAvg(Mat &cimg, int xstart, int ystart, int xend, int yend) {
    double avg = 0.0;
    double sumB = 0.0;
    double sumG = 0.0;
    double sumR = 0.0;
    
    for (int i=xstart; i<=xend; i++) {
        for (int j=ystart; j<yend; j++) {
            sumB += cimg.at<Vec3b>(i,j)[0];
            sumG += cimg.at<Vec3b>(i,j)[1];
            sumR += cimg.at<Vec3b>(i,j)[2];
        }
    }
    
    
    
    return avg;
}

double computeVar(Mat &cimg, int xstart, int ystart, int xend, int yend, double avg) {
    double var=0;
    
    
    return var;
}