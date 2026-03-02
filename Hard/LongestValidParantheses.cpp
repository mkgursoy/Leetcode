class Solution {
public:
    int longestValidParentheses(string s) 
    {
        int n = (int)s.size();
        if(n == 0)
        {
            return 0;
        }
        int dp[n];
        dp[0] = 0;
        for(int i = 1;n > i;i++)
        {
            if(s[i] == '(')
            {
                dp[i] = 0;
            }
            else
            {
                if(s[i - 1] == '(')
                {
                    if(i >= 2)
                    {
                        dp[i] = dp[i - 2] + 2;
                    }
                    else
                    {
                        dp[i] = 2;
                    }
                }
                else
                {
                    if(i == dp[i - 1])
                    {
                        dp[i] = 0;
                    }
                    else
                    {
                        if(s[i - 1 - dp[i - 1]] == '(')
                        {
                            if(i - 1 - dp[i - 1] == 0)
                            {
                                dp[i] = i + 1;
                            }
                            else
                            {
                                dp[i] = dp[i - 1] + 2 + dp[i - 2 - dp[i - 1]];
                            }
                        }
                        else
                        {
                            dp[i] = 0;
                        }
                    }
                }
            }
        } 
        return *max_element(dp, dp + n);   
    }
};
/*
	Thoughts:
	
	-This was a pretty fun problem. I don't think DP was the intended way here but this was the easiest solution
	I could find.
	
	Solution:

	-There are two ways to construct a valid bracket sequence:

	1) VALID + VALID
	2) ( + VALID + )

	-Now using these lets try to create a DP solution. Its clear we need an O(N) solution here. (or NlogN maybe
	but that doesn't concern our state generally.)

	-Let dp[i] denote the length of the longest valid sequence ending at index i (0 based). Base Case will be i = 0
	in which case, dp[0] = 0, and our answer will be the maximum element of the dp array.

	-Now let's find out the transition. If s[i] = '(', dp[i] will be 0 as no valid sequence can end with '('.

	-Lets first go for the second way to construct. Because we want to try increase the answer we should at least
	try to find an answer bigger than dp[i - 1]. If we try to find the longest valid from i, and set the left bound
	j, j must be less than to i - dp[i - 1] which is the end of the longest valid from i - 1.
	
	Proof: In a VBS (Valid Bracket Sequence) at every suffix the number of '(' should be less or equal to the number of
	')'. otherwise at least one '(' will remain unclosed, invalidating the sequence. If there existed a j greater than
	i - dp[i - 1] that means from j to i there should be equal '(' and ')'. But, remember that s[i] = ')', this would mean
	from j to i - 1 (a suffix of the VBS that i - 1 created) there are more '(' than ')'. This is a contradiction.
	
	-Now we can check if the VBS created by i - 1 can be increased by 2 by the second way, this is only possible
	if s[i - 1 - dp[i - 1]] == '(' which makes '(' + VALID + ')'.

	-For the first way notice that the one above was the biggest way to make the second VALID we require to construct
	a VBS by way 1. So we can simply check the biggest made by i - 2 - dp[i - 1], which is the first VALID so we 
	can get VALID + VALID.

	-This was a tough one to explain, but feel free to experiment with this solution to try understanding it better.

	
*/