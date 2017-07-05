#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *pNext;
};

int main(void)
{
	struct node *pHeader = NULL;
	
	struct node *p = (struct node *)malloc(sizeof(struct node));
	if(NULL == p)
	{
		printf("malloc error\n");
		return -1;
	}
	
	bzero(p, sizeof(struct node));
	
	p->data = 0;
	p->pNext = NULL;
	
	pHeader = p;
	
	
	struct node *p1 = (struct node *)malloc(sizeof(struct node));
	if(NULL == p1)
	{
		printf("malloc error\n");
		return -1;
	}
	
	bzero(p1, sizeof(struct node));
	
	p1->data = 1;
	p1->pNext = NULL;
	
	p->pNext = p1;
	
	struct node *p2 = (struct node *)malloc(sizeof(struct node));
	if(NULL == p2)
	{
		printf("malloc error\n");
		return -1;
	}
	
	bzero(p2, sizeof(struct node));
	
	p2->data = 2;
	p2->pNext = NULL;
	
	p1->pNext = p2;

	
	printf("node1 data: %d.\n", pHeader->data);	
	printf("p->data: %d.\n", p->data);			// pHeader->data等同于p->data
	
	// 访问链表第2个节点的有效数据
	printf("node2 data: %d.\n", pHeader->pNext->data);	
	printf("p1->data: %d.\n", p1->data);	
	// pHeader->pNext->data等同于p1->data
	
	// 访问链表第3个节点的有效数据
	printf("node3 data: %d.\n", pHeader->pNext->pNext->data);	
	printf("p2->data: %d.\n", p2->data);			
	
	
}