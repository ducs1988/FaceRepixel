//
//  repixel.cpp
//  FaceRepixel
//
//  Created by Chenshi Du on 11/2/12.
//  Copyright (c) 2012 IIT. All rights reserved.
//

#include "fr.h"

#define MAX_VALUE 10000000000

PicNodeList* picNodeList;
RefillList* refillList;
ReplaceInfo* last;

int process (Mat &, int, int, int, int, int, double);
int findProperPic (Color*, Color*, PicNode*);
double checkAvg (PicNode*, Color*);
bool checkVar (Color*, double);
int repixel (char*, PicNodeList*, RefillList*, int, double);


// main process
int process (Mat &cimg, int xstart, int ystart, int xend, int yend, int offset, double threshold) {

	int x = xstart;
	int y = ystart;

	while (x < xend) {
		y = ystart;
		while (y < yend) {
			
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
				process (cimg, x, y, xp, yp, offset / 2, threshold);
			}

			PicNode *picNode = nullptr;
			if (findProperPic (avgs, vars, picNode) == -1) {
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

			y += offset;
		}
		x += offset;
	}

	return 0;
}

// find the proper img according to average
int findProperPic (Color *avgs, Color *vars, PicNode *picNode) {
	int i;
	double min = MAX_VALUE;

	for (i = 0; i < picNodeList->numOfImgs; i++) {
		PicNode *pnode = &(picNodeList->picNode[i]);
		double current = checkAvg(pnode, avgs);
		if (current < min) {
			min = current;
			picNode = pnode;
		}
	}

	if (min == MAX_VALUE)
		return -1;

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

int repixel (char *path, PicNodeList* pPicNodeList, RefillList* pRefillList, int offset, double threshold) {
    
	Mat cimg = imread(path);

	picNodeList = pPicNodeList;
	refillList = pRefillList;

	ReplaceInfo *head = (ReplaceInfo *) malloc (sizeof(ReplaceInfo));
	memset(head, 0, sizeof(ReplaceInfo));
	head->pNext = NULL;
	refillList->head = head;
	last = head;

	process(cimg, 0, 0, cimg.rows, cimg.cols, offset, threshold);

    return 0;
}

