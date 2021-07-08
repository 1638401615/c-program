#include<stdio.h>
int a[101] , n;
void quicksort(int left,int right)
{
    int i , j , t , tmp;
    tmp = a[left];
    i = left;
    j = right;
    if(left > right)
	return; 
    while(i < j)
    {
        while (a[j] >= tmp && i < j)
        {
            j--;
        }
        while(a[i] <= tmp && i < j)
        {
            i++;
        }
        if(i < j)/*i和j互换元素，把比较大的那个元素a[i]放在该放的位置上*/
        {
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    a[left] = a[i];/*把比较小的元素a[j]放在该放的位置上*/
    a[i] = tmp;/*把中间元素放在中间*/
    quicksort(left,i - 1);
    quicksort(i + 1,right);
    return;
}
int main()
{
    scanf("%d",&n);
    for(int i = 1;i <= n;i++)
    {
        scanf("%d",&a[i]);
    }
    quicksort(1,n);
    for(int i = 1;i <= n;i++)
    printf("%d ",a[i]);
    return 0;
}