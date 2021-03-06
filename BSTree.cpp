/**
二分查找树
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Tree{
        int data;
        struct Tree *left;
        struct Tree *right;
} BSTree;

BSTree* createBSTree() {
     BSTree *root = (BSTree *) calloc(sizeof(BSTree), sizeof(char));
     int tmp;
     scanf("%d", &tmp);
     root->data = tmp;
     root->left = NULL;
     root->right = NULL;

     while(scanf("%d", &tmp) != EOF) {
         BSTree *ins = root;
         while(1) {
             if(ins->data >= tmp) {
                 if(ins->left != NULL) {
                     ins = ins->left;
                     continue;
                 } else {
                     BSTree *newItem = (BSTree *) calloc(sizeof(BSTree), sizeof(char));
                     newItem->data = tmp;
                     newItem->left = NULL;
                     newItem->right = NULL;
                     ins->left = newItem;
                     break;
                 }
             } else {
                 if(ins->right != NULL) {
                     ins = ins->right;
                     continue;
                 }  else {
                     BSTree *newItem = (BSTree *) calloc(sizeof(BSTree), sizeof(char));
                     newItem->data = tmp;
                     newItem->left = NULL;
                     newItem->right = NULL;
                     ins->right = newItem;
                     break;
                 }
             }
         }
     }
     return root;
}
//中序遍历
void inorder(BSTree *bTree) {
    if(bTree == NULL)
        return;
    inorder(bTree->left);
    printf("%d,", bTree->data);
    inorder(bTree->right);
}

struct LiNode{
	int access;
	BSTree *item;
	struct LiNode* next;
};

struct LiNode *header = NULL;

void deal() {
	BSTree *ptr = header->item;
	header->access = 1;
	if (ptr->right != NULL) {
		struct LiNode *right= (LiNode *) malloc(sizeof(LiNode));
		right->access = 0;
		right->next = header->next;
		header->next = right;
		right->item = ptr->right;
	}
	if (ptr->left != NULL) {
		struct LiNode *left = (LiNode *) malloc(sizeof(LiNode));
		left->access = 0; 
		left->item = ptr->left;
		left->next = header;
		header = left;
	}
}
//非递归中序
void inorder_(BSTree *root) {
	if (root == NULL)
		return;
	BSTree *ptr = root;
	bool first = true;
	while (first || header != NULL) {
		first = false;
		if(header == NULL) {
			struct LiNode *item = (LiNode *) malloc(sizeof(LiNode));
			item->access = 1;
			item->item = ptr;
			item->next = NULL;
			header = item;
			deal();
		} else {
			if (++(header->access) < 2) {
				deal();
			} else {
				printf("%d,", header->item->data);
				header = header->next;
			}
		}
	}
}
//先序遍历递归
void preorder(BSTree *bTree) {
    if(bTree == NULL)
        return;
    printf("%d,", bTree->data);
    preorder((bTree->left));
    preorder((bTree->right));
}
BSTree *array1[1000];
//非递归先序
void preorder_(BSTree *root) {
	if (root == NULL)
		return;
	BSTree *ptr = root;
	int bottom = 0, top = 0;
	bool first = true;
	while (top < bottom || first) {
		first = false;
		if(ptr != NULL) {
			printf("%d,", ptr->data);
			array1[bottom++] = ptr->left;
			array1[bottom++] = ptr->right;
		}
		ptr = array1[top++];
	}
}
//后序遍历
void postorder(BSTree *bTree) {
    if(bTree == NULL)
        return;
    postorder(bTree->left);
    postorder(bTree->right);
    printf("%d,", bTree->data);

}
void deal_post() {
	BSTree *ptr = header->item;
	header->access = 1;
	if (ptr->right != NULL) {
		struct LiNode *right= (LiNode *) malloc(sizeof(LiNode));
		right->access = 0;
		right->next = header;
		right->item = ptr->right;
		header = right;
	}
	if (ptr->left != NULL) {
		struct LiNode *left = (LiNode *) malloc(sizeof(LiNode));
		left->access = 0; 
		left->item = ptr->left;
		left->next = header;
		header = left;
	}
}
//非递归后序
void postorder_(BSTree *bTree) {
	if(bTree == NULL)
		return;
	BSTree *ptr = root;
	bool first = true;
	while (first || header != NULL) {
		first = false;
		if(header == NULL) {
			struct LiNode *item = (LiNode *) malloc(sizeof(LiNode));
			item->access = 1;
			item->item = ptr;
			item->next = NULL;
			header = item;
			deal_post();
		} else {
			if (++(header->access) < 2) {
				deal_post();
			} else {
				printf("%d,", header->item->data);
				header = header->next;
			}
		}
	}
}




int max(int a, int b) {
    if (a >= b)
        return a;
    return b;
}

//树的最大深度
int depth_of_tree(BSTree *bTree) {
    if(bTree == NULL)
        return 0;
    return 1 + max(depth_of_tree(bTree->left), depth_of_tree(bTree->right));
}

static BSTree *array[100];
static int depth;
void display(BSTree *item, int layer, bool flag) {
	//printf("print item->data:%d\n", item->data->data);
	for (int i=0; i<depth-layer; i++)
		printf(" ");
	if (item == NULL)
		printf(" ");
	else 
		printf("%d", item->data);
	if(flag)
		printf(" ");
}
//怎样从顶部开始逐层打印二叉树结点数据
void printByLayer(BSTree *bTree) {
    depth = depth_of_tree(bTree);
    printf("depth is %d\n", depth);
    BSTree *ptr = bTree;
	array[0] = ptr;
	int id = 0, last=0;
    for(int i=1; i<=depth; i++) {
		int k = pow(2, i-1);
		bool left = true;//打印标记
		while(k>0) {
			display(array[id], i, left);
			if(array[id] == NULL) {
				array[++last] = NULL;
				array[++last] = NULL;
			} else {
				//printf("Enqueue %d,%d\n", item->data->left->data, item->data->right->data);
				array[++last] = array[id]->left;
				array[++last] = array[id]->right;
			}
			k--;
			id++;
			left = !left;
    	}
		printf("\n");
	}
}
//是否是平衡二叉树
bool isBalanceTree(BSTree *bTree) {
	if(bTree == NULL) 
		return true;
	return (abs(depth_of_tree(bTree->left) - depth_of_tree(bTree->right)) <= 1);
}

int numOfChild(BSTree *tTree, BSTree* ch1, BSTree *ch2) {
	if (tTree == NULL)
		return 0;
	if(tTree == ch1 || tTree == ch2)
		return 1;
	int left = 0, right = 0;
	left = numOfChild(tTree->left, ch1, ch2);
	right = numOfChild(tTree->right, ch1, ch2);
	return left + right;
}

//二叉树上任意两个节点的最近共同父结点
BSTree *commonFather(BSTree *tTree, BSTree* ch1, BSTree* ch2) {
	int left = 0, right = 0;
	left = numOfChild(tTree->left, ch1, ch2);
	right = numOfChild(tTree->right, ch1, ch2);

	if (left == 2) return commonFather(tTree->left, ch1, ch2);
	if (right == 2) return commonFather(tTree->right, ch1, ch2);
	if (left == 1 && right == 1) return tTree;
	return NULL;
}	

//求二叉树的镜像
void treeImage(BSTree *tree) {
	if (tree == NULL)
		return;
	BSTree *tmp = tree->left;
	tree->left = tree->right;
	tree->right = tmp;
	treeImage(tree->left);
	treeImage(tree->right);
}
//TODO add other algorithm
int main() {
    BSTree *root = createBSTree();
    printf("中序遍历: ");
    inorder(root);
    printf("\n先序遍历： ");
    preorder(root);
    printf("\n后序遍历：");
    postorder(root);
    printf("\n逐层遍历：");
    printByLayer(root);
	if(isBalanceTree(root))
		printf("is balance tree\n");
	else 
		printf("not a balance tree\n");
}
