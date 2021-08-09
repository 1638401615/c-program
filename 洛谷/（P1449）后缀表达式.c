#include<stdio.h>
int main()
{
    int s[1010];
    char c;
    int num = 0 , i = 0;
    while((c = getchar()) != '@')
    {
        if(c >= '0' && c <= '9')
        {
            num *= 10;
            num += (c - '0');
        }
        else if(c == '.')
        {
            s[++i] = num;
            num = 0;
        }
        else if(c == '+')
        {
            s[i - 1] = s[i - 1] + s[i];
            s[i] = 0;
            i--;
        }
        else if(c == '-')
        {
            s[i - 1] = s[i - 1] - s[i];
            s[i] = 0;
            i--;
        }
        else if(c == '*')
        {
            s[i - 1] = s[i - 1] * s[i];
            s[i] = 0;
            i--;
        }
        else if(c == '/')
        {
            s[i - 1] = s[i - 1] / s[i];
            s[i] = 0;
            i--;
        }
    }
    printf("%d",s[1]);

    return 0;
}