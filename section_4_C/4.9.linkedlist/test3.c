#include <stdio.h>
#include <stdlib.h>


// ˫����Ľڵ�
struct node 
{
	int data;					// ��Ч����
	struct node *pPrev;			// ǰ��ָ�룬ָ��ǰһ���ڵ�
	struct node *pNext;			// ����ָ�룬ָ���һ���ڵ�
};

struct node *create_node(int data)
{
	struct node *p = (struct node *)malloc(sizeof(struct node));
	if (NULL == p)
	{
		printf("malloc error.\n");
		return NULL;
	}
	p->data = data;
	p->pPrev = NULL;
	p->pNext = NULL;		// Ĭ�ϴ����Ľڵ�ǰ�����ָ�붼ָ��NULL
	
	return p;
}


void insert_tail(struct node *pHeader, struct node *new)
{
	struct node *p = pHeader;
	
	while(NULL != p->pNext)
	{
		p = p->pNext;
	}
	
	p->pNext = new;
	new->pPrev = p;
}

void insert_head(struct node *pHeader, struct node *new)
{
	new->pNext = pHeader->pNext;
	
	if(NULL != pHeader->pNext)
	pHeader->pNext->pPrev = new;
	
	pHeader->pNext = new;
	
	new->pPrev = pHeader;
}

int main(void)
{
	struct node *pHeader = create_node(0);		// ͷָ��
	
	insert_tail(pHeader, create_node(11));
	insert_tail(pHeader, create_node(12));
	//insert_tail(pHeader, create_node(13));
	insert_head(pHeader, create_node(10));
	// ����
	
	printf("node 1 data: %d.\n", pHeader->pNext->data);
	printf("node 2 data: %d.\n", pHeader->pNext->pNext->data);
	printf("node 3 data: %d.\n", pHeader->pNext->pNext->pNext->data);
	printf("\n");

	struct node *p = pHeader->pNext->pNext->pNext;		// pָ�������һ���ڵ�
	printf("node 3 data: %d.\n", p->data);
	printf("node 2 data: %d.\n", p->pPrev->data);
	printf("node 1 data: %d.\n", p->pPrev->pPrev->data);
	
	
	
	return 0;
}
















