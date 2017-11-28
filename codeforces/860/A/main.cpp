#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;

char word[3 << 10];
int dp[3 << 10],n;

bool isVowel(char c){
	string vowels = "aeiou";
	for (char x : vowels)
		if(x == c) return 1;
	return 0;
}

int nxt[3000];

int solve(int pos) {
	if(pos == n) return 0;
	if(dp[pos] != -1) return dp[pos];
	int & ret = dp[pos];
	ret = 1 << 29;
	nxt[pos] = pos + 1;
	int ctr = 0,len = 0;
	set<char> used;
	for(int i = pos,ctr = 0;i < n;i++){
		int tmp = 0;
		if(isVowel(word[i])) {
			tmp = solve(i + 1) + 1;
			ctr = 0;
			len = 0;
			used.clear();
		}
		else {
			len++;
			ctr += used.find(word[i]) == used.end();
			used.insert(word[i]);
			if(len >= 3 && ctr >= 2) break;
			tmp = solve(i+1) + 1;
		}
		if(tmp < ret){
			ret = tmp;
			nxt[pos] = i + 1;
		}
	}
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> word;
	n = strlen(word);
	memset(dp,-1,sizeof dp);
	cerr << solve(0) << endl;
	int pos = 0;
	while(pos != n) {
		int r = nxt[pos];
		for(;pos < r;pos++)
			putchar(word[pos]);
		putchar(' ');
	}
	return 0;
}
