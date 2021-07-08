#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
FILE *fp;
char FileName[30];
int x;
typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //��������ʽ�ṹ�����Ķ���
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
typedef struct{  //���Ա�Ĺ������
     struct { char name[30];
     		  LinkList L;	
      } elem[10];
      int length;
      int listsize;
 }LISTS;
 LinkList L;
 LISTS Lists;
/*-----------------------------------������������--------------------------------------------*/
status InitList(LinkList& L);                             
status DestroyList(LinkList& L);
status ClearList(LinkList& L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
int LocateElem(LinkList L,ElemType e);
status PriorElem(LinkList L,ElemType e,ElemType &pre);
status NextElem(LinkList L,ElemType e,ElemType &next);
status ListInsert(LinkList &L,int i,ElemType e);
status ListDelete(LinkList &L,int i,ElemType &e);
status ListTraverse(LinkList L);
status  SaveList(LinkList L,char FileName[]);
status  LoadList(LinkList &L,char FileName[]);
status AddList(LISTS &Lists,char ListName[]);
status RemoveList(LISTS &Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);
/*------------------------------------����������---------------------------------------------*/
int main()
{
    strcpy(FileName,"d:\\abc.txt");
    int i , j , e , pre , next;
	Lists.length = 0;  
    int op=1;
    while(op){
	system("cls");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. InitList       10. ListInsert\n");
	printf("    	  2. DestroyList    11. ListDelete\n");
	printf("    	  3. ClearList      12. ListTrabverse\n");
	printf("    	  4. ListEmpty      13. SaveList\n");
	printf("    	  5. ListLength     14. LoadList\n");
	printf("    	  6. GetElem        15. AddList\n");
    printf("    	  7. LocateElem     16. RemoveList\n");
    printf("    	  8. PriorElem      17.LocateList\n");
	printf("    	  9. NextElem       18.changeList\n");
	printf("          0.exit"); 
	printf("-------------------------------------------------\n");
	printf("    ��ѡ����Ĳ���[0~18]:");
	scanf("%d",&op);
    switch(op){
	   case 1:
		 if(InitList(L)==OK) 
         printf("���Ա����ɹ���\n");
		 else 
         printf("���Ա���ʧ�ܣ�\n");
         getchar();getchar();
         break;
	   case 2:
		 if(DestroyList(L) == OK)
         printf("���Ա�ɾ���ɹ���\n");
         else
         printf("���Ա�ɾ��ʧ�ܣ������Ƿ�������Ա�\n");
		 getchar();getchar();
		 break;
	   case 3:
		 if(ClearList(L) == OK)
         printf("���Ա���ճɹ���\n");
         else
         printf("���Ա����ʧ�ܣ������Ƿ�������Ա�\n");     
		 getchar();getchar();
		 break;
	   case 4:
		 if(ListEmpty(L) == TRUE)
         printf("���Ա�Ϊ�գ�\n");
         else if(ListEmpty(L) == FALSE)
         printf("���Ա�Ϊ�գ�\n");
         else
         printf("���Ա����ڣ�\n");     
		 getchar();getchar();
		 break;
	   case 5:
		 int len;
         len =  ListLength(L);
         if(len == INFEASIBLE)
         printf("���Ա�����ȡʧ�ܣ������Ƿ�������Ա�\n");
         else
         printf("���Ա���Ϊ��%d\n",len);    
		 getchar();getchar();
		 break;
	   case 6:
         scanf("%d",&i);
		 j=GetElem(L,i,e);
         if(j == INFEASIBLE)
         printf("���Ա����ڣ�\n");
         else if(j == ERROR)    
         printf("����λ�ò��Ϸ���\n");
         else
         printf("%d����ȡ��Ԫ��Ϊ��%d",i,e);
		 getchar();getchar();
		 break;
	   case 7:
         scanf("%d",&e);
		 j = LocateElem(L,e);     
		 if(j == INFEASIBLE)
         printf("���Ա����ڣ�\n");
         else if(j == ERROR)
         printf("����ʧ�ܣ����Ա��в�����ֵΪ%d��Ԫ�أ�\n",e);
         else
         printf("���Ա��� %d ���ڵ�λ���ǣ�%d\n",e,j);
         getchar();getchar();
		 break;
	   case 8:
         int pre; 
		 scanf("%d",&e);
		 j = PriorElem(L,e,pre);
         if(j == INFEASIBLE)
         printf("���Ա����ڣ�\n");    
         else if(j == ERROR)
         printf("û���ҵ�ָ��Ԫ��%d��ǰ��Ԫ�أ�����ʧ�ܣ�\n",e);
         else
         printf("Ԫ�� %d ��ǰ��Ԫ���ǣ�%d\n",e,pre);
		 getchar();getchar();
		 break;
	   case 9:
	   	 int next;
	   	 scanf("%d",&e);
	   	 j = NextElem(L,e,next);
	   	 if(j == INFEASIBLE)
         printf("���Ա����ڣ�\n");    
         else if(j == ERROR)
         printf("û���ҵ�ָ��Ԫ��%d�ĺ��Ԫ�أ�����ʧ�ܣ�\n",e);
         else
         printf("Ԫ�� %d �ĺ��Ԫ���ǣ�%d\n",e,next);    
		 getchar();getchar();
		 break;
	   case 10:
		 scanf("%d%d",&i,&e);
         j = ListInsert(L,i,e);  
         if(j == INFEASIBLE)
         printf("���Ա����ڣ�\n");
         else if(j == ERROR)
         printf("����Ԫ��ʧ��!�������λ��ѡ���Ƿ���ȷ��\n");
         else
         {
         	printf("Ԫ�ز���ɹ���\n");
         	
		 }
		 getchar();getchar();
		 break;
	   case 11:
		 scanf("%d",&i);
		 j=ListDelete(L,i,e); 
         if(j == INFEASIBLE)
         printf("���Ա����ڣ�\n");
         else if(j == ERROR)
         printf("ɾ��Ԫ��ʧ��!����ɾ��λ��ѡ���Ƿ���ȷ��\n");   
         else
         printf("Ԫ�� %d �ѱ��ɹ�ɾ����\n",e); 
		 getchar();getchar();
		 break;
	   case 12:
		 j=ListTraverse(L);
         if(j == INFEASIBLE)
         printf("���Ա����ڣ�\n");
         else if(j==OK && !L -> next) 
         printf("���Ա��ǿձ�\n");    
		 
		getchar();getchar();
		 break;
       case 13:
         j=SaveList(L,FileName);
         if(j == INFEASIBLE)
         printf("���Ա����ڣ�\n");
         else
         printf("���ݳɹ������ļ���\n");  
         getchar();getchar();
         break;
       case 14:
         j=LoadList(L,FileName);
         if(j == INFEASIBLE)
         printf("���Ա��Ѵ��ڣ�����ʧ�ܣ�\n");
         else
         printf("�ɹ������ļ����ݣ�\n");  
         getchar();getchar();
         break;
       case 15: 
         char name[30];
         scanf("%s",name);
         j = AddList(Lists,name);
         if(j)
         printf("���Ա����ӳɹ���\n");
         getchar();getchar();
         break;
       case 16:
         char name1[30];
         scanf("%s",name1);
         j = RemoveList(Lists,name1);
         if(j == OK)
         printf("���Ա� %s ɾ���ɹ���\n",name1);
         else
         printf("��������Ϊ %s �����Ա�ɾ��ʧ�ܣ�\n",name1);
		 getchar();getchar();
         break;
       case 17:
       	 char name2[30];
       	 scanf("%s",name2);
       	 j = LocateList(Lists,name2);
       	 if(j != 0)
       	 {
       	 	printf("���Ա� %s ��Lists�е�λ���ǣ�%d\n",name2,j);
       	 	
			}
       	 else
       	 printf("Lists��û����Ϊ %s �����Ա�\n",name2);
         getchar();getchar(); 
         break;
        case 18:
		 char name3[30];
		 scanf("%s",name3);
		 x = LocateList(Lists,name3);
		 if(x != 0)
		 {
		 	printf("�ѳɹ��л��� %s ���Ա�\n",name3);
		 	L = Lists.elem[x - 1].L;/*�л���ȥ�������ݾ�����*/ 
		 	
		  }  
		  else
		  printf("Lists��û����Ϊ %s �����Ա�\n",name3);
		  getchar();getchar();
	   case 0:
         break;
	}//end of switch
  }//end of while
printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}
/*-------------------------------------�������岿��-------------------------------------------*/
status InitList(LinkList &L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(L)
    return INFEASIBLE;
    else
    {
        L = (LinkList)malloc(sizeof(LNode));
        L -> next = NULL;
        return OK;
    }
    /********** End **********/
}
status DestroyList(LinkList &L)
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(L)
    {
        free(L);
        L = NULL;
        return OK;
    }
    else
    return INFEASIBLE;
    /********** End **********/
}

status ClearList(LinkList &L)
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    else
    {
        free(L -> next);
        L -> next = NULL;
        return OK;
    }
    /********** End **********/
}
status ListEmpty(LinkList L)
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    if(L -> next == NULL)
    return TRUE;
    else
    return FALSE;
    /********** End **********/
}
int ListLength(LinkList L)
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    int length = 0;
    LinkList p = L -> next;
    while(p)
    {
        length++;
        p = p -> next;
    }
    return length;
    /********** End **********/
}
status GetElem(LinkList L,int i,ElemType &e)
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p = L -> next;
    if(i < 1)
    return ERROR;
    while(p)
    {
        i--;
        if(i == 0)
        {
            e = p -> data;
            return OK;
        }
        p = p -> next;
    }
    return ERROR;
    /********** End **********/
}
status LocateElem(LinkList L,ElemType e)
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p = L -> next;
    int i = 0;
    while(p)
    {
        i++;
        if(p -> data == e)
        return i;
        p = p -> next;
    }
    return ERROR;
    /********** End **********/
}
status PriorElem(LinkList L,ElemType e,ElemType &pre)
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p , q;
    p = L -> next;
    if(p)
    q = p -> next;
    else
    return ERROR;
    if(p -> data == e)
    return ERROR;
    while(q)
    {
        if(q -> data == e)
        {
            pre = p -> data;
            return OK;
        }
        p = p -> next;
        q = q -> next;
    }
    return ERROR;
    /********** End **********/
}
status NextElem(LinkList L,ElemType e,ElemType &next)
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p;
    p = L -> next;
    while(p)
    {
        if(p -> data == e && p -> next != NULL)
        {
            next = p -> next -> data;
            return OK;
        }
        p = p -> next;
    }
    return ERROR;
    /********** End **********/
}
status ListInsert(LinkList &L,int i,ElemType e)
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    int j = 2;
    if(!L)
    return INFEASIBLE;
    LinkList p , q , r;
    p = L -> next;
    if(p)
    q = p -> next;
    if(!p && i > 1)
    return ERROR;
    
    if(i == 1)
    {
        r = (LinkList)malloc(sizeof(LNode));
        r -> data = e;
        r -> next = p;
        L -> next = r;
        return OK;
    }
    while(q)
    {
        
        if(j == i)
        {
            r = (LinkList)malloc(sizeof(LNode));
            r -> data = e;
            r -> next = q;
            p -> next = r;
            return OK;
        }
        q = q -> next;
        p = p -> next;
        j++;
        if(j == i && q == NULL)
        {
            r = (LinkList)malloc(sizeof(LNode));
            r -> data = e;
            r -> next = NULL;
            p -> next = r;
            return OK;
        }
    }
    return ERROR;
    /********** End **********/
}
status ListDelete(LinkList &L,int i,ElemType &e)
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p , q;
    p = L -> next;
    if(!p)
    return ERROR;
    q = p -> next;
    if(i == 1)
    {
        e = p -> data;
        L -> next = p -> next;
        return OK;
    }
    i--;
    while(q)
    {
        i--;
        if(i == 0)
        {
            e = q -> data;
            p -> next = q -> next;
            free(q);
            return OK;
        }
        p = p -> next;
        q = q -> next;
    }
    return ERROR;
    /********** End **********/
}
status ListTraverse(LinkList L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    if(!L)
    return INFEASIBLE;
    LinkList p;
    p = L -> next;
    while(p)
    {
        printf("%d ",p -> data);
        p = p -> next;
    }
    return OK;
    /********** End **********/
}
status SaveList(LinkList L,char FileName[])
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 1 *********/
    if(!L)
    return INFEASIBLE;
    FILE *fp = NULL;
    fp = fopen(FileName,"w+");
    LinkList p;
    p = L -> next;
    while(p)
    {
        fprintf(fp,"%d ",p -> data);
        p = p -> next;
    }
    fclose(fp);
    return OK;
    /********** End 1 **********/
}

status LoadList(LinkList &L,char FileName[])
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin 2 *********/
    if(L)
    return INFEASIBLE;
    int e;
    L = (LinkList)malloc(sizeof(LNode));
    L -> next = NULL;
    LinkList p;
    p = L;
    FILE *fp = NULL;
    fp = fopen(FileName,"r");
    while(fscanf(fp,"%d",&e) == 1)/*����Ҫע�����whileѭ�����ܶ����һ������*/
    {
        p -> next = (LinkList)malloc(sizeof(LNode));
        p = p -> next;
        p -> data = e;
    }
    p -> next = NULL;
    fclose(fp);
    return OK;
    /********** End 2 **********/
}
status AddList(LISTS &Lists,char ListName[])
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    LinkList L1;
    L1 = NULL;
    InitList(L1);
    Lists.elem[Lists.length].L = L1;
    int k = 0;
    for(k = 0;k < Lists.length;k++)
    {
        if(strcmp(Lists.elem[k].name,ListName) == 0)
        printf("�Ѵ�����Ϊ %s �����Ա�!",ListName);
        return 0;
    }
    strcpy(Lists.elem[Lists.length].name , ListName); 
    Lists.length++;
    
    /********** End **********/
}
status RemoveList(LISTS &Lists,char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    ElemType x , i , j;
    for(i = 0;i < Lists.length;i++)
    {
        if(strcmp(Lists.elem[i].name , ListName) == 0)
        {
            for(j = i;j < Lists.length - 1;j++)
            Lists.elem[j] = Lists.elem[j + 1];
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
    /********** End **********/
}
int LocateList(LISTS Lists,char ListName[])
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
{
    // �������ﲹ����룬��ɱ�������
    /********** Begin *********/
    ElemType i;
    for(i = 0;i < Lists.length;i++)
    {
        if(strcmp(Lists.elem[i].name , ListName) == 0)
        return i+1;
    }
    return 0;
    /********** End **********/
}