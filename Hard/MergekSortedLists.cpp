/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution 
{
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) 
    {
        set<array<int,2>> st;
        for(int i = 0;(int)lists.size() > i;i++)
        {
            if(lists[i])
            {
                st.insert({lists[i]->val, i});
            }
        }
        if(!st.size()) return nullptr;
        ListNode* lt = new ListNode();
        ListNode* inc = lt;
        while(st.size())
        {
            auto [num, pos] = *st.begin();
            st.erase(st.begin());
            inc->val = num;
            if(lists[pos]->next)
            {
                lists[pos] = lists[pos]->next;
                st.insert({lists[pos]->val, pos});
            }
            if(st.size())
            {
                inc->next = new ListNode();
                inc = inc->next;
            }
        }
        return lt;
    }
};
/*
    Thoughts:

    -This is probably the easiest one I have solved so far. The actual technique is really
    well-known, so they probably added pointer stuff to add a layer into the problem.

    Solution:

    -We will apply the merge sort logic, which usually involves two lists, into multiple by
    using any data structure that can do insert, erase, find_min operations efficiently. I used set.

    -The key is that the linked lists are given sorted. Which means in the final linked list, every
    one of the k linked lists will appear as a subsequence in their initial order.

    -Hence, when sequentally forming the final linked list we only have to consider the current
    first unadded element in every list. This can be maintained trivially.

    -From all elements we consider, selecting the smallest and continuing with our algorithm will
    form the list.

    -While implementing this problem make sure to pay attention when to stop putting elements, as 
    the last element shouldn't be a new ListNode(), because it doesn't instantiate as nullptr you
    will have an extra 0 at the end.
*/