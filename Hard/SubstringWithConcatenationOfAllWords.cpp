class Solution 
{
    const static long long INF = 1e17 , MOD = 1e9 + 7;
    long long mul(long long a,long long b,long long mod = MOD)
    {
        return a * 1LL * b % mod;
    }
    long long sum(long long a,long long b,long long mod = MOD)
    {
        return (a + b + mod) % mod;
    }
    long long binpow(long long base,long long power,long long mod = MOD)
    {
        if(power == 1) return base;
        if(power == 0) return 1LL;
        
        if(power % 2 == 1)
        {
            long long a;    
            a = binpow(base,power / 2,mod);
            return mul(base, mul(a, a, mod), mod);
        } 
        else
        {
            long long a;
            a = binpow(base,power / 2,mod);
            return mul(a, a, mod);
        }
    }
    long long inv(long long a,long long mod = MOD)
    {
        return binpow(a, mod - 2, mod) % mod;
    }
    public:
    vector<int> findSubstring(string s, vector<string>& words) 
    {
        long long total_cnt = 0;
        vector<long long> req(26);
        unordered_map<long long, long long> personal_req;
        for(auto s1 : words)
        {
            long long cur = 1LL;
            long long hsh = 0LL;
            for(auto it : s1)
            {
                total_cnt++;
                req[it - 'a']++;
                hsh = sum(hsh, mul((it - 'a' + 1), cur));
                cur = mul(cur, 53LL);
            }
            personal_req[hsh]++;
        }
        long long pref[(int)s.size()][26];
        for(long long i = 0;26 > i;i++)
        {
            long long prev = 0;
            for(long long j = 0;(int)s.size() > j;j++)
            {
                prev += (s[j] == (char)(i + 'a'));
                pref[j][i] = prev;
            }
        }
        long long hsh[(int)s.size()];
        long long inv_53[(int)s.size() + 1];
        long long hsh1 = 0;
        long long cur = 1LL;
        for(long long i = 0;(int)s.size() > i;i++)
        {
            hsh1 = sum(hsh1, mul((s[i] - 'a' + 1), cur));
            hsh[i] = hsh1;
            cur = mul(cur, 53LL);
        }
        inv_53[(int)s.size()] = inv(cur);
        for(long long i = (int)s.size() - 1;i >= 0;i--)
        {
            inv_53[i] = mul(53LL, inv_53[i + 1]);
        }
        vector<int> ans;
        for(long long i = 0;(int)s.size() > i + total_cnt - 1;i++)
        {
            vector<long long> us(26);
            for(long long j = 0;26 > j;j++)
            {
                us[j] = pref[i + total_cnt - 1][j] - (i ? pref[i - 1][j] : 0LL);
            }
            if(us == req)
            {
                unordered_map<long long,long long> mp;
                mp = personal_req;
                long long len = words.back().size();
                long long lb = i;
                bool f = true;
                for(auto useless : words)
                {
                    long long hsh_substring = sum(hsh[lb + len - 1], -(lb ? hsh[lb - 1] : 0LL));
                    hsh_substring = mul(hsh_substring, inv_53[lb]);
                    if(!mp.count(hsh_substring))
                    {
                        f = !f;
                        break;
                    }
                    mp[hsh_substring]--;
                    if(mp[hsh_substring] == 0) mp.erase(hsh_substring);
                    lb += len;
                }
                if(f)
                {
                    ans.push_back(i);
                }
            }
        }
        return ans;
    }
};

/*
    Thoughts:

    -I might have overkilled this problem a little bit. But the actual logic behind it is pretty simple.
    If in an interview this was presented to me, I'm not certain I would be able to solve it in the given
    time as it is implementation-heavy and interviews are stressful.

    Solution:

    -I used a simple polynomial hash to solve this problem. Which will reduce the time to check if two strings
    are equal from O(length) to O(1). This was the part where the solution on leetcode became twice the size.

    -To do a polynomial hash you are required to be able to do addition, subtraction, multiplication, divison
    with a modulo, division is the factor that also requires exponention, to calculate modulo inverse.

    -Now that we got hashing out of the way, lets get into the actual solution.

    -I first complete the optional check, which uses prefix sums in order to efficiently check if in a substring of s
    all the words can exist. This is done by finding out the letter counts in all of the words and checking if it
    is equal to those in the substring.

    -The reason the above step is optional is because, in the worst case time complexity does not change.

    -If the words can exist in a given substring, because they are at equal length you can exhaustively check
    for every block in the substring (blocks are of length of a word which is constant) if there is a word that
    equals it, if it does remove that word from the checked words and continue, otherwise the substring isn't what
    we search for.*

    -In the worst case, for every substring in s we check for every word in "words". Which results in a time complexity of
    O(N * M), N being the length of s, and M being the length of "words".

    -Also note that, for step * we must have an efficient way of removing, and checking the vector words.
    I used unordered map as the check complexity is O(1), whilst removing is O(logM). So the complexity is
    actually about O(N * M * logM) which totals about 10^4 * 5000 * ~12 => 6 * 10^8 operations in the absolute
    worst case. Which passes just slightly.



*/