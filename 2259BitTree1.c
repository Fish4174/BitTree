#include<stdio.h>
#include<stdlib.h>
typedef char ElemType;
typedef struct node
{
	ElemType data;
	struct node *lchild,*rchild;
}BitTree;
BitTree *CreBiTree()//建立二叉树 
{
	BitTree *bt;
	ElemType x;
	scanf("%c",&x);
	if(x=='#') bt=NULL;
	else
	{
		bt=(BitTree *)malloc(sizeof(BitTree));
		bt->data=x;
		bt->lchild=CreBiTree();
		bt->rchild=CreBiTree();
	}
	return bt;
}
void PreOrder(BitTree *bt)//先序递归遍历 
{
	if(bt!=NULL)
	{
		printf("%c",bt->data);
		PreOrder(bt->lchild);
		PreOrder(bt->rchild);
	}
}
void InOrder(BitTree *bt)//中序递归遍历 
{
	if(bt!=NULL)
	{
		InOrder(bt->lchild);
		printf("%c",bt->data);
		InOrder(bt->rchild);
	}
}
void PostOrder(BitTree *bt)//后序递归遍历 
{
	if(bt!=NULL)
	{
		PostOrder(bt->lchild);
		PostOrder(bt->rchild);
		printf("%c",bt->data);
	}
}
int LeafCount(BitTree *bt)//统计叶子结点个数
{
	static int n=0;
	if(bt!=NULL)
	{
		if(bt->lchild==NULL&&bt->rchild==NULL)
			n++;
		LeafCount(bt->lchild);
		LeafCount(bt->rchild);
	}
	return n;
}
int High(BitTree *bt)//计算二叉树高度
{
	int H,H1,H2;
	if(bt==NULL) H=0;
	else
	{
		H1=High(bt->lchild);
		H2=High(bt->rchild);
		H=(H1>H2?H1:H2)+1;
	}
	return H;
}
int Compare(BitTree *bt,ElemType x)//统计结点值大于x的结点个数 
{
	static int cnt=0;
	if(bt!=NULL)
	{
		if(bt->data>x) cnt++;
		Compare(bt->lchild,x);
		Compare(bt->rchild,x);
	}
	return cnt;
}
int Count(BitTree *bt)
{
	int cnt;
	if(bt==NULL) cnt=0;
	else
		cnt=Count(bt->lchild)+Count(bt->rchild)+1;
	return cnt;
}
int ChildCount(BitTree *bt,ElemType x)//计算值为x的结点的孩子个数
{
	if(bt==NULL)
		return -1;
	if(bt->data==x)
	{
		return Count(bt)-1;
	}
	int left=ChildCount(bt->lchild,x);
	if(left!=-1)//左子树找到了，返回left，如果没找到则不返回，执行后续语句
		return left;
	int right=ChildCount(bt->rchild,x);
	return right;//右子树还没找到就是真的找不到了，此时若返回-1，则说明整棵树里没有值为x的结点
}
void ExchangeTree(BitTree *bt)//交换所有结点的左右子树
{
	BitTree *t;
	if(bt!=NULL)
	{
		if(bt->lchild!=NULL||bt->rchild!=NULL)
		{
			t=bt->lchild;
			bt->lchild=bt->rchild;
			bt->rchild=t;
		}
		ExchangeTree(bt->lchild);
		ExchangeTree(bt->rchild);
	}
}
void Exchange_xy(BitTree *bt,ElemType x,ElemType y)
{
	BitTree *t;
	if(bt!=NULL)
	{
		if(bt->lchild!=NULL||bt->rchild!=NULL)
		{
			if(bt->data>x&&bt->data<y)
			{
				//printf("%c的子树被交换了\n",bt->data);
				t=bt->lchild;
				bt->lchild=bt->rchild;
				bt->rchild=t;				
			}
		}
		Exchange_xy(bt->lchild,x,y);
		Exchange_xy(bt->rchild,x,y);
	}
}
int main()
{
	int op;
	ElemType x,y;
	BitTree *bt;
	printf("请输入二叉树的先序序列，以建立二叉树，输入#表示空。\n");
	//ABDGH#I####E##CF###
	bt=CreBiTree();
	printf("二叉树的先序遍历为：\n");
	PreOrder(bt);
	printf("\n\n");
	while(1)
	{
		printf("-------------------请选择操作-------------------\n");
		printf("先序遍历二叉树，请按1\n");
		printf("中序遍历二叉树，请按2\n");
		printf("后序遍历二叉树，请按3\n");
		printf("统计叶子结点数，请按4\n");
		printf("求二叉树高度，请按5\n");
		printf("统计结点值大于给定值x的结点个数，请按6\n");
		printf("计算值为x的结点的孩子个数，请按7\n");
		printf("交换二叉树中所有结点的左右子树，请按8\n");
		printf("交换所有值大于x小于y的结点的左右子树，请按9\n");
		printf("结束程序，请按0\n");
		scanf("%d",&op);
		switch(op)
		{
			case 1:
			{
				printf("二叉树的先序遍历为：\n");
				PreOrder(bt);
				printf("\n\n");
			}break;
			case 2:
			{
				printf("二叉树的中序遍历为：\n");
				InOrder(bt);
				printf("\n\n");
			}break;
			case 3:
			{
				printf("二叉树的后序遍历为：\n");
				PostOrder(bt);
				printf("\n\n");
			}break;
			case 4:
			{
				printf("二叉树中叶子结点个数为：\n");
				printf("%d\n",LeafCount(bt));
				printf("\n");
			}break;
			case 5:
			{
				printf("二叉树的高度为：\n");
				printf("%d\n",High(bt));
				printf("\n");
			}break;
			case 6:
			{
				printf("请输入参数x（大写字母）\n");
				getchar();
				scanf("%c",&x);
				printf("结点值大于给定值x的结点个数为：\n");
				printf("%d\n",Compare(bt,x));
				printf("\n"); 
			}break;
			case 7:
			{
				printf("请输入参数x\n");
				getchar();
				scanf("%c",&x);
				if(ChildCount(bt,x)!=-1)
				{
					printf("值为x的结点的孩子个数为：\n");
					printf("%d\n",ChildCount(bt,x));				
				}
				else
				{
					printf("参数不合理，找不到该节点。\n");
				}
				printf("\n");
			}break;
			case 8:
			{
				ExchangeTree(bt);
				printf("所有结点的左右子树已完成交换，新二叉树的先序遍历为：");
				PreOrder(bt);
				printf("\n\n");
			}break;
			case 9:
			{
				printf("请输入参数x和y（大写字母）：\n");
				getchar();
				scanf("%c %c",&x,&y);
				if(x>y||x<'A'||x>'Z'||y<'A'||y>'Z')
				{
					printf("参数不合理，请输入大写字母x和y，并满足 x<y 。\n\n");
				}
				else
				{
					Exchange_xy(bt,x,y);
					printf("值大于%c小于%c的结点的左右子树已完成交换，新二叉树的先序遍历为：",x,y);
					PreOrder(bt);
					printf("\n\n");				
				}
			}break;
			default:
			{
				exit(0);
			}break;
		}
	}
	return 0;
}
