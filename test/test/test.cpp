//
// Created by xyx on 11/4/20.
//
#include<cstdio>
#include<iostream>
using namespace std;

class test{
public:
    char a;
    char b;
    char c;
    char d;
    char e;
};

union node{
    union node *point;
    char client[1];
};

int main()
{
    char *chunk = new char[10];
    node* pnode = (node*)chunk;

    test* p  = (test*)pnode;

    p->a = 'a';
    p->b = 'b';
    p->c = 'c';
    p->d = 'd';
    p->e = 'e';
    printf("%lu,%lu, %lu,%lu,%lu\n", sizeof(test), sizeof(*p), sizeof(node), sizeof(*pnode), sizeof(chunk));
    printf("%p,%p, %p, %p\n",p,&p->a,&p->b,&p->c);
    printf("%p, %p, %p\n",pnode,pnode+1,pnode[2]);
    printf("%c,%c,%c,%c,%c\n", pnode[0], pnode[1], pnode[2], pnode[3], pnode[4]);
    return 0;
}