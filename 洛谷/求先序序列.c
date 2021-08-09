//法一：构造substring函数，不断递归左右子树，寻找各子树根结点
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char inorder[10];
char postorder[10];
//static char q[10]; 
char *substring(char *p , int i , int j)
{
    char *q;
    q = (char *)malloc(10 * sizeof(char));//必须每次重新分配地址！！！否则后面每次调用都是对同一个q进行改变，s1和s2会一模一样！！！
    int r = 0;
    for(int k = i;k < j;k++)
    q[r++] = p[k];
    q[r] = '\0';
    return q;
}
void func(char in[] , char after[])
{
    char ch;
    int len1 = strlen(in);
    int len2 = strlen(after);
    if(len1 > 0)
    {
        ch = after[len2 - 1];
        printf("%c",ch);
        int k;
        for(int i = 0;i < len1;i++)
        {
            if(in[i] == ch)
            {
                k = i;
                break;
            }
        }
        char *s1;
        char *s2;
        s1 = substring(in,0,k);
        s2 = substring(after,0,k);
        func(s1,s2);
        s1 = substring(in,k + 1,len1);
        s2 = substring(after,k,len2 - 1);
        func(s1,s2);
    }
    
}
int main()
{
    scanf("%s",inorder);
    scanf("%s",postorder);
    func(inorder,postorder);
    return 0;
}
/*
ACGDBHZKX
CDGAHXKZB
*/
//法二：直接根据数学关系找到序列划分边界进行dfs
/*
#include<stdio.h>
#include<string.h>
char s1[10];
char s2[10];
int len;
int find(char ch)//寻找到根节点在中序排列中的位置 
{
    for(int i=0;i<len;i++)
    {
        if(s1[i]==ch) return i;
    }
}
void dfs(int l1,int r1,int l2,int r2)
{
    int m=find(s2[r2]);
    printf("%c",s2[r2]);
    if(m>l1) /*具有左子树*/
//	dfs(l1,m-1,l2,r2-r1+m-1);//r1-m为右子树结点数 
//  if(m<r1) /*具有右子树*/
//	dfs(m+1,r1,l2+m-l1,r2-1);//m-l1为左子树节点数
//}
/*int main()
{
    scanf("%s",s1);
    scanf("%s",s2);
    len=strlen(s1);
    dfs(0,len-1,0,len-1);
}*/