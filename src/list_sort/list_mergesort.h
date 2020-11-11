//
// Created by xyx on 11/11/20.
//

#ifndef TEST_LIST_MERGESORT_H
#define TEST_LIST_MERGESORT_H
#include "listnode.h"

ListNode* _merge_1(ListNode* list1, ListNode* list2);

ListNode* mergeSort(ListNode* head)
{
    if(nullptr == head || nullptr == head->next)
    {
        return head;
    }
    ListNode* fast = head;
    ListNode* slow = head;
    ListNode* pre  = slow;
    while(fast != nullptr && fast->next != nullptr)
    {
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode *r = mergeSort(slow);
    pre->next = nullptr;
    ListNode *l = mergeSort(head);
    return _merge_1(l ,r);
}

ListNode* _merge_1(ListNode* list1, ListNode* list2)
{
    ListNode *head  = new ListNode;
    ListNode *pre = head;
    while(list1 != nullptr && list2 != nullptr)
    {
        if(list1->val < list2->val)
        {
            pre->next = list1;
            list1 = list1->next;
        }
        else
        {
            pre->next = list2;
            list2 = list2->next;
        }
        pre = pre->next;
    }
    pre->next = list1 == nullptr ? list2 : list1;
    pre = head->next;
    delete(head);
    return pre;
}
#endif //TEST_LIST_MERGESORT_H
