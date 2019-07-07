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

const int MAXA = 1 << 20;
bool high[MAXA],low[MAXA];
int base[MAXA];

ll sum_of_squares(ll n) {
	return n*(n + 1)*(2*n+1)/6;
}

ll sum_of_i(ll n) {
	return n*(n+1)/2;
}

ll sum_of_odd_squares(ll n) {
	return 4*sum_of_squares(n)-4*sum_of_i(n) + n;
}

ll sum_of_even_squares(ll n){
	return 4*sum_of_squares(n);
}

vi pyramids;

void init(){
	for(int i = 2;sum_of_squares(i) < MAXA;i++) {
		high[sum_of_squares(i)] = 1;
		base[sum_of_squares(i)] = i;
	}
	for(int i = 2;sum_of_odd_squares(i) < MAXA;i++) {
		low[sum_of_odd_squares(i)] = 1;
		base[sum_of_odd_squares(i)] = 2*i-1;
	}
	for(int i = 2;sum_of_even_squares(i) < MAXA;i++){
		low[sum_of_even_squares(i)] = 1;
		base[sum_of_even_squares(i)] = 2*i;
	}
	for(int i = 1;i < MAXA;i++)
		if(low[i] || high[i])
			pyramids.pb(i);
}

int taken[MAXA];
vector<pi> ans;

bool bt(int n,int d) {
	if(n == 0) return 1;
	if(d == 0) return 0;
	int r = upper_bound(all(pyramids),n) - pyramids.begin();
	r--;
	if(r < 0) return 0;
	for(int i = 0;i < 120 && i <= r;i++){
		int m = pyramids[r-i];
		if(!taken[m]) {
			taken[m] = 1;
			bool res = bt(n - m,d - 1);
			taken[m] = 0;
			if(res) {
				ans.pb(mp(m,high[m]));
				return 1;
			}
		}
	}
	return 0;
}




int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	init();
	for(int t = 1,n;scanf("%d",&n) == 1 && n;t++) {
		printf("Case %d:",t);
		ans.clear();
		for(int d = 2;d <= 8;d++)
			if(bt(n,d))
				break;
		if(ans.empty()) puts(" impossible");
		else {
			sort(all(ans));
			reverse(all(ans));
			for(auto p : ans)
				printf(" %d%c",base[p.xx],"LH"[p.yy]);
			puts("");
		}
	}
	return 0;
}
