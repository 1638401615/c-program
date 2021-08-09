#include<stdio.h>
#include<string.h>

char* ReplaceSubStr(const char* str, const char* srcSubStr, const char* dstSubStr, char* out)
{
    if (!str&&!out)
    {
        return NULL;
    }
    if (!srcSubStr && !dstSubStr)
    {
        return out;
    }
    char *out_temp = out;
    int src_len = strlen(srcSubStr);
    int dst_len = strlen(dstSubStr);
    while (*str!='\0')
    {
        if (*str == *srcSubStr)
        {
            //���ܷ����滻
            const char* str_temp = str;
            int flag = 0;
            for (int i = 0; i < src_len; i++)
            {
                if (str_temp[i]!=srcSubStr[i])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag)
            {
                //˵�������滻
                *out_temp++ = *str++;
            }
            else
            {
                //˵��Ҫ�滻
                for (int i = 0; i < dst_len; i++)
                {
                    *out_temp++ = dstSubStr[i];
                }
                str = str + src_len;
            }
        }
        else
        {
            //�����滻
            *out_temp++ = *str++;
        }
    }
    *out_temp = 0;
    return out;
}