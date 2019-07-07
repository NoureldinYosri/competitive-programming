#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

int n,K;
string s;
pi dp[1 << 20];


int main(int argc,char **argv){
	freopen("redistricting.in","r",stdin);
#ifndef HOME
	freopen("redistricting.out","r",stdin);
#endif
	cin >> n >> K >> s;
	vi pref(n,0);
	int aux = 0;
	multiset<pi> S;
	for(int i = 1;i <= n;i++) {
		if(i >= K)
			S.erase(S.find(dp[i - K]));
		char c = s[i - 1];
		aux += 2*(c == 'H') - 1;
		auto ptr = S.lower_bound(mp(aux,INT_MIN));
		int v = INT_MAX;
		if(ptr != S.end()) v = min(v,1 + ptr->yy);
		if(ptr != S.begin()) {
			ptr--;
			v = min(v,ptr->yy);
		}
		dp[i] = mp(aux,v);

	}
	return 0;
}
