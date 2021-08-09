#include"stdio.h"
#include<string.h>
void diff(char filename1[],char filename2[])
{
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    char file1[100];
    char file2[100];
    int line = 0;
    fp1 = fopen(filename1 , "r");
    fp2 = fopen(filename2 , "r");
    if(fp1 == NULL || fp2 == NULL)
    {
         printf("有文件打开失败！\n");
        return;
    }
    while (!feof(fp1) && !feof(fp2))
    {
        fgets(file1,100,fp1);
        fgets(file2,100,fp2);
        line++;
        if(strcmp(file1,file2) != 0)
        printf("line %d :\n file1: %s \n file2: %s \n",line,file1,file2);
    }
    if(feof(fp1))
    {
        while (!feof(fp2))
        {
            fgets(file2,100,fp2);
            line++;
            printf("file2 增添部分：\nline %d : \n %s\n",line,file2);
        }
    }
    if(feof(fp2))
    {
        while (!feof(fp1))
        {
            fgets(file1,100,fp1);
            line++;
            printf("file1 增添部分：\nline %d : \n %s\n",line,file1);
        }
    }
    fclose(fp1);
    fclose(fp2);
    return;
}