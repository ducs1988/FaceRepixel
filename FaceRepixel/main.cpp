//
//  main.cpp
//  FaceRepixel
//
//  Created by Chenshi Du on 11/2/12.
//  Copyright (c) 2012 IIT. All rights reserved.
//

#include <fr.h>

//using namespace cv;
//using namespace std;

PicNodeList stPicNodeList;
RefillList stRefillList;

int main(int argc, char* argv[])
{
    
    printf("hello world!\n");
    if (argc != 4){
        printf("FaceRepixel <path to img> <output path> <threshold>\n");
        return 0;
    }
    int cNum = atoi(argv[3]);
    if (cNum<0 || cNum>255) {
        printf("Illegal threshold. (1~255)\n");
        return 0;
    }
    char *path = argv[1];
    char *output = argv[2];
    
    
    preProc(&stPicNodeList, "/Users/CS/Pictures/Picasa/Exports/Pics");
    printPicNodeList(&stPicNodeList);
    repixel(path, &stPicNodeList, &stRefillList, 50, cNum);
    printRefillList(&stRefillList);
    
    printf("bye world!\n");
    
    refill(path, output, &stRefillList);
    
    printf("bye world!\n");
    
	return 0;
     
}
