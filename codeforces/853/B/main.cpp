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

const ll oo = 1LL << 60;
pair<pi,pi> A[1 << 20];
int n,m,k;
int T[1 << 20],fr[1 << 20],to[1 << 20],weight[1 << 20];

bool can[1 << 20];
ll cost[1 << 20];
int best[1 << 20];


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&m,&k);
	loop(i,m) scanf("%d %d %d %d",&A[i].xx.xx,&A[i].yy.xx,&A[i].yy.yy,&A[i].xx.yy);
	sort(A,A + m);
	loop(i,m) {
		T[i] = A[i].xx.xx;
		weight[i] = A[i].xx.yy;
		fr[i] = A[i].yy.xx;
		to[i] = A[i].yy.yy;
	}
	/*prArr(T,m,int);
	prArr(fr,m,int);
	prArr(to,m,int);
	prArr(weight,m,int);
	*/
	ll tot = 0;
	for(int i = m-1,ctr = 0;i >= 0;i--){
		if(fr[i] == 0) {
			int u = to[i];
			if(best[u] == 0) {
				best[u] = weight[i];
				ctr++;
				tot += weight[i];
			}
			else {
				tot -= best[u];
				best[u] = min(best[u],weight[i]);
				tot += best[u];
			}
		}
//		cerr << i << " " << ctr << endl;
		can[i] = ctr == n;
		cost[i] = tot;
	}
//	prArr(can,m,int);
	tot = 0;
	ll ans = oo;
	memset(best,0,sizeof best);
	for(int i = 0,ctr = 0;i < m;i++){
		if(to[i] == 0) {
			int u = fr[i];
			if(best[u] == 0) {
				best[u] = weight[i];
				ctr++;
				tot += weight[i];
			}
			else {
				tot -= best[u];
				best[u] = min(best[u],weight[i]);
				tot += best[u];
			}
			if(T[m-1] <= T[i] + k) break;
			int idx = upper_bound(T + i+1,T + m,T[i] + k) - T;
			if(ctr == n && can[idx])
				ans = min(ans,tot + cost[idx]);
		}
	}
	if(ans >= oo) ans = -1;
	cout << ans << endl;
	return 0;
}
