//��һ������substring���������ϵݹ�����������Ѱ�Ҹ����������
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char inorder[10];
char postorder[10];
//static char q[10]; 
char *substring(char *p , int i , int j)
{
    char *q;
    q = (char *)malloc(10 * sizeof(char));//����ÿ�����·����ַ�������������ÿ�ε��ö��Ƕ�ͬһ��q���иı䣬s1��s2��һģһ��������
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
//������ֱ�Ӹ�����ѧ��ϵ�ҵ����л��ֱ߽����dfs
/*
#include<stdio.h>
#include<string.h>
char s1[10];
char s2[10];
int len;
int find(char ch)//Ѱ�ҵ����ڵ������������е�λ�� 
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
    if(m>l1) /*����������*/
//	dfs(l1,m-1,l2,r2-r1+m-1);//r1-mΪ����������� 
//  if(m<r1) /*����������*/
//	dfs(m+1,r1,l2+m-l1,r2-1);//m-l1Ϊ�������ڵ���
//}
/*int main()
{
    scanf("%s",s1);
    scanf("%s",s2);
    len=strlen(s1);
    dfs(0,len-1,0,len-1);
}*/