#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;


int n;
pi AB[1 << 20];
ll f[1 << 20];
int got[1 << 20];
int color[1 << 20];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) {
		scanf("%d", &AB[i].first);
		AB[i].second = i;
	}
	sort(AB, AB + n);
	ll ans = 0, best = 0;
	f[0] = f[1] = 1LL << 60;
	int nxt = -1;
	for(int i = 2; i < n;i ++){
		ll tmp = (i >= 3 ? f[i-3] : 0) - AB[i-2].first;
		if(tmp < best){
			best = tmp;
			nxt = i-3;
		}
		ans = f[i] = AB[i].first + best;
		got[i] = nxt;
	}
	int cur = n-1, k = 0;
	while(cur > -1){
		k++;
		nxt = got[cur];
		while(cur > nxt){
			color[AB[cur].second] = k;
			cur--;
		}
	}
	cout << ans << " " << k << endl;
	loop(i, n) printf("%d%c", color[i], " \n"[i==n-1]);
	return 0;
}
