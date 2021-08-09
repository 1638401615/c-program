#include<stdio.h>
#include<io.h>
void copy(char oldname[],char newname[])
{
    FILE *fp1,*fp2;
    char file[100];
    fp1 = NULL , fp2 = NULL;
    fp1 = fopen(oldname,"r");
    fp2 = fopen(newname,"w");
    if(fp1 != NULL)
    {
            while (!feof(fp1))
        {
            fgets(file,100,fp1);
            fputs(file,fp2);
        }
    }
    
    fclose(fp1);
    fclose(fp2);
}