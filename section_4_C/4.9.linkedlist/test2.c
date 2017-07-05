#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *pNext;
};

struct node *creat_node(int data)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	if(NULL == p)
	{
		printf("malloc error\n");
		return NULL;
	}
	
	bzero(p, sizeof(struct node));
	
	p->data = data;
	p->pNext = NULL;
	
	return p;
	
}

void insert_tail(struct node *pHeader, struct node *new)
{
	int cnt = 0;
	struct node *p = pHeader;
	//如果这里的p只是一个指针，而不是指向一个节点，那么会触发段错误，根本就没有p->pNext
	while(NULL != p->pNext)
	{
		p=p->pNext;
		cnt++;
	}
	p->pNext = new;
	pHeader->data = cnt+1;
	
}

void insert_head(struct node *pHeader, struct node *new)
{
	//第一步：新节点的pNext指针指向原第一个节点
	new->pNext = pHeader->pNext;
	//第二步：将头结点的pNext指针指向新节点指向新节点
	pHeader->pNext = new;
	
	pHeader->data++;
}

void list_for_each(struct node *pHeader)
{
	struct node *p = pHeader;
	printf("-----------开始遍历-----------\n");
	while(NULL != p->pNext)
	{
		p = p->pNext;
		printf("node data: %d.\n", p->data);
	}
	printf("-------------遍历结束-------------\n\n");
}

int delete_node(struct node *pHeader, int data)
{
	struct node *p = pHeader;
	struct node *pPrev = NULL;
	while(NULL != p->pNext)
	{
		pPrev = p;
		p = p->pNext;
		
		if(p->data == data)
		{
			if(p->pNext == NULL)
			{
				pPrev->pNext = NULL;
				free(p);
			}
			else 
			{
				pPrev->pNext = p->pNext;
				free(p);
			}
		}
	}
	return 0;
//	printf("没找到这个节点.\n");
//	return -1;
	
}

void reverse_list(struct node *pHeader)
{
	struct node *p = pHeader->pNext;
	struct node *pBack = NULL;
	if((p == NULL)||(p->pNext == NULL)) //p为第一个有效节点
		return;

	while(NULL != p->pNext)
	{
		pBack = p->pNext;
		if(p == pHeader->pNext)	//要区分原链表第一个有效节点
		{
			// 原链表中第一个有效节点将是逆序后新链表的尾节点，尾节点的pNext指向NULL
			p->pNext = NULL;	//头插之尾部连接
		}
		else
		{
			p->pNext = pHeader->pNext;	//头插之尾部连接
		}
		pHeader->pNext = p;				//头插之头部连接
		
		p = pBack;
	}
	insert_head(pHeader, p);
}

int main(void)
{
#if 0	
	// 这样直接insert_tail会段错误。
	struct node *pHeader = NULL;

	pHeader = creat_node(0);
	pHeader->pNext = creat_node(1);
	pHeader->pNext->pNext = creat_node(2);
#endif

	struct node *pHeader = creat_node(0);
	insert_tail(pHeader, creat_node(1));
	insert_tail(pHeader, creat_node(3));
	insert_tail(pHeader, creat_node(5));
	insert_head(pHeader, creat_node(2));
	insert_head(pHeader, creat_node(5));
	list_for_each(pHeader);
	
//	delete_node(pHeader, 5);
//	printf("------------------删除后-------------\n");
	//list_for_each(pHeader);
	reverse_list(pHeader);
	list_for_each(pHeader);
	return 0;
}


