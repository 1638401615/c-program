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
        if(strcmp(command,"q") == 0) break;//当在新一行命令行中输入q，退出输入
        scanf("%s",action);
        if(strcmp(command,"git") != 0)
        {
            printf("命令行输入格式错误！\n");
            continue;
        }
        /*-------------------------对不同的action进行判断-------------------*/
        if(strcmp(action,"init") == 0)//git init
        {
            printf("将当前目录变成git可管理的仓库\n");
            continue;
        }
        else if(strcmp(action,"status") == 0)
        {
            printf("查看当前仓库状态\n");
            continue;
        }
        else if(strcmp(action,"add") == 0)//判断git add .和git add filename两种情况
        {
            scanf("%s",args);
            if(strcmp(args,".") == 0)
            printf("将当前目录下所有文件添加到仓库\n");
            else
            printf("将文件%s添加到仓库中\n",args);
            continue;
        }
        else if(strcmp(action,"diff") == 0)//文件比较
        {
            char file1[20];
            char file2[20];
            scanf("%s",file1);
            scanf("%s",file2);
            printf("比较文件%s和文件%s的区别\n",file1,file2);
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
                printf("提交文件到仓库，并附有说明：%s\n",args);
                else
                printf("提交文件到仓库，不附带说明\n");
                continue;
            }
        }
        else if(strcmp(action,"reset") == 0)//git reset [---mixed] [HEAD] 简单版本，所以只实现mixed，且必须敲出来。。。
        {
            scanf("%s",option);
            scanf("%s",args);
            if(strcmp(option,"--mixed") == 0)
            {
                if(strcmp(args,"HEAD^") == 0 || strcmp(args,"HEAD~1") == 0)//多个版本回退就一个个退吧（
                printf("回退所有内容到到上一个版本\n");
                else if(strcmp(args,"HEAD") == 0)
                printf("取消已缓存的内容\n");
                else
                printf("回退到指定版本：%s\n",args);
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
                printf("强行从暂存区和工作区中删除修改后的 %s 文件\n",args);
                continue;
            }
            else if(strcmp(tmp,"--cached") == 0)//git rm --cached filename
            {
                strcpy(option,tmp);
                scanf("%s",args);
                printf("仅从暂存区中删除 %s 文件\n",args);
                continue;
            }
            else//git rm filename
            {
                strcpy(args,tmp);
                printf("从暂存区和工作区中删除 %s 文件\n",args);
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
                printf("强制移动或者重命名文件 %s 到 %s\n",file,newfile);
                continue;
            }
            else//git mv file newfile
            {
                char file[20];
                char newfile[20];
                strcpy(file,tmp);
                scanf("%s",newfile);
                printf("移动或者重命名文件 %s 到 %s\n",file,newfile);
                continue;
            }
        }
        
        printf("命令行输入格式错误！\n");
    }
    
    return 0;
}