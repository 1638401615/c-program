#include<stdio.h>


#include<string.h>
int dif(char filename1[],char filename2[])
{
    char file1[100],file2[100];
    FILE *fp1 = NULL;
    FILE *fp2 = NULL;
    fp1 = fopen(filename1,"r");
    fp2 = fopen(filename2,"r");
    while (!feof(fp1) && !feof(fp2))
    {
        fgets(file1,100,fp1);
        fgets(file2,100,fp2);
        if(strcmp(file1,file2) != 0)
        return 1;
    }
    if(!feof(fp1) || !feof(fp2))
    return 1;
    return 0;
}
void clean(char filename[])
{
    char workingpath[30] = "D:\\mygit\\working\\";
    char stagingpath[30] = "D:\\mygit\\staging\\";
    char localpath[30] = "D:\\mygit\\local\\";
    strcat(workingpath,filename);
    strcat(stagingpath,filename);
    strcat(localpath,filename);
    if(!fileexist(stagingpath) || !fileexist(localpath))
    remove(workingpath);
    else
    {
        if(dif(workingpath,localpath))
        {
            copy(localpath,workingpath);
            copy(localpath,stagingpath);
        }
    }
}