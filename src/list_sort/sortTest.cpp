//
// Created by xyx on 11/11/20.
//

#include "listnode.h"
#include <iostream>
#include <vector>
#include <random>
#include "list_mergesort.h"
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
        cout<< it << " ";
        pre = cur;
    }
    cout<< endl;
    return head;
}
int main(int argc, char *argv[])
{
    ListNode *head = genLink();
    printList(head);
    ListNode *res = mergeSort(head);
    printList(res);
    sortVerify(res);
    delete(head);
    delete(res);
    return 0;
}

