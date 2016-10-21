#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;
typedef struct BitNode   								//节点
{
	ElemType e;
	struct BitNode *next;
	struct BitNode *lchild,*rchild;

}BitNode,*BitTree;
typedef struct 											//栈
{	BitNode *base;
	BitNode * top;
} SqStack;

void InitStack(SqStack * p);							//初始化栈
int StackEmpty(SqStack *p);								//判断栈空
void Push(SqStack *p,BitTree T);						//入栈	
void Pop(SqStack *p,BitTree *T);						//出栈
int GetTop(SqStack *p,BitTree * T);						//获得栈的头结点
int Visit(BitNode * p);									//访问结点数据，即打印数据
BitTree CreateBitTree(BitTree T);						//创建二叉树
void InOrderTraverse1(BitTree T,SqStack * S);			//非递归中序遍历1
void InOrderTraverse2(BitTree T,SqStack * S);			//非递归中序遍历2
void main()
{
	SqStack S,S1;
	BitTree T;
	InitStack(&S);
	InitStack(&S1);
	T=CreateBitTree(T);
	InOrderTraverse1(T,&S);
	printf("\n");
	InOrderTraverse2(T,&S1);

}

void InitStack(SqStack * p)
{
	p->top=(BitNode *)malloc(sizeof(BitNode));
	p->base=(BitNode *)malloc(sizeof(BitNode));
	if((p->top)==NULL)
	{
		printf("don't have enough space\n");
	}
	if((p->base)==NULL)
	{
		printf("don't have enough space\n");
	}
	p->top->next=p->base;
}

int StackEmpty(SqStack *p)
{
	if(p->top->next==p->base)
	{
		return 1;
	}else{
		return 0;
	}

}
void Push(SqStack *p,BitTree T)
{
	T->next=p->top->next;
	p->top->next=T;

}
void Pop(SqStack *p,BitTree * T)
{
	BitNode  * q;
	if(StackEmpty(p))
	{
		exit(1);
	}

	q=p->top->next;
	*T=q;
	p->top->next=q->next;

}
int GetTop(SqStack *p,BitTree *T)
{
	*T=p->top->next;
	return 1;
}
int Visit(BitNode * p)
{
	printf("%d\t",p->e);
	return 1;

}
BitTree CreateBitTree(BitTree T)
{	

	ElemType e;
	scanf("%d",&e);
	if(e==-1) T=NULL;			//当输入-1时生成空树
	else{
		T=(BitNode *)malloc(sizeof(BitNode));
		if(T==NULL)
		{
			printf("don't have enough space");
			exit(1);
		}
		T->e=e;
		T->lchild=CreateBitTree(T->lchild);
		T->rchild=CreateBitTree(T->rchild);
	}
	return T;
}
void InOrderTraverse1(BitTree T,SqStack * S)
{
	BitTree p=T;
	Push(S,p);
	while(!StackEmpty(S))
	{
		while(GetTop(S,&p)&&p)
		{
			Push(S,p->lchild);
		}
		Pop(S,&p);
		if(!StackEmpty(S))
		{
			Pop(S,&p);
			Visit(p);
			Push(S,p->rchild);
		}

	}

}
void InOrderTraverse2(BitTree T,SqStack * S)
{
	BitTree p=T;
	if(p!=NULL)
		Push(S,p);
	while(!StackEmpty(S))
	{	
		Pop(S,&p);
		if(p)
		{
			Push(S,p);
			p=p->lchild;
			Push(S,p);
		}else{
			Pop(S,&p);
			Visit(p);
			Push(S,p->rchild);
		}
	}
}
