//
// Created by xyx on 11/11/20.
//

#include "listnode.h"
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include "list_mergesort.h"
#include "list_mergesort_stl.h"
#include "list_fastsort.h"
using namespace std;

void sortVerify(ListNode *head)
{
    ListNode * cur = head;
    while(nullptr != cur && nullptr != cur->next)
    {
        if(cur->val > cur->next->val)
        {
            cout<<"false" << endl;
            return;
        }
        cur = cur->next;
    }
    cout<< "true" << endl;
}

ListNode* genLink(int n = 10)
{
    vector<int> vec(n,0);
    random_device random_seed;
    mt19937 eng(random_seed());
    for(auto &it : vec)
    {
        it = eng();
    }

    ListNode *head = nullptr;
    ListNode *pre  = nullptr;
    for(auto it : vec)
    {
        ListNode* cur = new ListNode(it);
        if(nullptr == head)
            head = cur;
        if(nullptr != pre)
            pre->next = cur;
        //cout<< it << " ";
        pre = cur;
    }
    //cout<< endl;
    return head;
}

void listSort_test(ListNode*(*func)(ListNode*),int n = 10)
{
    clock_t start,end;
    double duration;
    ListNode *head = genLink(n);
    start = clock();
    ListNode *res = func(head);
    end = clock();
    sortVerify(res);
    duration = (double)(end - start);
    cout<< " " << duration << endl;
}

int main(int argc, char *argv[])
{
    cout<< "mergeSort_stl" << endl;
    listSort_test(mergeSort_stl, 1000);

    cout<< "mergeSort" << endl;
    listSort_test(mergeSort, 1000);

    cout<< "fastSort" << endl;
    listSort_test(fastSort, 1000);

    return 0;
}

