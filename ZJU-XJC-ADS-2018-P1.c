#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define ElemType int

typedef struct BSTNode *Position;
typedef Position BinTree;
struct BSTNode{
    ElemType Data;
    BinTree Left;
    BinTree Right;
    BinTree Parent;
};


Position I, Head;
int Max(int a, int b);
int GetHeight(BinTree T);
BinTree BSTInsert(BinTree BST, ElemType X);
BinTree BSTDelete(BinTree BST, ElemType X);
BinTree AVLInsert(BinTree AVL, ElemType X);
BinTree AVLDelete(BinTree AVL, ElemType X);
BinTree LLRotation(BinTree T);
BinTree LRRotation(BinTree T);
BinTree RLRotation(BinTree T);
BinTree RRRotation(BinTree T);
BinTree Splay(BinTree ST, Position I);
BinTree SplayInsert(BinTree ST, ElemType X);
BinTree SplayDelete(BinTree ST, ElemType X);
BinTree ZIG(BinTree T);
BinTree ZAG(BinTree T);
BinTree ZIGZAG(BinTree T);
BinTree ZAGZIG(BinTree T);

int main(void)
{
    int a[10001];   // insert sequence,a[0] and b[0] are the size of operation
    int b[10001];   // delete sequence(in random)
    int i, j;
    int n;
    clock_t start, finish, time;
    
    printf("1.BST     2.AVL     3.Splay\n");
    scanf("%d", &n);

    // import sequence with file operation
    // data
    FILE *fp1;
    if((fp1 = fopen("/Users/mac/Desktop/Ads/p1/c2/data1.txt", "r")) == NULL) {
        printf("error, cannot open file1.");
        return -1;
    }
    // sequence
    FILE *fp2;
    if((fp2 = fopen("/Users/mac/Desktop/Ads/p1/c2/data2.txt", "r")) == NULL) {
        printf("error, cannot open file2.");
        return -1;
    }


    time = 0;
    if(n == 1)
    {
        fscanf(fp1, "%d", &a[0]);
        fscanf(fp2, "%d", &b[0]);
        for(i = 0; i < a[0]; i++)
            fscanf(fp1, "%d", &a[i + 1]);
        for(i = 0; i < a[0]; i++)
            fscanf(fp2, "%d", &b[i + 1]);
        BinTree T = NULL;
        for(j = 0; j <= 100; j++)
        {
            for ( i = 1; i < a[0]; i++ ) {
                start = clock();
                T = BSTInsert(T, a[i]);
                finish = clock();
                time += finish - start;
            }
            for ( i = 1; i < b[0]; i++ ) {
                start = clock();
                T = BSTDelete(T, b[i]);
                finish = clock();
                time += finish - start;
            }
        }
        printf("%ld\n", time);
    }

    else if(n == 2)
    {
        fscanf(fp1, "%d", &a[0]);
        fscanf(fp2, "%d", &b[0]);
        for(i = 0; i < a[0]; i++)
            fscanf(fp1, "%d", &a[i + 1]);
        for(i = 0; i < a[0]; i++)
            fscanf(fp2, "%d", &b[i + 1]);
        BinTree T = NULL;
        for(j = 0; j <= 100; j++)
        {
            for ( i = 1; i < a[0]; i++ ) {
                start = clock();
                T = AVLInsert(T, a[i]);
                finish = clock();
                time += finish - start;
            }
            for ( i = 1; i < b[0]; i++ ) {
                start = clock();
                T = AVLDelete(T, b[i]);
                finish = clock();
                time += finish - start;
            }
        }
        printf("%ld\n", time);
    }

    else if(n == 3)
    {
        fscanf(fp1, "%d", &a[0]);
        fscanf(fp2, "%d", &b[0]);
        for(i = 0; i < a[0]; i++)
            fscanf(fp1, "%d", &a[i + 1]);
        for(i = 0; i < a[0]; i++)
            fscanf(fp2, "%d", &b[i + 1]);
        BinTree T = NULL;
        for(j = 0; j <= 100; j++)
        {
            for( i = 1; i < a[0]; i++ ) {
                start = clock();
                T = SplayInsert(T, a[i]);
                T = Splay(T, I);
                finish = clock();
                time += finish - start;
            }
            for ( i = 1; i < b[0]; i++ ) {
                start = clock();
                T = SplayDelete(T, b[i]);
                T = Splay(T, I);
                finish = clock();
                time += finish - start;
            }
        }
        printf("%ld\n", time);
    }
    fclose(fp1);
    fclose(fp2);

    return 0;
}

int Max(int a, int b)
{
    return a > b ? a:b;
}

int GetHeight(BinTree T)
{
    if(T)  return(Max(GetHeight(T->Left), GetHeight(T->Right)) + 1);
    else  return 0;
}

BinTree BSTInsert(BinTree BST, ElemType X)
{
    if(!BST)
    {
        BST = (BinTree)malloc(sizeof(struct BSTNode));
        BST->Data = X;
        BST->Left = BST->Right = BST->Parent = NULL;
    }
    else
    {
        if(X < BST->Data)
            BST->Left = BSTInsert(BST->Left, X);
        else if(X > BST->Data)
            BST->Right = BSTInsert(BST->Right, X);
    }
    return BST;
}

BinTree BSTDelete(BinTree BST, ElemType X)
{
    if(!BST)
        printf("Element %d can't be found!", X);
    else
    {
        if(X < BST->Data)
            BST->Left = BSTDelete(BST->Left, X);
        else if(X > BST->Data)
            BST->Right = BSTDelete(BST->Right, X);
        else
        {
            Position Tmp;
            if(BST->Left && BST->Right)
            {
                Tmp = BST->Right;
                while(Tmp->Left)
                    Tmp = Tmp->Left;//Find the smallest element from BST->Right， and replace the elements to be deleted
                BST->Data = Tmp->Data;
                BST->Right = BSTDelete(BST->Right, BST->Data);
            }
            else
            {
                Tmp = BST;
                if(!BST->Left)
                    BST = BST->Right;
                else
                    BST = BST->Left;
            }
            free(Tmp);
        }
    }
    return BST;
}

BinTree AVLInsert(BinTree AVL, ElemType X)
{
    if(!AVL)
    {
        AVL = (BinTree)malloc(sizeof(struct BSTNode));
        AVL->Data = X;
        AVL->Left = AVL->Right = AVL->Parent = NULL;
    }

    else if(X < AVL->Data)
    {
        AVL->Left = AVLInsert(AVL->Left, X);
        AVL->Left->Parent = AVL;
        if(GetHeight(AVL->Left) - GetHeight(AVL->Right) == 2)
        {
            if(X < AVL->Left->Data)
                AVL = LLRotation(AVL);
            else
                AVL = LRRotation(AVL);
        }
    }

    else if(X > AVL->Data)
    {
        AVL->Right = AVLInsert(AVL->Right, X);
        AVL->Right->Parent = AVL;
        if(GetHeight(AVL->Left) - GetHeight(AVL->Right) == -2)
        {
            if(X > AVL->Right->Data)
                AVL = RRRotation(AVL);
            else
                AVL = RLRotation(AVL);
        }
    }

    return AVL;
}

BinTree AVLDelete(BinTree AVL, ElemType X)
{
    if(!AVL)
        printf("Element %d can't be found!", X);
    else
    {
        if(X < AVL->Data)
            AVL->Left = AVLDelete(AVL->Left, X);
        else if(X > AVL->Data)
            AVL->Right = AVLDelete(AVL->Right, X);
        else
        {
            Position Tmp;
            if(AVL->Left && AVL->Right)
            {
                Tmp = AVL->Right;
                while(Tmp->Left)
                    Tmp = Tmp->Left;
                AVL->Data = Tmp->Data;
                AVL->Right = AVLDelete(AVL->Right, AVL->Data);
            }
            else
            {
                Tmp = AVL;
                if(!AVL->Left)
                    AVL = AVL->Right;
                else
                    AVL = AVL->Left;
                AVL->Parent = Tmp->Parent;
            }
            free(Tmp);
        }
        if(GetHeight(AVL->Left) - GetHeight(AVL->Right) == -2)
        {
            if(X > AVL->Right->Data)
                AVL = RRRotation(AVL);
            else
                AVL = RLRotation(AVL);
        }
        else if(GetHeight(AVL->Left) - GetHeight(AVL->Right) == 2)
        {
            if(X < AVL->Left->Data)
                AVL = LLRotation(AVL);
            else
                AVL = LRRotation(AVL);
        }
    }
    return AVL;
}

BinTree LLRotation(BinTree T)
{
    Position P = T->Parent;
    BinTree L = T->Left;
    T->Left = L->Right;
    L->Right->Parent = T;
    L->Right = T;
    T->Parent = L;
    L->Parent = P;

    return L;
}

BinTree RRRotation(BinTree T)
{
    Position P = T->Parent;
    BinTree R = T->Right;
    T->Right = R->Left;
    R->Left->Parent = T;
    R->Left = T;
    T->Parent = R;
    R->Parent = P;

    return R;
}

BinTree LRRotation(BinTree T)
{
    T->Left = RRRotation(T->Left);
    return LLRotation(T);
}

BinTree RLRotation(BinTree T)
{
    T->Right = LLRotation(T->Right);
    return RRRotation(T);
}

BinTree Splay(BinTree ST, Position I)
{
    Position P, G;

    P = I->Parent;
    while(P != NULL) {
        G = P->Parent;
        if (I == P->Left) {
            if (G == NULL)
                ZIG(P);
            else if (P == G->Left) {
                ZIG(P);
                ZIG(G);
            } else
                ZIGZAG(G);
        } else {
            if (G == NULL)
                ZAG(P);
            else if (P == G->Right) {
                ZAG(P);
                ZAG(G);
            } else
                ZAGZIG(G);
        }

        P = I->Parent;
    }
    return I;
}

BinTree SplayInsert(BinTree ST, ElemType X)
{
    if(!ST)
    {
        ST = (BinTree)malloc(sizeof(struct BSTNode));
        ST->Data = X;
        ST->Left = ST->Right = ST->Parent = NULL;
        I = ST;
    }
    else
    {
        if(X < ST->Data)
        {
            ST->Left = SplayInsert(ST->Left, X);
            ST->Left->Parent = ST;
        }
        else if(X > ST->Data)
        {
            ST->Right = SplayInsert(ST->Right, X);
            ST->Right->Parent = ST;
        }
    }
    return ST;
}

BinTree SplayDelete(BinTree ST, ElemType X)
{
    Position Tmp;
    if(!ST)
        printf("Element %d can't be found!", X);
    else
    {
        if(X < ST->Data)
            ST->Left = SplayDelete(ST->Left, X);
        else if(X > ST->Data)
            ST->Right = SplayDelete(ST->Right, X);
        else
        {
            if(ST->Left && ST->Right)
            {
                Tmp = ST->Right;
                while(Tmp->Left)
                    Tmp = Tmp->Left;
                ST->Data = Tmp->Data;
                ST->Right = SplayDelete(ST->Right, ST->Data);
                I = ST;
            }
            else
            {
                Tmp = ST;
                if(!ST->Left)
                {
                    ST = ST->Right;
                    I = ST->Parent;
                }
                else
                {
                    ST = ST->Left;
                    I = ST->Parent;
                }
                free(Tmp);
            }
        }
    }
    return ST;
}

BinTree ZIG(BinTree T)
{
    Position P = T->Parent;
    BinTree L = T->Left;
    T->Left = L->Right;
    L->Right->Parent = T;
    L->Right = T;
    L->Parent = T->Parent;
    T->Parent = L;
    L->Parent = P;

    return L;
}

BinTree ZAG(BinTree T)
{
    Position P = T->Parent;
    BinTree R = T->Right;
    T->Right = R->Left;
    R->Left->Parent = T;
    R->Left = T;
    R->Parent = T->Parent;
    T->Parent = R;
    R->Parent = P;

    return R;
}

BinTree ZIGZAG(BinTree T)
{
    T->Left = ZAG(T->Left);
    return ZIG(T);
}

BinTree ZAGZIG(BinTree T)
{
    T->Right = ZIG(T->Right);
    return ZAG(T);
}
