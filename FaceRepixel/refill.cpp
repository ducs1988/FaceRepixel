//
//  refill.cpp
//  FaceRepixel
//
//  Created by Chenshi Du on 11/2/12.
//  Copyright (c) 2012 IIT. All rights reserved.
//

#include "fr.h"

int refill(char* path, RefillList* pRefillList){
    Mat cImg = imread(path);
    Mat newImg = Mat(cImg.rows, cImg.cols, cImg.type());
    cImg.release();
    ReplaceInfo *info = pRefillList->head->pNext;
    while (info) {
        Mat src = imread(info->picNode->path);
        int newsx = info->xstart;
        int newsy = info->ystart;
        int newex = info->xend;
        int newey = info->yend;
        int rows = newex-newsx+1;
        int cols = newey-newsy+1;
        printf("rows = %d, cols = %d\n", rows, cols);
        Mat dst = Mat(rows, cols, cImg.type());
        resize(src, dst, Size(dst.cols, dst.rows));
        
        for (int i=newsx; i<=newex; i++) {
            for (int j=newsy; j<=newey; j++) {
                newImg.at<Vec3b>(i,j)[0]=dst.at<Vec3b>(i-newsx,j-newsy)[0];
                newImg.at<Vec3b>(i,j)[1]=dst.at<Vec3b>(i-newsx,j-newsy)[1];
                newImg.at<Vec3b>(i,j)[2]=dst.at<Vec3b>(i-newsx,j-newsy)[2];
            }
        }
        src.release();
        dst.release();
        info = info->pNext;
    }
    
    imwrite("repixel.png", newImg);
    
    return 0;
}