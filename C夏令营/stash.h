#include<stdio.h>


#include<string.h>
int difs(char filename1[],char filename2[])
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
void stash(char filename[])
{
    char workingpath[30] = "D:\\mygit\\working\\";
    char stagingpath[30] = "D:\\mygit\\staging\\";
    char localpath[30] = "D:\\mygit\\local\\";
    char savepath[50] = "D:\\mygit\\.git\\stash\\";
    strcat(workingpath,filename);
    strcat(stagingpath,filename);
    strcat(localpath,filename);
    strcat(savepath,filename);
    if(!fileexist(stagingpath) || !fileexist(localpath))
    {
        copy(workingpath,savepath);//把当前做出的修改保存到stash文件夹中
        remove(workingpath);
        
    }
    else if(difs(workingpath,localpath))
    {
        copy(workingpath,savepath);//把当前做出的修改保存到stash文件夹中
        copy(localpath,workingpath);
        copy(localpath,stagingpath);
    }
    
}