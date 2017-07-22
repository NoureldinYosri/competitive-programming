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

const int MAX = 1 << 20;
int cnt[MAX];
ll tot[MAX];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int n,x;
	ll ans = LLONG_MAX;
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",&x);
		cnt[x]++;
	}
	if(cnt[0] == n) {
		puts("2");
		return 0;
	}
	loop(i,MAX-1) {
		tot[i + 1] = tot[i] + cnt[i + 1]*(i + 1LL);
		cnt[i + 1] += cnt[i];
	}
	for(int g = 2;g < MAX;g++){
		ll tmp = 0;
		for(int cur = g,m = g/2;cur < MAX;cur += g,m += g){
			int u = cnt[m] - cnt[cur - g],v = cnt[cur - 1] - cnt[m];
			ll tmp1 = tot[m] - tot[cur - g] - u*1LL*(cur - g);
			ll tmp2 = (cur + 0LL)* v - (tot[cur - 1] - tot[m]);
			tmp += tmp1 + tmp2;
			assert(tmp1 >= 0);
			assert(tmp2 >= 0);
		}
		ans = min(ans,tmp);
	}
	printf("%lld\n",ans);
	return 0;
}
