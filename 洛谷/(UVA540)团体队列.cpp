#include<stdio.h>
#include<stdlib.h>
#include<string.h>
	#define OK 1
    #define OVERFLOW -2
	#define ERROR 0
typedef struct QNode{
    int data;
    struct QNode *next;
}QNode, *QueuePtr;
typedef struct 
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;
int InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if(!Q.front)
    exit(OVERFLOW);
    Q.front -> next = NULL;
    return OK;
}
int EnQueue(LinkQueue &Q, int e)
{
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    p -> data = e;
    p -> next = NULL;
    Q.rear -> next = p;
    Q.rear = p;
    return OK;
}
int DeQueue(LinkQueue &Q, int &e)
{
    if(Q.front == Q.rear)
    return ERROR;
    QueuePtr p;
    p = Q.front -> next;
    e = p -> data;
    Q.front -> next = p -> next;
    if(Q.rear == p)
    {
        Q.front = Q.rear;
    }
    free(p);
    return OK;
}
int QueueEmpty(LinkQueue Q)
{
    if(Q.front == Q.rear)
    return OK;
    return ERROR;
}

int tag [1000001];
int main()
{
    int flag = 0;
    
    int n , m , num , count = 0;
    char op[20];
    while (1)
    {
        LinkQueue q , p[1001];
        InitQueue(q);
        for(int i = 1;i <= 1000;i++)
        InitQueue(p[i]);
        flag = 0;
        count++;
        scanf("%d",&n);
        if(n == 0)
        break;
        for(int i = 1;i <= n;i++)/*先把团队的数据搞进去(x)把数据标记为不同团队（√）*/
        {
            scanf("%d",&m);
            for(int j = 1;j <= m;j++)
            {
                int k;
                scanf("%d",&k);
                tag[k] = i;/*打下标记*/
            }
        }
        while (1)
        {
            scanf("%s",op);
            if(strcmp(op,"ENQUEUE") == 0)
            {
                scanf("%d",&num);
                if(QueueEmpty(p[tag[num]]))
                {
                    EnQueue(q , tag[num]);
                    EnQueue(p[tag[num]] , num);
                }
                else
                EnQueue(p[tag[num]],num);
            }
            if(strcmp(op,"DEQUEUE") == 0)
            {
                int e;
                if(flag == 0)
                {
                    printf("Scenario #%d\n",count);
                    flag = 1;
                }
                while(QueueEmpty(p[q.front->next->data]))
                {
                    q.front = q.front->next;
                }
                
                DeQueue(p[q.front->next->data] , e);
                printf("%d\n",e);
            }
            if(strcmp(op,"STOP") == 0)
            {
                printf("\n");
                break;
            }
        }
        
    }
    
    return 0;
}