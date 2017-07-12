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

const int MAX = 200000 + 1000;
vector<pair<ll,int> > G[MAX];
int T[MAX],B[MAX],n,m;
pi events[MAX << 1];


int main(){
	//freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
	//	freopen("output.out", "w", stdout);
	#endif
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",T + i);
	range(i,1,m) scanf("%d",B + i);
	int L = 0;
	loop(i,n) events[L++] = mp(T[i],i);
	range(i,1,m) events[L++] = mp(B[i],-i);
	sort(events,events + L);
	ll ans = 0,mx = 0,oo = 1LL << 60;
	for(int i = 0;i < L;i++) if(events[i].yy < 0){
		ll left = i ? events[i - 1].xx : -oo;
		int j = i;
		while(j < L && events[j].yy < 0) j++;
		ll right = (j == L) ? oo : events[j].xx;

		ll mn = (right - events[i].xx)*2;

		for(int t = i;t < j;t++){
			ll x = events[t].xx - left;
			ll y = (t + 1 != j) ? (right - events[t + 1].xx) : 0;
			mn = min(mn,x*2 + y*2);
		}
		mn = min(mn,right - left);
		ans += mn;
		i = j;
	}
	cout << ans << endl;
	return 0;
}
