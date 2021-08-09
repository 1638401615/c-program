#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<io.h>
#include"gettime.h"
#include"diff.h"
#include"copy.h"
#include"hash.h"
#include"mkdir.h"
#include"exist.h"
#include"struct.h"
#include"replacesubstr.h"
#include"clean.h"
#include"stash.h"
//#include"differ.h"
//#include"rework.h"
char command[10];
char action[10];
char option[10];
char args[100];
int filenum = 0;
information info[100]; 
void rework(char filename[])
{
    char workingpath[100] , savepath[100];
    ReplaceSubStr(filename,"local","working",workingpath);
    ReplaceSubStr(filename,"local",".git",savepath);
    for(int i = 1;i <= filenum;i++)
    {
        if(strcmp(info[i].file,workingpath) == 0)
        {
            if(info[i].type == 0)
            {
                remove(filename);
            }
            if(info[i].type == 1 || info[i].type == 2)
            {
                copy(savepath,filename);
            }
            break;
        }
    }
}
void differ(char filename1[],char filename2[])
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
    int i , j  = 0, k = 0;
    for(i = 1;i <= filenum;i++)
    {
        if(strcmp(info[i].file,file1) == 0)
        break;
    }
    while (!feof(fp1) && !feof(fp2))
    {
        fgets(file1,100,fp1);
        fgets(file2,100,fp2);
        line++;
        if(strcmp(file1,file2) != 0)//把修改位置和信息写入数据结构中
        {
            
            info[i].line[++j] = line;
            strcpy(info[i].revise[line],file2);
        }
    }
    if(feof(fp1))
    {
        while (!feof(fp2))
        {
            fgets(file2,100,fp2);
            line++;
            
            info[i].line[++j] = line;//把原版本多的信息保存下来，用于回溯
            strcpy(info[i].revise[line],file2);
        }
    }
    if(feof(fp2))
    {
        while (!feof(fp1))
        {
            fgets(file1,100,fp1);
            line++;
            //printf("file1 增添部分：\nline %d : \n %s\n",line,file1);
        }
    }
    fclose(fp1);
    fclose(fp2);
    return;
}
int main()
{
    while (1)
    {
        scanf("%s",command);
        if(strcmp(command,"git") != 0)
        {
            if(strcmp(command,"q") == 0) break;//当在新一行命令行中输入q，退出输入
            if(strcmp(command,"touch") == 0)//touch filename
            {
                char workingpath[30] = "D:\\mygit\\working\\"; 
                scanf("%s",args);
                strcat(workingpath,args);
                FILE *f = NULL;
                f = fopen(workingpath,"w");
                fclose(f);
                strcpy(info[++filenum].file,workingpath);//为所有新建文件进行记录
                info[filenum].type = 0;
                continue;
            } 
            printf("命令行输入格式错误！\n");
            continue;
        }
        scanf("%s",action);
        /*-------------------------对不同的action进行判断-------------------*/
        if(strcmp(action,"init") == 0)//git init .git文件夹路径
        {
            mkdir();
            //printf("将当前目录变成git可管理的仓库\n");
            system("md D:\\mygit\\.git\\stash");
            continue;
        }
        else if(strcmp(action,"status") == 0)
        {
            for(int i = 1;i <= filenum;i++)
            {
                if(info[i].type == 0)
                printf("新建：%s\n",info[i].file);
                if(info[i].type == 1)
                printf("修改：%s\n",info[i].file);
                if(info[i].type == 2)
                printf("删除：%s\n",info[i].file);
            }
            //printf("查看当前仓库状态\n");
            continue;
        }
        else if(strcmp(action,"add") == 0)//git add filename
        {
            char stagingpath[30] = "D:\\mygit\\staging\\";
            char workingpath[30] = "D:\\mygit\\working\\";
            scanf("%s",args);//filename

            strcat(workingpath,args);//工作区文件路径
            strcat(stagingpath,args);//暂存区文件路径
            if(!fileexist(workingpath))//工作区已无此文件情况
            {
                remove(stagingpath);
                for(int i = 1;i <= filenum;i++)
                {
                    if(strcmp(info[i].file,workingpath) == 0)
                    info[i].type = 2;
                }
            }
            else if(!fileexist(stagingpath))//暂存区还没添加过该文件情况
            {
                copy(workingpath,stagingpath);
            }
            else//暂存区已经添加过该文件情况
            {
                differ(workingpath,stagingpath);//记录修改前的内容，保存下来
                copy(workingpath,stagingpath);
                for(int i = 1;i <= filenum;i++)
                {
                    if(strcmp(info[i].file,workingpath) == 0)
                    info[i].type = 1;
                }
            }
            
            continue;
        }
        else if(strcmp(action,"diff") == 0)//git diff path1 path2
        {
            char filename1[30];
            char filename2[30];
            scanf("%s",filename1);
            scanf("%s",filename2);
        
            //printf("比较文件%s和文件%s的区别\n",file1,file2);
            diff(filename1,filename2);
            continue;
        }
        else if(strcmp(action,"commit") == 0)//git commit filename  -m "xxxx"
        {
            char filename[30];
            char stagingpath[30] = "D:\\mygit\\staging\\";
            char workingpath[30] = "D:\\mygit\\working\\";
             char localpath[30] = "D:\\mygit\\local\\";
            scanf("%s",filename);
            strcat(stagingpath,filename);
            strcat(localpath,filename);
            scanf("%s",option);
            scanf("%s",args);
            int len = strlen(args);
            
            if(strcmp(option,"-m") == 0 && args[0] == '\"' && args[len-1] == '\"')
            {
                int h;
                char savepath[100];
                ReplaceSubStr(localpath,"local",".git",savepath);
                
                copy(localpath,savepath);//在本地仓库存在上一个版本的情况下，先把上一个版本的文件保存到.git文件夹里面去
                h = hash((strcat(gettime(),args)));//哈希生成,加了个时间戳保障唯一性
                if(!fileexist(stagingpath))//文件被删除情况
                {
                    remove(localpath);
                }
                else
                copy(stagingpath,localpath);//暂存区文件提交到本地仓库
                FILE *fp;
                fp = NULL;
                fp = fopen("D:\\mygit\\.git\\info.txt","a+");//记录提交
                fprintf(fp,"%d commit %s\n Date:%s\n Author:mingmingchen\n",h,args,gettime());
                fclose(fp);
                continue;
            }
        }
        else if(strcmp(action,"reset") == 0)//git reset head^/head~1 filename 
        {
            char localpath[30] = "D:\\mygit\\local\\";
            scanf("%s",args);
            if(strcmp(args,"head^") == 0 || strcmp(args,"head~1") == 0)
            {
                char filename[30];
                scanf("%s",filename);
                strcat(localpath,filename);
                rework(localpath);
                continue;
            }
        }
        else if(strcmp(action,"rm") == 0)
        {
            char tmp[30];
            scanf("%s",tmp);
            if(strcmp(tmp,"-f") == 0)//git rm -f filename
            {
                char stagingpath[30] = "D:\\mygit\\staging\\";
                char workingpath[30] = "D:\\mygit\\working\\";
                char localpath[30] = "D:\\mygit\\local\\";
                strcpy(option,tmp);
                scanf("%s",args);//filename
                strcat(workingpath,args);
                strcat(localpath,args);
                remove(workingpath) , remove(stagingpath);//同时去暂存区和工作区删除不同目录下的相同文件
                //printf("强行从暂存区和工作区中删除修改后的 %s 文件\n",args);
                for(int i = 1;i <= filenum;i++)
                {
                    if(strcmp(info[i].file,workingpath) == 0)
                    {
                        info[i].type = 2;
                    }
                }
                continue;
            }
            else if(strcmp(tmp,"--cached") == 0)//git rm --cached filename(stagingpath)
            {
                char stagingpath[30] = "D:\\mygit\\staging\\";
                char workingpath[30] = "D:\\mygit\\working\\";
                strcpy(option,tmp);
                scanf("%s",args);//filename
                strcat(stagingpath,args);
                remove(stagingpath);
                //printf("仅从暂存区中删除 %s 文件\n",args);
                continue;
            }
            else//git rm filename
            {
                char stagingpath[30] = "D:\\mygit\\staging\\";
                char workingpath[30] = "D:\\mygit\\working\\";
                strcpy(args,tmp);//args储存的是工作区的文件名
                strcat(workingpath,args);
                strcat(stagingpath,args);
                remove(workingpath) , remove(stagingpath);
                //printf("从暂存区和工作区中删除 %s 文件\n",args);
                for(int i = 1;i <= filenum;i++)
                {
                    if(strcmp(info[i].file,workingpath) == 0)
                    {
                        info[i].type = 2;
                    }
                }
                continue;
            }
        }
        else if (strcmp(action,"mv") == 0)
        {
            char stagingpath[30] = "D:\\mygit\\staging\\";
            char workingpath[30] = "D:\\mygit\\working\\";
            char tmp[20];
            scanf("%s",tmp);
            if(strcmp(tmp,"-f") == 0)//git mv -f file newfile
            {
                
                char file[20];
                char newfile[20];
                scanf("%s",file);
                scanf("%s",newfile);
                char newpath[30] = "D:\\mygit\\working\\";
                strcat(workingpath,file);
                strcat(newpath,newfile);
                rename(workingpath,newpath);
                for(int i = 1;i <= filenum;i++)//把记录信息的数据结构的file名字更新
                {
                    if(strcmp(info[i].file,workingpath) == 0)
                    strcpy(info[i].file,newpath);
                }
                //printf("强制移动或者重命名文件 %s 到 %s\n",file,newfile);
                continue;
            }
            else//git mv file newfile
            {
                char file[20];
                char newfile[20];
                strcpy(file,tmp);
                scanf("%s",newfile);
                char newpath[30] = "D:\\mygit\\working\\";
                strcat(workingpath,file);
                strcat(newpath,newfile);
                rename(workingpath,newpath);
                for(int i = 1;i <= filenum;i++)
                {
                    if(strcmp(info[i].file,workingpath) == 0)
                    strcpy(info[i].file,newpath);
                }
                //printf("移动或者重命名文件 %s 到 %s\n",file,newfile);
                continue;
            }
        }
        else if(strcmp(action,"log") == 0)
        {
            FILE *fpin;
            char logs[100];
            fpin = fopen("D:\\mygit\\.git\\info.txt","r");
            fgets(logs,100,fpin);
            while (!feof(fpin))
            {
                printf("%s\n",logs);
                fgets(logs,100,fpin);
            }
            
            fclose(fpin);
            continue;
        }
        else if(strcmp(action,"clean") == 0)//git clean filename
        {
            char filename[30];
            scanf("%s",filename);
            clean(filename);
            continue;
        }
        else if(strcmp(action,"stash") == 0)
        {
            char filename[30];
            char workingpath[30] = "D:\\mygit\\working\\";
            char stagingpath[30] = "D:\\mygit\\staging\\";
            char localpath[30] = "D:\\mygit\\local\\";
            scanf("%s",option);
            if(strcmp(option,"apply") == 0)//git stash apply filename工作区文件恢复修改
            {
                scanf("%s",filename);
                strcat(workingpath,filename);
                char savepath[50] = "D:\\mygit\\.git\\stash\\";
                strcat(savepath,filename);
                copy(savepath,workingpath);
                copy(savepath,stagingpath);
                continue;
            }
            else//git stash filename
            {
                strcpy(filename,option);
                stash(filename);
                continue;
            }
        }
        else if(strcmp(action,"save") == 0)//git save
        {
            FILE *fps = NULL;
            fps = fopen("D:\\mygit\\.git\\status.txt","w");
            for(int i = 1;i <= filenum;i++)
            {
                fprintf(fps,"%s\n",info[i].file);
                fprintf(fps,"%d\n",info[i].type);
            }
            fclose(fps);
            continue;
        }
        else if(strcmp(action,"load") == 0)//git load
        {
            FILE *fpl = NULL;
            fpl = fopen("D:\\mygit\\.git\\status.txt","r");
            int k = 1;
            fscanf(fpl,"%s",info[k].file);
            fscanf(fpl,"%d",&info[k].type);
            while(!feof(fpl))
            {
                k++;
                fscanf(fpl,"%s",info[k].file);
                fscanf(fpl,"%d",&info[k].type);
            }
            filenum = k - 1;
            fclose(fpl);
            continue;
        }
        printf("命令行输入格式错误！\n");
    }
    return 0;
}