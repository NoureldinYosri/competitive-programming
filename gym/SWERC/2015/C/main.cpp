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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 1 << 20;
ll A[MAX];
int in1[MAX],in2[MAX],siz[MAX];
int n;
typedef pair<ll,ll> pl;

ll solve(){
	PQ<pl,vector<pl>,greater<pl> > pq;
	loop(i,n) pq.push(mp(A[i],i));
	int N = n;
	while(pq.size() > 1){
		pl A = pq.top(); pq.pop();
		pl B = pq.top(); pq.pop();
		pq.push(mp(A.xx + B.xx,N));
		in1[N] = A.yy;
		in2[N] = B.yy;
		N++;
	}
	siz[N - 1] = 0;
	queue<int> q; q.push(pq.top().yy);
	ll ret = 0;
	while(!q.empty()){
		int u = q.front(); q.pop();
		if(u < n) {
			ret += siz[u] *1LL* A[u];
			continue;
		}
		siz[in1[u]] = siz[u] + 1;
		siz[in2[u]] = siz[u] + 1;
		q.push(in1[u]);
		q.push(in2[u]);

	}
	return ret;
}

int main(){
	//freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
	//	freopen("output.out", "w", stdout);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		loop(i,n) scanf("%lld",A + i);
		printf("%lld\n",solve());
	}
	return 0;
}
