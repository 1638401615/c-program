#include"stdio.h"
int main()
{
    FILE *fp = NULL;
    int a;
    char c , s[100] , buff[100];
    /*写入文件*/
    fp = fopen("D:\\abc.txt" , "w+");
    fprintf(fp,"hello world!--by fprintf\n");/*向文件中写入字符串可以用fprintf或者puts(fputc只能输入一个字符)*/
    fputs("hello world1--by puts\n",fp);
    fputc('o',fp);
    fclose(fp);
    /*读取文件*/
    fp = fopen("D:\\abc.txt" , "r+");/*无论是fscanf还是fgetc还是fgets用过后均会改变文件指针的位置，下一次使用不会从头开始读取，而是还未读取处开始读取*/
    fgets(s , 50 , fp);
    
    fscanf(fp,"%s",buff);
    printf("1:%s\n",buff);
    printf("2:%s",s);
    rewind(fp);/*使用rewind函数可以将文件指针复位，回到指向文件开头的位置*/
    c = fgetc(fp);
    printf("%c\n",c);
    c = fgetc(fp);
    printf("%c\n",c);
    fclose(fp);
    return 0;
}