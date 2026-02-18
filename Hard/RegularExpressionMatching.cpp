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