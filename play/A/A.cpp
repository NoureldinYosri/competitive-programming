#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

class Solution {
    vector<vector<int> > Trie;
    vector<int> nc;
    vector<char> who;
public:
    void insert(const char *s){
        if(Trie.empty()) Trie.push_back(vector<int>(256,-1)),nc.push_back(0),who.push_back(0);
        int p = 0;
        for(;*s;s++){
	    if(Trie[p][*s] == -1){
                who[p] = *s;
                nc[p]++;
                Trie[p][*s] = Trie.size();
		Trie.push_back(vector<int>(256,-1));
                nc.push_back(0);
                who.push_back(0);
            }
            p = Trie[p][*s];
        }
    }
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
	sort(strs.begin(),strs.end());
	string cur = strs[0];
	insert(strs[0].c_str());
        for(auto s : strs) {
		if(s == "") return "";	
		if(cur.length() > s.length()) {
			insert(s.c_str());
			cur = s;
		}
		else {
			int i = 0;
			while(i < cur.length() && cur[i] == s[i]) i++;
			if(i == cur.length()) continue;
			insert(s.c_str());
			cur = s;
		}
	}
        int p = 0; string ret = "";
        while(nc[p] == 1) {
            ret += who[p];
            p = Trie[p][who[p]];
        }
	return ret;
    }
};

int main(){
	auto V = vector<string>(1,"a");
	Solution().longestCommonPrefix(V);
	return 0;
}
