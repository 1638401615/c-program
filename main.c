#include<stdio.h>
int i , j , n , count = 0;
int a[10001] , b[10001]; 
int check(int x)
{
	if(a[x - 1] + a[x] + a[x + 1] == b[x])
	{
		
		return 1;
	}
	return 0;
}
void dfs(int x)
{ 
	if(x == n+1)
	{
		if(check(n))
		count ++;
		return;
	}
	a[x] = 0;
	if(x == 1 || check(x - 1))
	dfs(x + 1);
	a[x] = 1;
	if(x == 1 || check(x - 1))
	dfs(x + 1);
}
int main()
{
	
	scanf("%d",&n);
	
	for(i = 1;i <= n;i++)
	scanf("%d",&b[i]);
	dfs(1);
	printf("%d",count);
	return 0;
}