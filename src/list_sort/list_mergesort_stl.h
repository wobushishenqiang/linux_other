//
// Created by xyx on 11/11/20.
//

#ifndef TEST_LIST_MERGESORT_STL_H
#define TEST_LIST_MERGESORT_STL_H
#include "listnode.h"
ListNode* _merge_stl(ListNode* list1, ListNode* list2)
{
    ListNode *head = new ListNode;
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
    pre->next =
            (list1 == nullptr ? list2 : list1);
    pre = head->next;
    delete(head);
    return pre;
}

ListNode* mergeSort_stl(ListNode* head)
{
    if(nullptr == head || nullptr == head->next)
    {
        return head;
    }
    ListNode *cur = head;
    ListNode *carry = nullptr;
    ListNode* counter[64] = {nullptr};
    int fill = 0;
    while(cur != nullptr)
    {
        //get one node
        ListNode* tmp = cur->next;
        cur->next = carry;
        carry = cur;
        cur = tmp;

        //merge 1 2 4 8 node...
        int i = 0;
        //!= nullptr before num of fill we whould put something in like fill == 4 we should fill in 1 2
        while(i < fill && counter[i] != nullptr)
        {
            counter[i] = _merge_stl(counter[i], carry);
            carry = nullptr;

            tmp = counter[i];
            counter[i] = carry;
            carry = tmp;
            i++;
        }
        //put the last merged list in counter
        tmp = counter[i];
        counter[i] = carry;
        carry = tmp;

        //when merge num of fill finish
        if(i == fill) ++fill;
    }

    for(int i = 1; i < fill; ++i)
    {
        counter[i] = _merge_stl(counter[i], counter[i-1]);
    }
    return counter[fill-1];


}
#endif //TEST_LIST_MERGESORT_STL_H
