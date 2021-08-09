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
         printf("���ļ���ʧ�ܣ�\n");
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
        if(strcmp(file1,file2) != 0)//���޸�λ�ú���Ϣд�����ݽṹ��
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
            
            info[i].line[++j] = line;//��ԭ�汾�����Ϣ�������������ڻ���
            strcpy(info[i].revise[line],file2);
        }
    }
    if(feof(fp2))
    {
        while (!feof(fp1))
        {
            fgets(file1,100,fp1);
            line++;
            //printf("file1 �����֣�\nline %d : \n %s\n",line,file1);
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
            if(strcmp(command,"q") == 0) break;//������һ��������������q���˳�����
            if(strcmp(command,"touch") == 0)//touch filename
            {
                char workingpath[30] = "D:\\mygit\\working\\"; 
                scanf("%s",args);
                strcat(workingpath,args);
                FILE *f = NULL;
                f = fopen(workingpath,"w");
                fclose(f);
                strcpy(info[++filenum].file,workingpath);//Ϊ�����½��ļ����м�¼
                info[filenum].type = 0;
                continue;
            } 
            printf("�����������ʽ����\n");
            continue;
        }
        scanf("%s",action);
        /*-------------------------�Բ�ͬ��action�����ж�-------------------*/
        if(strcmp(action,"init") == 0)//git init .git�ļ���·��
        {
            mkdir();
            //printf("����ǰĿ¼���git�ɹ���Ĳֿ�\n");
            system("md D:\\mygit\\.git\\stash");
            continue;
        }
        else if(strcmp(action,"status") == 0)
        {
            for(int i = 1;i <= filenum;i++)
            {
                if(info[i].type == 0)
                printf("�½���%s\n",info[i].file);
                if(info[i].type == 1)
                printf("�޸ģ�%s\n",info[i].file);
                if(info[i].type == 2)
                printf("ɾ����%s\n",info[i].file);
            }
            //printf("�鿴��ǰ�ֿ�״̬\n");
            continue;
        }
        else if(strcmp(action,"add") == 0)//git add filename
        {
            char stagingpath[30] = "D:\\mygit\\staging\\";
            char workingpath[30] = "D:\\mygit\\working\\";
            scanf("%s",args);//filename

            strcat(workingpath,args);//�������ļ�·��
            strcat(stagingpath,args);//�ݴ����ļ�·��
            if(!fileexist(workingpath))//���������޴��ļ����
            {
                remove(stagingpath);
                for(int i = 1;i <= filenum;i++)
                {
                    if(strcmp(info[i].file,workingpath) == 0)
                    info[i].type = 2;
                }
            }
            else if(!fileexist(stagingpath))//�ݴ�����û��ӹ����ļ����
            {
                copy(workingpath,stagingpath);
            }
            else//�ݴ����Ѿ���ӹ����ļ����
            {
                differ(workingpath,stagingpath);//��¼�޸�ǰ�����ݣ���������
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
        
            //printf("�Ƚ��ļ�%s���ļ�%s������\n",file1,file2);
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
                
                copy(localpath,savepath);//�ڱ��زֿ������һ���汾������£��Ȱ���һ���汾���ļ����浽.git�ļ�������ȥ
                h = hash((strcat(gettime(),args)));//��ϣ����,���˸�ʱ�������Ψһ��
                if(!fileexist(stagingpath))//�ļ���ɾ�����
                {
                    remove(localpath);
                }
                else
                copy(stagingpath,localpath);//�ݴ����ļ��ύ�����زֿ�
                FILE *fp;
                fp = NULL;
                fp = fopen("D:\\mygit\\.git\\info.txt","a+");//��¼�ύ
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
                remove(workingpath) , remove(stagingpath);//ͬʱȥ�ݴ����͹�����ɾ����ͬĿ¼�µ���ͬ�ļ�
                //printf("ǿ�д��ݴ����͹�������ɾ���޸ĺ�� %s �ļ�\n",args);
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
                //printf("�����ݴ�����ɾ�� %s �ļ�\n",args);
                continue;
            }
            else//git rm filename
            {
                char stagingpath[30] = "D:\\mygit\\staging\\";
                char workingpath[30] = "D:\\mygit\\working\\";
                strcpy(args,tmp);//args������ǹ��������ļ���
                strcat(workingpath,args);
                strcat(stagingpath,args);
                remove(workingpath) , remove(stagingpath);
                //printf("���ݴ����͹�������ɾ�� %s �ļ�\n",args);
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
                for(int i = 1;i <= filenum;i++)//�Ѽ�¼��Ϣ�����ݽṹ��file���ָ���
                {
                    if(strcmp(info[i].file,workingpath) == 0)
                    strcpy(info[i].file,newpath);
                }
                //printf("ǿ���ƶ������������ļ� %s �� %s\n",file,newfile);
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
                //printf("�ƶ������������ļ� %s �� %s\n",file,newfile);
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
            if(strcmp(option,"apply") == 0)//git stash apply filename�������ļ��ָ��޸�
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
        printf("�����������ʽ����\n");
    }
    return 0;
}