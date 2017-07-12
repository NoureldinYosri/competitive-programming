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

const int MAX = 20*1000 + 10,mod = 1e9 + 7;
const vi P{2 ,3 ,5 ,7 ,11 ,13 ,17 ,19 ,23 ,29 ,31 ,37 ,41 ,43 ,47 ,53 ,59 };
const int SZP = 17;
int f[MAX][SZP],prod[MAX];
double g[MAX],lg[SZP];
int A[MAX],n;
int power[SZP][6];
int ans[MAX];
vp fact[61];
bool in[MAX][61];

void init(){
	loop(i,SZP) lg[i] = log(P[i]);
	loop(i,SZP){
		power[i][0] = 1;
		loop(j,5) power[i][j + 1] = (power[i][j] * 1LL * P[i])%mod;
	}
	range(i,1,60){
		int x = i;
		loop(j,SZP){
			int p = P[j],e = 0;
			while(x%p == 0){
				x /= p;
				e++;
			}
			if(e) fact[i].pb(mp(j,e));
		}
	}
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
		freopen("out.out", "w", stdout);
	#endif
	init();
	int m; scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i),prod[i] = 1;
	for(int x = 1;x <= n;x++){
		double mn = LLONG_MAX;
		for(int i = 0;i <= n - x;i++){
			if(!in[i][A[i + x - 1]]){
				for(auto E : fact[A[i + x - 1]]){
					int j = E.xx,e = E.yy;
					int d = max(e - f[i][j],0);
					f[i][j] += d;
					g[i] += d*lg[j];
					prod[i] = (prod[i] *1LL*power[j][d])%mod;
				}
				in[i][A[i + x - 1]] = 1;
			}
			if(g[i] < mn){
				mn = g[i];
				ans[x] = prod[i];
			}
		}
	//	cerr << x << " " << mn << " " << ans[x] << " " << g[0] << endl;
	}
	while(m--){
		int x; scanf("%d",&x);
		printf("%d\n",ans[x]);
	}
	return 0;
}
