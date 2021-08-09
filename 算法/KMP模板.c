#include<stdio.h>
#include<string.h>
int kmp[1000010];/*ʧ������*/
int main()
{
    int j = 0;
    char a[1000010];/*�ı���*/
    char b[1000010];/*ģʽ��*/
    scanf("%s",a+1);
    scanf("%s",b+1);
    int la = strlen(a+1);
    int lb = strlen(b+1);
    kmp[0] = kmp[1] = 0;
    for(int i = 2;i <= lb;i++)/*��ʼ��kmp���飬��ʵȫ�ֱ����Ѿ�Ĭ�ϳ�ʼ��Ϊ0���˴�ֻ��˵��*/
    {
        while(j && b[i] != b[j + 1])
        j = kmp[j];
        if(b[i] == b[j + 1])
        j++;
        kmp[i] = j;
    }
    j = 0;//ע�⽫j��ֵ���³�ʼ��������
    for(int i = 1;i <= la;i++)
    {
        while (j > 0 && a[i] != b[j + 1])
        {
            j = kmp[j];
        }
        if(a[i] == b[j + 1])
        j++;
        if(j == lb)
        {
            printf("%d\n",i - j + 1);
            j = kmp[j];//ƥ��ɹ���ģʽ�����������λ�ã�����Ѱ���µ�ƥ��
        }
    }
    for(int i = 1;i <= lb;i++)
    printf("%d ",kmp[i]);
    return 0;
}