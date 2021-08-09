int hash(char s[])
{
    char *p;
    int h = 0;
    for(p = s;*p;p++)
    {
        h = h*3 + *p;
    }
    return h;
}