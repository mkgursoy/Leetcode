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
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) 
    {
        if(k == 1) return head;
        ListNode* new_head = head;
        bool bb = true;
        ListNode* last_strt;
        ListNode* actual_start = head;
        while(new_head)
        {
            ListNode* prev = new_head;
            ListNode* strt = new_head;
            bool b = true;
            for(int i = 0;k - 1 > i;i++)
            {
                if(!(new_head -> next))
                {
                    b = false;
                    break;
                }
                new_head = new_head -> next;
            }
            if(!b)
            {
                break;
            } 
            new_head = strt;
            new_head = new_head->next;
            prev = strt;
            for(int i = 0;k - 1 > i;i++)
            {
                strt->next = new_head->next;
                new_head->next = prev;
                prev = new_head;
                new_head = strt->next;
            }
            if(bb)
            {
                actual_start = prev;
                bb = false;
            }
            else
            {
                last_strt->next = prev;
            }
            last_strt = strt;
            
        }
        return actual_start;
    }
};
/*
    Thoughts:

    -This was actually really enjoyable, coming up with a solution for the O(1) extra question was really enjoyable
    I'm not going to explain the original question, as its pretty straight-forward.

    Solution:

    -First of all we have to find a way to reverse K nodes in a row, so let N = K. We will execute the following algorithm:

    -Lets be at node i, the next should be the one previous to reverse. But if we do that we now don't have access to
    the original next, so we cannot continue.

    -To solve this we first set the first nodes next to our original next. This way by using the first nodes next we can
    continue traversing. And at the end the first nodes next will be nullptr, so its convinient.

    -I will visualize this step for it to more clear. Say our list is 1 -> 2 -> 3.

    1 -> 2 -> 3 -> (nullptr) (initial)

    2 -> 1 -> 3 -> (nullptr) (set 1s next to 3, and 2s next to 1)

    3 -> 2 -> 1 -> (nullptr) (set 3s next to 1, and 1s next to (nullptr))

    -The only problem now is that, the original head node (1) is the last node now. So if we return that we only return a 
    linked list with size 1 (1 -> (nullptr)). So we will return the last node in the original linked list (3).

    -Lets now figure out how to merge some set of K reversed lists:

    -Let a list be 1 -> 2 -> 3 -> 4 -> 5 -> 6 and K is 3.

    -If we execute the first algorithm only we now have list: 3 -> 2 -> 1 -> 4 <- 5 <- 6.

    -Which means we lost 5 and 6. To fix this problem we will do the exact same thing at start. Set 1's next to 6.
    This will be called "the merging fix"

    -We have now solved problem for k * x = n (x is an integar > 0). But there can be some that isn't supposed to be 
    reversed.
    
    -That can easily be found if the last part has length smaller than k. When that happens just break the loop, as
    the next of the last block will remain the first of the last block if we don't use the merging fix.

    Now lets visualize the final algorithm for 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8:

    1) 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> (nullptr)

    2) 2 -> 1 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> (nullptr)

    3) 3 -> 2 -> 1 -> 4 -> 5 -> 6 -> 7 -> 8 -> (nullptr)

    4) 3 -> 2 -> 1 -> 4 <- 5              5) 3 -> 2 -> 1 -> 4 <- 5 <- 6
                      |                                     |
                      v                                     v
                      6                                     7
                      |                                     |
                      v                                     v
                      7                                     8
                      |                                     |
                      v                                     v
                      8                                  (nullptr)
                      |
                      v
                  (nullptr)

    6) 3 -> 2 -> 1 -> 6 -> 5 -> 4 -> 7 -> 8 -> (nullptr): Our result.

            

*/