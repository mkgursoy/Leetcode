class Solution 
{
public:
    bool isMatch(string s, string p) 
    {
        vector<pair<char,int>> vec;
        for(int i = 0;(int)p.size() > i;i++)
        {
            if(i != (int)p.size() - 1 && p[i + 1] == '*' && p[i] != '*')
            {
                vec.push_back({p[i], 1});
            }
            else
            {
                if(p[i] != '*')
                {
                    vec.push_back({p[i], 0});
                }
            }
        }
        bool dp[(int)s.size() + 1][(int)vec.size()];
        if(vec[0].second)
        {
            bool all_good = true;
            for(int i = 1;(int)s.size() >= i;i++)
            {
                if(s[i - 1] != vec[0].first && vec[0].first != '.')
                {
                    all_good = false;
                }
                dp[i][0] = all_good;
            }
            dp[0][0] = true;
        }
        else
        {
            for(int i = 0;(int)s.size() >= i;i++)
            {
                dp[i][0] = false;
            }
            if(vec[0].first == s[0] || vec[0].first == '.')
            {
                dp[1][0] = true;
            }
        }
        for(int i = 0;(int)s.size() >= i;i++)
        {
            for(int j = 1;(int)vec.size() > j;j++)
            {
                auto [ch, tr] = vec[j];
                if(i == 0)
                {
                    dp[i][j] = (tr && dp[i][j - 1]);
                }
                else
                {
                    if(!tr)
                    {
                        bool all_good = true;
                        if(ch != s[i - 1] && ch != '.') all_good = false;
                        dp[i][j] = (dp[i - 1][j - 1] && all_good);
                    } 
                    else
                    {
                        dp[i][j] = dp[i][j - 1];
                        bool all_good = true;
                        for(int i1 = i;i1 > 0;i1--)
                        {
                            if(s[i1 - 1] != ch && ch != '.') all_good = false;
                            dp[i][j] |= (all_good && dp[i1 - 1][j - 1]);
                        }
                    }
                }
            }
        }
        return dp[(int)s.size()][(int)vec.size() - 1];
    }
};
/*
    Thoughts:

    -At first I though about simply trying every single way we could use each '*' sign, but even though
    this seems like it would work (there is about 10^7 ways to assign the number of uses to each), this 
    inevitably got TLE. So I had to find the actual solution which was pretty fun to think about.

    I came up with a solution that has about a O(N^2 * M) time complexity N and M being the sizes of s and p,
    respectively.

    Solution:

    We will use Dynamic Programming to solve this problem. In a DP problem you find these in order.

    1- State (What DP represents): DP[i][j] will be the answer for substrings s: [0, i] p: [0, j]. 

    2- Answer: DP[N][M], which basically is all of s and p involved.

    3- Transitions: This is the part it gets complicated.

    -The current state of p isn't very simple. We will represent p as pairs. {char ch, bool tr}:

    *ch represents the character and tr represents if it can be used multiple amount of times (if it has '*' after)

    -Now if we know the answer for s: [0, i] and p: [0, j - 1] we should examine what we can do with p[j]

    -If we can use it multiple find we can calculate s: [i, N] by simply adding the character multiple or zero times.

    -Otherwise, we HAVE to use it one time so we find out s : i + 1 p : j

    -The transitions for this are trivial, find out the base case j : 0 

    -Now you will see in my code i made the dp array not [N][M] but [N + 1][M]. This is because of 
    the zero uses rule. So the modified state is s : [0, i) p : [0, j] this is purely based on my implementation
    the logic won't change.

    -This is a tricky problem, and the explanation can also look pretty complicated I would suggest experimenting with it
    till you can confidently write the same yourself.
*/