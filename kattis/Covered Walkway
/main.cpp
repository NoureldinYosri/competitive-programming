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
#define pl pair<ll,ll>
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

const ll oo = 1LL << 60;
const int MAX = 1 << 20;
int n,c;
deque<int> dq;
ll dp[MAX];
int X[MAX];

ll eval(int i,int y){
	ll x = X[i];
	return dp[i - 1] + (y - x) * (y - x) + c;
}

double get_pos(int u,int v){
	// (x - X[u + 1])^2 + c + dp[u] = (x - X[v + 1])^2 + c + dp[v];
	ll a = -2*(X[u] - X[v]);
	double b = X[v]*1.0*X[v] - X[u]*1.0*X[u] + dp[v-1] - dp[u-1];
	return b/a;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&c);
	range(i,1,n){
		scanf("%d",X + i);
		if(X[i] == X[i - 1]){
			dp[i] = dp[i - 1];
			continue;
		}
		int siz = sz(dq);
		while(siz > 1 && get_pos(dq[siz-2],dq[siz - 1]) >= get_pos(dq[siz-1],i)) {
			dq.pop_back();
			siz--;
		}
		dq.pb(i);
		while(sz(dq) > 1 && eval(dq[0],X[i]) >= eval(dq[1],X[i])) dq.pop_front();
		dp[i] = eval(dq[0],X[i]);
	}
	cout << dp[n] << endl;
	return 0;
}
