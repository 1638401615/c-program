
char* gettime()
{
   time_t rawtime;
   struct tm *info;
   char *buffer;
   buffer = (char*)malloc(sizeof(char)*80);
   time( &rawtime );
   info = localtime( &rawtime );
   strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", info);
   return buffer;
}
