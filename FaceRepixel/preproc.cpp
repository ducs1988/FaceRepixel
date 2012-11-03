//
//  preproc.cpp
//  FaceRepixel
//
//  Created by Chenshi Du on 11/2/12.
//  Copyright (c) 2012 IIT. All rights reserved.
//

#include <string.h>

#include "fr.h"

int testdir(char *path)  
{  
	struct stat buf;  
	if(lstat(path,&buf)<0)  
	{  
		return 0;  
	}  
	if(S_ISDIR(buf.st_mode))  
	{  
		return 1; //directory  
	}  
	return 0;  
}  


int setPicNodeList(char *path, PicNodeList* pPicNodeList)  
{  
	DIR *db;  
	int i=0;
	char filename[128];  
	struct dirent *p;
	db = opendir(path);  
	if(db == NULL)return 0;  
	memset(filename,0,128);  
	while ((p=readdir(db)))  
	{  
		if((strcmp(p->d_name,".")==0)||(strcmp(p->d_name,"..")==0)||p->d_name[0] == '.')
			continue;  
		else  
		{
            memset(filename, 0, 128);
			sprintf(filename, "%s/%s", path, p->d_name);
            
			if(testdir(filename) == 0)  //a file
			{
				memcpy(pPicNodeList->picNode[i].path, filename, strlen(filename));
                printf("%s\n", filename);
				/*if(computeAvgAndVar(filename, &(pPicNodeList->picNode[i].avg), &(pPicNodeList->picNode[i].var)) != 0){
					printf("Error in computeAvgAndVar(), filename[%s]\n", filename);  
					return -1;
				}*/
                i++;				
			}  
		}  
		 
	}  
	closedir(db);  
	return 0;  
}

int getFileNum(char *path, int* num)
{  
	DIR *db;
	char filename[128];
    int total = 0;
	
	struct dirent *p;  
	db = opendir(path);  
	if(db == NULL) return -1;  
	
	memset(filename,0,128);
	
	*num = 0;
	
	while ((p=readdir(db)))  
	{  
		if((strcmp(p->d_name,".")==0)||(strcmp(p->d_name,"..")==0)||p->d_name[0] == '.')
			continue;  
		else  
		{  
			sprintf(filename, "%s/%s", path, p->d_name);   
			if(testdir(filename) == 0)  //a file
			{  
				total ++;
				printf("%s\n", filename);
                //printf("%d\n", total);
			}
		}
	}
    *num = total;
    //printf("%d\n", *num);
	closedir(db);  
	return 0;  
}  

int preProc(PicNodeList* pPicNodeList, char* path){
	
	int iResult = -1;
	int num;
	
	//test if the path is a directory 
	if(access(path,F_OK) != 0 || testdir(path) == 0)  
	{  
		printf("[%s] is not a valid directory\n", path);  
		return -1;  
	}
	
	if(getFileNum(path, &num) != 0){
		printf("Error in getFileNum()\n");  
		return -1;
	}
	
	pPicNodeList->numOfImgs = num;
	
	pPicNodeList->picNode = (PicNode *)malloc(num*sizeof(PicNode));
	
	memset(pPicNodeList->picNode, 0, num*sizeof(PicNode));
	
	if(setPicNodeList(path, pPicNodeList) != 0){
		printf("Error in pPicNodeList()\n");
		free(pPicNodeList->picNode);
		return -1;
	}
    
    return 0;
}

void printPicNodeList(PicNodeList* pPicNodeList){
    
    printf("[%d]\n", pPicNodeList->numOfImgs);
    
    for(int i=0; i<pPicNodeList->numOfImgs; i++){
        printf("[%d][%s]\n", i, pPicNodeList->picNode[i].path);
    }
}