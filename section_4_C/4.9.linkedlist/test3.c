#include <stdio.h>
#include <stdlib.h>


// 双链表的节点
struct node 
{
	int data;					// 有效数据
	struct node *pPrev;			// 前向指针，指向前一个节点
	struct node *pNext;			// 后向指针，指向后一个节点
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
	p->pNext = NULL;		// 默认创建的节点前向后向指针都指向NULL
	
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
	struct node *pHeader = create_node(0);		// 头指针
	
	insert_tail(pHeader, create_node(11));
	insert_tail(pHeader, create_node(12));
	//insert_tail(pHeader, create_node(13));
	insert_head(pHeader, create_node(10));
	// 遍历
	
	printf("node 1 data: %d.\n", pHeader->pNext->data);
	printf("node 2 data: %d.\n", pHeader->pNext->pNext->data);
	printf("node 3 data: %d.\n", pHeader->pNext->pNext->pNext->data);
	printf("\n");

	struct node *p = pHeader->pNext->pNext->pNext;		// p指向了最后一个节点
	printf("node 3 data: %d.\n", p->data);
	printf("node 2 data: %d.\n", p->pPrev->data);
	printf("node 1 data: %d.\n", p->pPrev->pPrev->data);
	
	
	
	return 0;
}
















