//
//  repixel.cpp
//  FaceRepixel
//
//  Created by Chenshi Du on 11/2/12.
//  Copyright (c) 2012 IIT. All rights reserved.
//

#include "fr.h"

#define MAX_VALUE 10000000000

//PicNodeList* picNodeList;
//RefillList* refillList;
ReplaceInfo* last;

int process (Mat &, int, int, int, int, int, double);
int findProperPic (Color*, Color*, PicNode**, PicNodeList*);
double checkAvg (PicNode*, Color*);
bool checkVar (Color*, double);
int repixel (char*, PicNodeList*, RefillList*, int, double);
void printNode (ReplaceInfo*);


// main process
int process (Mat &cimg, int xstart, int ystart, int xend,
             int yend, int offset, double threshold,
             PicNodeList* picNodeList, RefillList* refillList) {
    
    if (xend - xstart < 3 || yend - ystart < 3 || offset < 3)
        return 0;
    
	int x = xstart;
	int y = ystart;
    
    printf("xend = %d\n", xend);
    printf("yend = %d\n", yend);
    
	while (x < xend) {
        printf("x = %d\n", x);
		y = ystart;
		while (y < yend) {
			printf("y = %d\n", y);
            
			int xp;
			int yp;
			if (x + offset >= cimg.rows)
				xp = cimg.rows - 1;
			else
				xp = x + offset;
			if (y + offset >= cimg.cols)
				yp = cimg.cols - 1;
			else
				yp = y + offset;
            
			Color *avgs = (Color*) malloc (sizeof(Color));
			computeAvg (cimg, x, y, xp, yp, avgs);
			Color *vars = (Color*) malloc (sizeof(Color));
			computeVar (cimg, x, y, xp, yp, avgs, vars);
            
			if (checkVar(vars, threshold)) {
				process (cimg, x, y, xp, yp, offset / 2, threshold, picNodeList, refillList);
			}
            
			PicNode *picNode = nullptr;
			if (findProperPic (avgs, vars, &picNode, picNodeList) == -1) {
                return -1;
			}
            
			ReplaceInfo *replaceInfo = (ReplaceInfo*) malloc (sizeof(ReplaceInfo));
			memset(replaceInfo, 0, sizeof(ReplaceInfo));
			replaceInfo->xstart = x;
			replaceInfo->ystart = y;
			replaceInfo->xend = xp;
			replaceInfo->yend = yp;
			replaceInfo->pNext = NULL;
			replaceInfo->picNode = picNode;
			last->pNext = replaceInfo;
            
//            printf("begin cshou debug Last Node##############\n");
//            printNode(last);
//            printf("end cshou debug Last Node##############\n");
//            printNode(replaceInfo);
            
            last = replaceInfo;
            
			y += offset;
		}
		x += offset;
	}
    
	return 0;
}

void printNode (ReplaceInfo *pReplaceInfo) {
    printf("Using replacement...\n");
    printf("xstart = [%d]\n", pReplaceInfo->xstart);
    printf("ystart = [%d]\n", pReplaceInfo->ystart);
    printf("xend = [%d]\n", pReplaceInfo->xend);
    printf("yend = [%d]\n", pReplaceInfo->yend);
    printf("Pic Node path = [%s]\n", pReplaceInfo->picNode->path);
    printf("pNext = [%d]\n", pReplaceInfo->pNext);
}

// find the proper img according to average
int findProperPic (Color *avgs, Color *vars, PicNode** picNode, PicNodeList *picNodeList) {
	int i;
	double min = MAX_VALUE;
    
    //printf("Finding proper pic...\n");
    
	for (i = 0; i < picNodeList->numOfImgs; i++) {
		//printf("Original pic node path = %s\n", picNodeList->picNode[i].path);
        
        PicNode *pnode = &(picNodeList->picNode[i]);
        
        //printf("new pic node path = %s\n", pnode->path);
        
		double current = checkAvg(pnode, avgs);
		if (current < min) {
			min = current;
			*picNode = pnode;
		}
	}
    
	if (min == MAX_VALUE)
		return -1;
    
    //printf("returned pic node = [%s]", picNode->path);
    
    //printf("Finish finding proper pic...\n");
    
	return 0;
}

// compute the average sum of three color
double checkAvg (PicNode *picNode, Color *avgs) {
	double sum = 0;
	sum += abs(picNode->avg.rValue - avgs->rValue);
	sum += abs(picNode->avg.gValue - avgs->gValue);
	sum += abs(picNode->avg.bValue - avgs->bValue);
    
	return sum / 3;
}

// check the variance is less than threshold
bool checkVar (Color *vars, double threshold) {
    
	if (vars->rValue <= threshold &&
		vars->gValue <= threshold &&
		vars->bValue <= threshold) {
		return false;
	}
    
	return true;
    
}

void printRefillList (RefillList* pRefillList) {
    ReplaceInfo *info = pRefillList->head->pNext;
    while (info != NULL) {
        char *path = info->picNode->path;
        printf("%s\n", path);
        info = info->pNext;
    }
}

int repixel (char *path, PicNodeList* pPicNodeList, RefillList* pRefillList, int offset, double threshold) {
    
	Mat cimg = imread(path);
    
	ReplaceInfo *head = (ReplaceInfo *) malloc (sizeof(ReplaceInfo));
	memset(head, 0, sizeof(ReplaceInfo));
	head->pNext = NULL;
	pRefillList->head = head;
	last = head;
    
    //printf("Ready to process...\n");
    
	process(cimg, 0, 0, cimg.rows, cimg.cols, offset, threshold, pPicNodeList, pRefillList);
    
    //printf("Finish processing...\n");
    
    return 0;
}

