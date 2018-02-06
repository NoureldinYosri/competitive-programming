#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
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

const int maxn = 2*5000 + 42; // Maximum amount of states

struct suffixAutomata{
	map<char, int> to[maxn]; // Transitions
	int link[maxn]; // Suffix links
	int len[maxn]; // Lengthes of largest strings in states
	int last = 0; // State corresponding to the whole string
	int sz = 1; // Current amount of states

	inline void add_letter(char c) // Adding character to the end
	{
		int p = last; // State of string s
		last = sz++; // Create state for string sc
		len[last] = len[p] + 1;
		for (; to[p][c] == 0; p = link[p]) // (1)
			to[p][c] = last; // Jumps which add new suffixes
		if (to[p][c] == last) { // This is the first occurrence of c if we are here
			link[last] = 0;
			return;
		}
		int q = to[p][c];
		if (len[q] == len[p] + 1) {
			link[last] = q;
			return;
		}
	// We split off cl from q here
		int cl = sz++;
		to[cl] = to[q]; // (2)
		link[cl] = link[q];
		len[cl] = len[p] + 1;
		link[last] = link[q] = cl;
		for (; to[p][c] == q; p = link[p]) // (3)
			to[p][c] = cl; // Redirect transitions where needed
	}

	int cnt[maxn];
	int dfs(int u) {
		cnt[u] = 1;
		for(auto p : to[u])
			cnt[u] += dfs(p.yy);
		return cnt[u];
	}

	void explore(int u) {
		for(auto p : to[u])
			cerr << u << " " << p.yy << " " << p.xx << endl;
		for(auto p : to[u])
			explore(p.yy);
	}
};






string S,T;
suffixAutomata A,B;
int dp[maxn][maxn];

int solve(int u1,int u2) {
	if(ret != -1) return ret;
	if(A.cnt[u1] == 1 && B.cnt[u2] == 1) return ret = 0;

	ret = 10000;
	for(auto p : A.to[u1]) {
		char c = p.xx;
		if(B.to[u2].find(c) == B.to[u2].end()) continue;
		ret = min(ret,1 + solve(A.to[u1][c],B.to[u2][c]));
	}
	cerr << u1 << " " << u2 << " -> " << ret << endl;
	return ret;
}

int main() {
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> S >> T;
	for(char c : S) A.add_letter(c);
	for(char c : T) B.add_letter(c);

	A.dfs(0);
	B.dfs(0);

//	A.explore(0);
//	cerr << endl;
//	B.explore(0);

	memset(dp,-1,sizeof dp);
	cout << solve(0,0) << endl;

	return 0;

}
