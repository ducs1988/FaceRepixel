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
    preProc(&stPicNodeList, "/Users/CS/Pictures/Picasa/Exports/Pics");
    printPicNodeList(&stPicNodeList);
    repixel("/Users/CS/Pictures/DSC03081.JPG", &stPicNodeList, &stRefillList, 100, 200);
    printRefillList(&stRefillList);
    
    printf("bye world!\n");
    
    refill("/Users/CS/Pictures/DSC03081.JPG", &stRefillList);
    
    printf("bye world!\n");
    
	return 0;
     
}
