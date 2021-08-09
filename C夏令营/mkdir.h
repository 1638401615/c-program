#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void mkdir()
{
char s[256] = "D:\\mygit\\.git";

//printf("请输入想要创建的文件夹路径");
//scanf("%s",s);
char b[]="md ";
system(strcat(b,s));

}