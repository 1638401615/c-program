#include<stdio.h>
int fileexist(char filename[])
{
    int flag = 1;
    FILE *fp = NULL;
    fp = fopen(filename,"r");
    if(fp == NULL)
    flag = 0;
    fclose(fp);
    return flag;
}