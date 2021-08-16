#define _CRT_SECURE_NO_WARNINGS 1
#include "string.h"
#include "stdio.h"    
#include "stdlib.h"   


#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* 存储空间初始分配量 */

typedef int Status;

//构造二叉树
int TreeIndex = 1;
typedef char String[24]; //0号单元存放串的长度
String str;

Status StrAssign_lt(String T,char *chars) {
	int i;
	if (strlen(chars) > MAXSIZE)
		return ERROR;
	else
	{
		T[0] = strlen(chars);
		for ( i = 1; i <= T[0]; i++)
		{
			T[i] = *(chars + i - 1);   //0号单元存储串的长度，1号单元开始存放字符串的一个字符
		}
		return OK;
	}
}

typedef char TElemType;
TElemType Nil = ' '; /* 字符型以空格符为空 */

//lt -> linkTree
Status visit_lt(TElemType e) {
	printf("%c ", e);
	return OK;
}

//二叉树链式结构
typedef struct BiTreeNode{
	TElemType data; //结点数据
	struct BiTreeNode* lchild;  //左孩子结点
	struct BiTreeNode* rchild; //右孩子结点
}BiTreeNode,*BiTree;

/*
//非递归层次遍历所需要的队列
typedef struct QueueNode {
	BiTree data;
	struct QueueNode* next;
}QueueNode;

typedef struct LinkQueue_lt {
	QueueNode* front;
	QueueNode* tail;
}LinkQueue_lt;
*/

//构造空二叉树
Status InitBiTree_lt(BiTree *T) {
	*T = NULL;
	TreeIndex = 1;
	return OK;
}

//销毁二叉树
void DestoryBiTree_lt(BiTree *T) {
	if (*T) {
		if ((*T)->lchild)
			DestoryBiTree_lt((*T)->lchild);     //销毁左孩子子树 
		if ((*T)->rchild)
			DestoryBiTree_lt((*T)->rchild);		//销毁右孩子子树
		free(*T); //释放结点
		*T = NULL; //防止生成野指针
	}
}

//前序输入二叉树中结点的值,'#'表示空树，构造二叉链表表示二叉树T。 【中序和后序创建基本一致，可参考遍历】
void CreatePreBiTree_lt(BiTree* T) {
	TElemType ch;
	//scanf("%c",&ch); 
	ch = str[TreeIndex++];
	if (ch == '#')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTreeNode));
		if (!(*T))			//创建失败
			exit(EOVERFLOW);
		(*T)->data = ch;	//生成根结点
		CreatePreBiTree_lt(&(*T)->lchild);		//构造左子树
		CreatePreBiTree_lt(&(*T)->rchild);		//构造右子树
	}
}


//判断是否为空树 若T为空二叉树,则返回TRUE,否则FALSE
Status BiTreeEmpty_lt(BiTree T) {
	if (T)
		return FALSE;
	else
		return TRUE;
}

//#define ClearBiTree_lt DestoryBiTree_lt;
//清除二叉树与销毁二叉树一致
void ClearBiTree_lt(BiTree* T) {
	if (*T) {
		if ((*T)->lchild)
			ClearBiTree_lt(&(*T)->lchild);     //销毁左孩子子树 
		if ((*T)->rchild)
			ClearBiTree_lt(&(*T)->rchild);		//销毁右孩子子树
		free(*T); //释放结点
		*T = NULL; //防止生成野指针
	}
}

// 二叉树T存在，p指向T中某个结点，返回p所指结点的值
TElemType Value_lt(BiTree p) {
	return p->data;
}

//前序递归遍历T
void PreOrderTraverse_lt(BiTree T) {
	if (T == NULL)
		return;
	printf("%c", T->data);				//显示结点数据，可以更改为其它对结点操作
	PreOrderTraverse_lt(T->lchild);		//再先序遍历左子树
	PreOrderTraverse_lt(T->rchild);		//最后先序遍历右子树
}

//中序递归遍历T
void InOrderTraverse_lt(BiTree T) {
	if (T == NULL)
		return;
	InOrderTraverse_lt(T->lchild);		//先先序遍历左子树
	printf("%c", T->data);				//再显示结点数据，可以更改为其它对结点操作
	InOrderTraverse_lt(T->rchild);		//最后先序遍历右子树
}

//后序递归遍历T
void PostOrderTraverse_lt(BiTree T) {
	if (T == NULL)
		return;
	PostOrderTraverse_lt(T->lchild);	///先先序遍历左子树
	PostOrderTraverse_lt(T->rchild);	//再先序遍历右子树
	printf("%c", T->data);				//最后显示结点数据，可以更改为其它对结点操作
}


//统计结点个数
int NodeCount_lt(BiTree T) {
	if (T == NULL)
		return 0;
	else
		return NodeCount_lt(T->lchild) + NodeCount_lt(T->rchild) + 1;
}

//返回T的深度
int BiTreeDepth_lt(BiTree T) {
	int i, j;  //i 递归计算左子树深度，j计算右子树深度
	if (!T)   //如果为空树，深度为0，递归结束
		return 0;
	i = BiTreeDepth_lt(T->lchild);
	j = BiTreeDepth_lt(T->rchild);
	return i > j ? i + 1 : j + 1;  //加1是加入根结点
}

//返回T的根
TElemType Root_lt(BiTree T) {
	if (BiTreeEmpty_lt(T))
		return Nil;
	else
		return T->data;  //因为创建树时是使用先序遍历创建
}

//查找结点
BiTree Sreach_lt(BiTree T,TElemType key) {
	if (T == NULL)
		return NULL;
	if (T->data == key)  //判断当前结点是否等于key值，是返回结点地址
		return T;
	//不是，在向子树寻找
	BiTree P = Sreach_lt(T->lchild,key);//查找左子树
	if (P != NULL)			//判断是否找到
		return P;
	return Sreach_lt(T->rchild, key);// 查找右子树，返回查找结果
}

//查找某结点的父节点
BiTree Parent_lt(BiTree T,BiTree P) {    
	if (T == NULL || P == NULL)
		return NULL;
	if (T->lchild == P || T->rchild == P)	//判断t的左右孩子是否为p
		return T;
	BiTree Q = Parent_lt(T->lchild,P);      //从T的左子树先查找
	if (Q != NULL)
		return Q;
	//Q = Parent_lt(T->rchild, P);
	//if (Q != NULL)
	//	return Q;
	/*  上面可以简写为下面代码 */
	return Parent_lt(T->rchild,P);  ////查找右子树
}

//获取二叉树的左子树
BiTree LeftChild_lt(BiTree T) {
	if (T!=NULL)		//不为空返回T的左子树
		return T->lchild;
	return NULL;
}

//获取二叉树的右子树 
BiTree RightChild_lt(BiTree T) {
	if (T != NULL)		 //不为空返回T的右子树
		return T->rchild;
	return NULL;
}

//获取左兄弟结点
BiTree LeftSibling_lt(BiTree T,TElemType key) {
	BiTree P;
	if (T == NULL)
		return NULL;
	if (T->rchild != NULL && T->rchild->data == key)	//(T->rchild != NULL)防止空指针异常 找到右结点为key后返回其左兄弟结点
		return T->lchild;
	P = LeftSibling_lt(T->lchild, key);		//从左子树寻找，找到就返回
	if (P != NULL)
		return P;
	return LeftSibling_lt(T->rchild, key);	//从右子树寻找，找到就返回
}

//获取右兄弟结点 
BiTree RightSibling_lt(BiTree T,TElemType key) {
	BiTree P;
	if (T == NULL)
		return NULL;
	if (T->lchild != NULL && T->lchild->data == key)   //找到左结点为key后返回其右兄弟结点
		return T->rchild;
	P = RightSibling_lt(T->lchild,key);		 //从左子树寻找，找到就返回
	if (P != NULL)
		return P;
	return RightSibling_lt(T->rchild,key);  //从右子树寻找，找到就返回
}


//复制二叉树(T2拷贝给T1)
void Copy_lt(BiTree T1,BiTree *T2) {
	if (T1 == NULL)
		*T2 = NULL;
	else
	{
		*T2 = (BiTree)malloc(sizeof(BiTreeNode));
		if (!(*T2))
			exit(EOVERFLOW);
		(*T2)->data = T1->data;
		Copy_lt(T1->lchild,&(*T2)->lchild);
		Copy_lt(T1->rchild,&(*T2)->rchild);
	}
}

int mainlt(){
	int i,count;
	BiTree T,T1,Tp,Tl,Tr,Tnew,TLs,TRs;
	TElemType e,e1;
	InitBiTree_lt(&T);

	StrAssign_lt(str, "ABDH#K###E##CFI###G#J##");

	CreatePreBiTree_lt(&T);
	
	printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty_lt(T),BiTreeDepth_lt(T));

	e = Root_lt(T);
	printf("二叉树的根为: %c\n", e);

	printf("\n前序遍历二叉树:");
	PreOrderTraverse_lt(T);
	printf("\n中序遍历二叉树:");
	InOrderTraverse_lt(T);
	printf("\n后序遍历二叉树:");
	PostOrderTraverse_lt(T);

	printf("\n");

	count = NodeCount_lt(T);
	printf("二叉树有 %d 个结点\n", count);

	T1 = Sreach_lt(T, 'D');
	printf("\n前序遍历二叉树T1:");
	PreOrderTraverse_lt(T1);

	Tp = Parent_lt(T,T1);
	printf("\n前序遍历二叉树Tp:");
	PreOrderTraverse_lt(Tp);
	printf("\n结点%c的父节点为结点%c",T1->data, Tp->data);

	Tl = LeftChild_lt(T);
	printf("\n遍历二叉树%c的左子树:", T->data);
	PreOrderTraverse_lt(Tl);

	Tr = RightChild_lt(T);
	printf("\n遍历二叉树%c的右子树:", T->data);
	PreOrderTraverse_lt(Tr);

	InitBiTree_lt(&Tnew);
	Copy_lt(T,&Tnew);
	printf("\n前序遍历二叉树Tnew:");
	PreOrderTraverse_lt(Tnew);

	e1 = 'E';
	TRs = RightSibling_lt(T, e1);
	if (TRs != NULL) {
		printf("\n结点%c的兄弟结点为%c", e1, TRs->data);
	}

	TLs = LeftSibling_lt(T,e1);
	if (TLs != NULL)
	{
		printf("\n结点%c的兄弟结点为%c", e1, TLs->data);
	}

	ClearBiTree_lt(&T);
	printf("\n构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty_lt(T), BiTreeDepth_lt(T));
	
	return 0;
}