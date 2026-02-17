#define all(x) x.begin(), x.end()
class Solution 
{
    public:
    int find_xth_lowest(vector<int> nums1, vector<int> nums2, int x)
    {
        int l = 0, r = nums1.size() - 1;
        while(r >= l)
        {
            int mid = (l + r) / 2;
            int mn_low1 = lower_bound(all(nums1), nums1[mid]) - nums1.begin();
            int mx_low1 = upper_bound(all(nums1), nums1[mid]) - nums1.begin() - 1;
            int mn_low2 = lower_bound(all(nums2), nums1[mid]) - nums2.begin();
            int mx_low2 = upper_bound(all(nums2), nums1[mid]) - nums2.begin();
            int mn_low = mn_low1 + mn_low2;
            int mx_low = mx_low1 + mx_low2;

            if(mx_low >= x && x >= mn_low)
            {
                return nums1[mid];
            }
            if(x > mx_low)
            {
                l = mid + 1;
            }
            if(mn_low > x)
            {
                r = mid - 1;
            }
        }
        l = 0, r = nums2.size() - 1;
        while(r >= l)
        {
            int mid = (l + r) / 2;
            int mn_low1 = lower_bound(all(nums1), nums2[mid]) - nums1.begin();
            int mx_low1 = upper_bound(all(nums1), nums2[mid]) - nums1.begin();
            int mn_low2 = lower_bound(all(nums2), nums2[mid]) - nums2.begin();
            int mx_low2 = upper_bound(all(nums2), nums2[mid]) - nums2.begin() - 1;
            int mn_low = mn_low1 + mn_low2;
            int mx_low = mx_low1 + mx_low2;

            if(mx_low >= x && x >= mn_low)
            {
                return nums2[mid];
            }
            if(x > mx_low)
            {
                l = mid + 1;
            }
            if(mn_low > x)
            {
                r = mid - 1;
            }
        }
        return -1;
    }
    double findMedianSortedArrays(vector<int> nums1, vector<int> nums2) 
    {
        if(nums1.size() > nums2.size())
        {
            return findMedianSortedArrays(nums2, nums1);
        }    
        if(nums1.size() == 0)
        {
            return (double)(nums2[nums2.size() / 2] + nums2[(nums2.size() - 1) / 2]) / 2.0L;
        }
        int med_low = find_xth_lowest(nums1, nums2, (nums1.size() + nums2.size() - 1) / 2);
        int med_high = find_xth_lowest(nums1, nums2, (nums1.size() + nums2.size()) / 2);
        return (double)(med_low + med_high) / 2.0L;
    }
};

/*
    Thoughts:

    -This is not a straightforward problem. Easiest way to solve it would be to combine both arrays in
    O(N + M) complexity, and then finding median in O(1). This would also be a pretty efficient solution.
    However O(N + M) is not allowed by Leetcode forcing us to rely on another solution.

    My solution for this problem is O(log^2(N + M)) which is the most efficient I could come up with.

    Solution:

    -To avoid cases considering odd and even length arrays we can slightly alter the definition of a median by
    stating it to be (A[N / 2] + A[(N - 1) / 2]) / 2, in an array A of length N. Note that this also works for 
    odd length arrays as the N / 2'th and (N - 1) / 2'th elements are the same in that case.

    -We now need to have a way to calculate the i'th number in the final array without actually merging them.

    -To check if a number Z can be the i'th element lets check the following:

    * Z has to be in either nums1 or nums2

    * If when the array is merged i1 elements from nums1, and i2 elements from nums2 come before Z i1 + i2 = i

    * Because an element can be in multiple different places in the final array (elements aren't necessarily distinct)
    we should find the hypotetical first and last place it can be in. If i is in between these places there will exist a way
    for Z to be the i'th number in the final array.

    There are two builtin functions upperbound() and lowerbound(), finding the first element greater than or greater-equal than
    a number in an array respectively. We can use these to figure out how many elements are smaller.

    -Lets define four numbers mx_1, mx_2, mn_1, mn_2: representing the maximal elements from nums1 and nums2 that can be in the final
    array before Z and minimal elements from nums1 and nums than can be in the final array before Z.

    -If mx_1 + mx_2 >= i >= mn_1 + mn_2 than Z can be in the i'th position.

    -----------------------------------------------------------------

    -After this we should find the 2 elements to find our final median.

    -function(i) will return the value of the i'th element in the final array: Z.

    -To do such lets assume Z to be in nums1, and if it doesn't work then try nums2.

    -If possible Z in nums1 doesnt fit requirements there can be 2 cases:

    * Either it is too small for possibly being i, i > mx_1 + mx_2 (We should look at bigger elements)

    * Or it is too big for possibly being i, mn_1 + mn_2 > i (We should look at smaller elements)

    Hence, using Binary Search is the most practical way to find the number.

    Binary Search is O(logN) and Checking is O(logN) resulting in the final complexity of O(log^2(N + M))
*/