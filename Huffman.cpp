#include <iostream>
using namespace std;
struct TNode
{
    int freq;
    char info;
    bool unicodes[100];
    int len;
    struct TNode *left;
    struct TNode *right;
    struct TNode *next;
};
struct TNode *GetTNode(char x, int f)
{
    struct TNode *newNode;
    newNode = new (struct TNode);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->next = NULL;
    newNode->info = x;
    newNode->freq = f;
    newNode->len = 0;
    return newNode;
}

void InsBeg(struct TNode **S, struct TNode *N)
{
    N->next = *S;
    *S = N;
}

// Insert After
void InsAfter(struct TNode **P, struct TNode *N)
{
    if (*P == NULL)
    {
        cout << "Void Insertion" << endl;
        exit(1);
    }
    else
    {
        N->next = (*P)->next;
        (*P)->next = N;
    }
}
// Traverse
void Transverse(struct TNode *Start)
{
    struct TNode *P = Start;
    while (P != NULL)
    {
        cout << P->info << " " << P->freq << endl;
        P = P->next;
    }
    cout << endl;
}
struct TNode *delbeg(struct TNode **start)
{
    if (*start != NULL)
    {
        struct TNode *Q = *start;
        *start = (*start)->next;
        return Q;
    }
    else
    {
        cout << "Void Deletion";
        exit(1);
    }
}
int CountNode(struct TNode **Start)
{
    struct TNode *P = *Start;
    int count = 0;
    while (P != NULL)
    {
        count++;
        P = P->next;
    }
    return count;
}

void Insert(struct TNode **Start, struct TNode *N)
{
    struct TNode *P = *Start;
    if ((*Start) == NULL)
    {
        InsBeg(&(*Start), N);
    }
    else
    {
        struct TNode *Q = NULL;
        while (P != NULL && N->freq >= P->freq)
        {
            Q = P;
            P = P->next;
        }
        if (Q == NULL)
            InsBeg(&(*Start), N);
        else
            InsAfter(&Q, N);
    }
}

void InOrder(struct TNode *T)
{
    if (T != NULL)
    {
        InOrder(T->left);
        if (T->left == NULL && T->right == NULL)
        {
            cout << " " << T->info << "    " << T->freq << "     ";
            for (int i = 0; i <= T->len; i++)
            {

                cout << T->unicodes[i] << " ";
            }
        }
        cout << endl;
        InOrder(T->right);
    }
}
struct TNode *BuildHuffmanntree(struct TNode **N)
{
    int n = CountNode(N);
    struct TNode *Z = NULL;
    for (int i = 0; i < n - 1; i++)
    {
        struct TNode *X = delbeg(N);
        struct TNode *Y = delbeg(N);
        Z = GetTNode('Z', X->freq + Y->freq);
        Z->left = X;
        Z->right = Y;
        Insert(N, Z);
    }
    return Z;
}
void Unicodes(struct TNode **N, bool values[], int len)
{
    if (*N != NULL)
    {
        if (len != -1)
        {

            if ((*N)->left == NULL && (*N)->right == NULL)
            {
                (*N)->len = len;
                for (int i = 0; i <= len; i++)
                {
                    (*N)->unicodes[i] = values[i];
                }
            }
        }
        values[len + 1] = false;
        Unicodes(&(*N)->left, values, len + 1);
        values[len + 1] = true;
        Unicodes(&(*N)->right, values, len + 1);
    }
}
int main()
{
    struct TNode *Start = NULL;
    struct TNode *T = NULL;
    Insert(&Start, GetTNode('a', 50));
    Insert(&Start, GetTNode('r', 70));
    Insert(&Start, GetTNode('e', 30));
    Insert(&Start, GetTNode('n', 15));
    Insert(&Start, GetTNode('t', 15));
    Insert(&Start, GetTNode('s', 10));
    // Transverse(Start);
    T = BuildHuffmanntree(&Start);
    bool values[100];
    int len = -1;
    Unicodes(&T, values, len);
    cout << "Info"
         << "  "
         << "freq"
         << "  "
         << "  "
         << "unicodes" << endl;
    InOrder(T);
    return 0;
}