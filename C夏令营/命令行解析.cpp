#include<stdio.h>
#include<string.h>
char command[10];
char action[10];
char option[10];
char args[100];
int main()
{
    while (1)
    {
        scanf("%s",command);
        if(strcmp(command,"q") == 0) break;//������һ��������������q���˳�����
        scanf("%s",action);
        if(strcmp(command,"git") != 0)
        {
            printf("�����������ʽ����\n");
            continue;
        }
        /*-------------------------�Բ�ͬ��action�����ж�-------------------*/
        if(strcmp(action,"init") == 0)//git init
        {
            printf("����ǰĿ¼���git�ɹ���Ĳֿ�\n");
            continue;
        }
        else if(strcmp(action,"status") == 0)
        {
            printf("�鿴��ǰ�ֿ�״̬\n");
            continue;
        }
        else if(strcmp(action,"add") == 0)//�ж�git add .��git add filename�������
        {
            scanf("%s",args);
            if(strcmp(args,".") == 0)
            printf("����ǰĿ¼�������ļ���ӵ��ֿ�\n");
            else
            printf("���ļ�%s��ӵ��ֿ���\n",args);
            continue;
        }
        else if(strcmp(action,"diff") == 0)//�ļ��Ƚ�
        {
            char file1[20];
            char file2[20];
            scanf("%s",file1);
            scanf("%s",file2);
            printf("�Ƚ��ļ�%s���ļ�%s������\n",file1,file2);
            continue;
        }
        else if(strcmp(action,"commit") == 0)//git commit -m "xxxx"
        {
            scanf("%s",option);
            scanf("%s",args);
            int len = strlen(args);

            if(strcmp(option,"-m") == 0 && args[0] == '\"' && args[len-1] == '\"')
            {
                if(len > 2)
                printf("�ύ�ļ����ֿ⣬������˵����%s\n",args);
                else
                printf("�ύ�ļ����ֿ⣬������˵��\n");
                continue;
            }
        }
        else if(strcmp(action,"reset") == 0)//git reset [---mixed] [HEAD] �򵥰汾������ֻʵ��mixed���ұ����ó���������
        {
            scanf("%s",option);
            scanf("%s",args);
            if(strcmp(option,"--mixed") == 0)
            {
                if(strcmp(args,"HEAD^") == 0 || strcmp(args,"HEAD~1") == 0)//����汾���˾�һ�����˰ɣ�
                printf("�����������ݵ�����һ���汾\n");
                else if(strcmp(args,"HEAD") == 0)
                printf("ȡ���ѻ��������\n");
                else
                printf("���˵�ָ���汾��%s\n",args);
                continue;
            }
        }
        else if(strcmp(action,"rm") == 0)
        {
            char tmp[20];
            scanf("%s",tmp);
            if(strcmp(tmp,"-f") == 0)//git rm -f filename
            {
                strcpy(option,tmp);
                scanf("%s",args);
                printf("ǿ�д��ݴ����͹�������ɾ���޸ĺ�� %s �ļ�\n",args);
                continue;
            }
            else if(strcmp(tmp,"--cached") == 0)//git rm --cached filename
            {
                strcpy(option,tmp);
                scanf("%s",args);
                printf("�����ݴ�����ɾ�� %s �ļ�\n",args);
                continue;
            }
            else//git rm filename
            {
                strcpy(args,tmp);
                printf("���ݴ����͹�������ɾ�� %s �ļ�\n",args);
                continue;
            }
        }
        else if (strcmp(action,"mv") == 0)
        {
            char tmp[20];
            scanf("%s",tmp);
            if(strcmp(tmp,"-f") == 0)//git mv -f file newfile
            {
                char file[20];
                char newfile[20];
                scanf("%s",file);
                scanf("%s",newfile);
                printf("ǿ���ƶ������������ļ� %s �� %s\n",file,newfile);
                continue;
            }
            else//git mv file newfile
            {
                char file[20];
                char newfile[20];
                strcpy(file,tmp);
                scanf("%s",newfile);
                printf("�ƶ������������ļ� %s �� %s\n",file,newfile);
                continue;
            }
        }
        
        printf("�����������ʽ����\n");
    }
    
    return 0;
}