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

int main(int argc, char* argv[])
{
    printf("hello world!\n");
    preProc(&stPicNodeList, "/Users/CS/Pictures/test");
    printPicNodeList(&stPicNodeList);
    printf("bye world!\n");
	return 0;
}
