#include <iostream>
#include <fstream>
using namespace std;
#include "Huffman.h"
void WriteFile(ofstream *MyFile, struct TNode *T)
{
    if (T != NULL)
    {
        WriteFile(MyFile, T->left);
        if (T->left == NULL && T->right == NULL)
        {
            for (int x = 0; x < T->freq; x++)
            {
                for (int i = 0; i <= T->len; i++)
                {
                    *MyFile << T->unicodes[i];
                }
            }
        }
        WriteFile(MyFile, T->right);
    }
}
int main()
{
    struct TNode *Start = NULL;
    struct TNode *T = NULL;
    Insert(&Start, GetTNode('a', 5));
    Insert(&Start, GetTNode('r', 7));
    Insert(&Start, GetTNode('e', 3));
    Insert(&Start, GetTNode('n', 1));
    Insert(&Start, GetTNode('t', 1));
    Insert(&Start, GetTNode('s', 6));
    T = BuildHuffmanntree(&Start);
    bool values[100];
    int len = -1;
    Unicodes(&T, values, len);
    ofstream MyFile("encoded");
    WriteFile(&MyFile, T);
    MyFile.close();
    return 0;
}