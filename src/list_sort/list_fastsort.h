//
// Created by xyx on 11/11/20.
//

#ifndef TEST_LIST_FASTSORT_H
#define TEST_LIST_FASTSORT_H
#include "listnode.h"
void _partional(ListNode *&head, ListNode *&ref)
{
    //get the ref node
    //small than ref node will be put forward of the ref, the bigger wille be put backward
    ref = head;
    ListNode* newhead = ref;
    ListNode *cur = ref->next;
    ListNode *pre = ref;
    ListNode *infrontRef = nullptr;
    while(nullptr != cur)
    {
        if(cur->val < ref->val)
        {
            if(nullptr != infrontRef)
            {
                infrontRef->next = cur;
                ListNode *tmp = cur->next;
                cur->next = ref;
                pre->next = tmp;
                infrontRef = cur;
            }
            else
            {
                newhead = cur;
                infrontRef = cur;
                ListNode *tmp = cur->next;
                cur->next = ref;
                pre->next = tmp;
            }
        }
        else
        {
            pre = pre->next;
        }
        cur = pre->next;
    }
    head = newhead;
}

ListNode* fastSort(ListNode *head)
{
    if(nullptr == head || nullptr == head->next)
        return head;

    ListNode *partnode = nullptr;
    _partional(head, partnode);
    ListNode *r = fastSort(partnode->next);
    partnode->next = nullptr;
    ListNode *l = fastSort(head);
    partnode->next = r;
    return l;
}
#endif //TEST_LIST_FASTSORT_H
