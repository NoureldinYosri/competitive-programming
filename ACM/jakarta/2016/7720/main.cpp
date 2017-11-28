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


int mod = 1e9 + 7;


int mul(int a,int b){
	return (a*1LL*b)%mod;
}

int pow_mod(int x,int p){
	if(!p) return 1;
	int y = 1;
	for(;p > 1;p >>= 1) {
		if(p & 1) y = mul(x,y);
		x = mul(x,x);
	}
	return mul(x,y);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	range(t,1,T) {
		int ans = 1;
		int n;
		scanf("%d",&n);
		loop(i,n){
			int a,b,c; scanf("%d %d %d",&a,&b,&c);
			int x = 1;
			if(a > 1){
				x = pow_mod(a,b);
				int y = pow_mod(a,c - b + 1);
				y--; y += (y < 0) ? mod : 0;
				int d = a - 1;
				x = mul(x,mul(y,pow_mod(d,mod - 2)));
			}
			else x = c - b + 1;
			ans = mul(ans,x);
//			cout << a << " " << b << " " << c << " -> " << x << " and " << ans << endl;
		}
		printf("Case #%d: %d\n",t,ans);
	}
	return 0;
}
