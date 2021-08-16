#define _CRT_SECURE_NO_WARNINGS 1
#include "string.h"
#include "stdio.h"    
#include "stdlib.h"   


#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100 /* �洢�ռ��ʼ������ */

typedef int Status;

//���������
int TreeIndex = 1;
typedef char String[24]; //0�ŵ�Ԫ��Ŵ��ĳ���
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
			T[i] = *(chars + i - 1);   //0�ŵ�Ԫ�洢���ĳ��ȣ�1�ŵ�Ԫ��ʼ����ַ�����һ���ַ�
		}
		return OK;
	}
}

typedef char TElemType;
TElemType Nil = ' '; /* �ַ����Կո��Ϊ�� */

//lt -> linkTree
Status visit_lt(TElemType e) {
	printf("%c ", e);
	return OK;
}

//��������ʽ�ṹ
typedef struct BiTreeNode{
	TElemType data; //�������
	struct BiTreeNode* lchild;  //���ӽ��
	struct BiTreeNode* rchild; //�Һ��ӽ��
}BiTreeNode,*BiTree;

/*
//�ǵݹ��α�������Ҫ�Ķ���
typedef struct QueueNode {
	BiTree data;
	struct QueueNode* next;
}QueueNode;

typedef struct LinkQueue_lt {
	QueueNode* front;
	QueueNode* tail;
}LinkQueue_lt;
*/

//����ն�����
Status InitBiTree_lt(BiTree *T) {
	*T = NULL;
	TreeIndex = 1;
	return OK;
}

//���ٶ�����
void DestoryBiTree_lt(BiTree *T) {
	if (*T) {
		if ((*T)->lchild)
			DestoryBiTree_lt((*T)->lchild);     //������������ 
		if ((*T)->rchild)
			DestoryBiTree_lt((*T)->rchild);		//�����Һ�������
		free(*T); //�ͷŽ��
		*T = NULL; //��ֹ����Ұָ��
	}
}

//ǰ������������н���ֵ,'#'��ʾ������������������ʾ������T�� ������ͺ��򴴽�����һ�£��ɲο�������
void CreatePreBiTree_lt(BiTree* T) {
	TElemType ch;
	//scanf("%c",&ch); 
	ch = str[TreeIndex++];
	if (ch == '#')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTreeNode));
		if (!(*T))			//����ʧ��
			exit(EOVERFLOW);
		(*T)->data = ch;	//���ɸ����
		CreatePreBiTree_lt(&(*T)->lchild);		//����������
		CreatePreBiTree_lt(&(*T)->rchild);		//����������
	}
}


//�ж��Ƿ�Ϊ���� ��TΪ�ն�����,�򷵻�TRUE,����FALSE
Status BiTreeEmpty_lt(BiTree T) {
	if (T)
		return FALSE;
	else
		return TRUE;
}

//#define ClearBiTree_lt DestoryBiTree_lt;
//��������������ٶ�����һ��
void ClearBiTree_lt(BiTree* T) {
	if (*T) {
		if ((*T)->lchild)
			ClearBiTree_lt(&(*T)->lchild);     //������������ 
		if ((*T)->rchild)
			ClearBiTree_lt(&(*T)->rchild);		//�����Һ�������
		free(*T); //�ͷŽ��
		*T = NULL; //��ֹ����Ұָ��
	}
}

// ������T���ڣ�pָ��T��ĳ����㣬����p��ָ����ֵ
TElemType Value_lt(BiTree p) {
	return p->data;
}

//ǰ��ݹ����T
void PreOrderTraverse_lt(BiTree T) {
	if (T == NULL)
		return;
	printf("%c", T->data);				//��ʾ������ݣ����Ը���Ϊ�����Խ�����
	PreOrderTraverse_lt(T->lchild);		//���������������
	PreOrderTraverse_lt(T->rchild);		//����������������
}

//����ݹ����T
void InOrderTraverse_lt(BiTree T) {
	if (T == NULL)
		return;
	InOrderTraverse_lt(T->lchild);		//���������������
	printf("%c", T->data);				//����ʾ������ݣ����Ը���Ϊ�����Խ�����
	InOrderTraverse_lt(T->rchild);		//����������������
}

//����ݹ����T
void PostOrderTraverse_lt(BiTree T) {
	if (T == NULL)
		return;
	PostOrderTraverse_lt(T->lchild);	///���������������
	PostOrderTraverse_lt(T->rchild);	//���������������
	printf("%c", T->data);				//�����ʾ������ݣ����Ը���Ϊ�����Խ�����
}


//ͳ�ƽ�����
int NodeCount_lt(BiTree T) {
	if (T == NULL)
		return 0;
	else
		return NodeCount_lt(T->lchild) + NodeCount_lt(T->rchild) + 1;
}

//����T�����
int BiTreeDepth_lt(BiTree T) {
	int i, j;  //i �ݹ������������ȣ�j�������������
	if (!T)   //���Ϊ���������Ϊ0���ݹ����
		return 0;
	i = BiTreeDepth_lt(T->lchild);
	j = BiTreeDepth_lt(T->rchild);
	return i > j ? i + 1 : j + 1;  //��1�Ǽ�������
}

//����T�ĸ�
TElemType Root_lt(BiTree T) {
	if (BiTreeEmpty_lt(T))
		return Nil;
	else
		return T->data;  //��Ϊ������ʱ��ʹ�������������
}

//���ҽ��
BiTree Sreach_lt(BiTree T,TElemType key) {
	if (T == NULL)
		return NULL;
	if (T->data == key)  //�жϵ�ǰ����Ƿ����keyֵ���Ƿ��ؽ���ַ
		return T;
	//���ǣ���������Ѱ��
	BiTree P = Sreach_lt(T->lchild,key);//����������
	if (P != NULL)			//�ж��Ƿ��ҵ�
		return P;
	return Sreach_lt(T->rchild, key);// ���������������ز��ҽ��
}

//����ĳ���ĸ��ڵ�
BiTree Parent_lt(BiTree T,BiTree P) {    
	if (T == NULL || P == NULL)
		return NULL;
	if (T->lchild == P || T->rchild == P)	//�ж�t�����Һ����Ƿ�Ϊp
		return T;
	BiTree Q = Parent_lt(T->lchild,P);      //��T���������Ȳ���
	if (Q != NULL)
		return Q;
	//Q = Parent_lt(T->rchild, P);
	//if (Q != NULL)
	//	return Q;
	/*  ������Լ�дΪ������� */
	return Parent_lt(T->rchild,P);  ////����������
}

//��ȡ��������������
BiTree LeftChild_lt(BiTree T) {
	if (T!=NULL)		//��Ϊ�շ���T��������
		return T->lchild;
	return NULL;
}

//��ȡ�������������� 
BiTree RightChild_lt(BiTree T) {
	if (T != NULL)		 //��Ϊ�շ���T��������
		return T->rchild;
	return NULL;
}

//��ȡ���ֵܽ��
BiTree LeftSibling_lt(BiTree T,TElemType key) {
	BiTree P;
	if (T == NULL)
		return NULL;
	if (T->rchild != NULL && T->rchild->data == key)	//(T->rchild != NULL)��ֹ��ָ���쳣 �ҵ��ҽ��Ϊkey�󷵻������ֵܽ��
		return T->lchild;
	P = LeftSibling_lt(T->lchild, key);		//��������Ѱ�ң��ҵ��ͷ���
	if (P != NULL)
		return P;
	return LeftSibling_lt(T->rchild, key);	//��������Ѱ�ң��ҵ��ͷ���
}

//��ȡ���ֵܽ�� 
BiTree RightSibling_lt(BiTree T,TElemType key) {
	BiTree P;
	if (T == NULL)
		return NULL;
	if (T->lchild != NULL && T->lchild->data == key)   //�ҵ�����Ϊkey�󷵻������ֵܽ��
		return T->rchild;
	P = RightSibling_lt(T->lchild,key);		 //��������Ѱ�ң��ҵ��ͷ���
	if (P != NULL)
		return P;
	return RightSibling_lt(T->rchild,key);  //��������Ѱ�ң��ҵ��ͷ���
}


//���ƶ�����(T2������T1)
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
	
	printf("����ն�������,���շ�%d(1:�� 0:��) �������=%d\n", BiTreeEmpty_lt(T),BiTreeDepth_lt(T));

	e = Root_lt(T);
	printf("�������ĸ�Ϊ: %c\n", e);

	printf("\nǰ�����������:");
	PreOrderTraverse_lt(T);
	printf("\n�������������:");
	InOrderTraverse_lt(T);
	printf("\n�������������:");
	PostOrderTraverse_lt(T);

	printf("\n");

	count = NodeCount_lt(T);
	printf("�������� %d �����\n", count);

	T1 = Sreach_lt(T, 'D');
	printf("\nǰ�����������T1:");
	PreOrderTraverse_lt(T1);

	Tp = Parent_lt(T,T1);
	printf("\nǰ�����������Tp:");
	PreOrderTraverse_lt(Tp);
	printf("\n���%c�ĸ��ڵ�Ϊ���%c",T1->data, Tp->data);

	Tl = LeftChild_lt(T);
	printf("\n����������%c��������:", T->data);
	PreOrderTraverse_lt(Tl);

	Tr = RightChild_lt(T);
	printf("\n����������%c��������:", T->data);
	PreOrderTraverse_lt(Tr);

	InitBiTree_lt(&Tnew);
	Copy_lt(T,&Tnew);
	printf("\nǰ�����������Tnew:");
	PreOrderTraverse_lt(Tnew);

	e1 = 'E';
	TRs = RightSibling_lt(T, e1);
	if (TRs != NULL) {
		printf("\n���%c���ֵܽ��Ϊ%c", e1, TRs->data);
	}

	TLs = LeftSibling_lt(T,e1);
	if (TLs != NULL)
	{
		printf("\n���%c���ֵܽ��Ϊ%c", e1, TLs->data);
	}

	ClearBiTree_lt(&T);
	printf("\n����ն�������,���շ�%d(1:�� 0:��) �������=%d\n", BiTreeEmpty_lt(T), BiTreeDepth_lt(T));
	
	return 0;
}