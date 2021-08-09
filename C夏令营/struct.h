typedef struct 
{
    char file[30];//文件路径
    int type;//0:新增文件 1:修改文件 2:删除文件 3:正常状态
    int line[100];//修改的行
    char revise[100][100];//修改前的内容,第一个框内表示第几行
}information;
