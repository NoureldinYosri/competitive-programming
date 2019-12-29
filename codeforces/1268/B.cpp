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

const int MAX = 300*1000 + 10;

const ll oo = 1LL << 60;
const int B = 4;
int A[MAX];
int n;
ll dp[MAX][1 << B];
bool vis[MAX][1 << B];

ll solve(int i,int imsk){
	if(i == n) return imsk ? -oo : 0;
	ll & ret = dp[i][imsk];
	if(vis[i][imsk]) return ret;
	ret = 0;
	vis[i][imsk] = 1;
	

	for(int msk = 0;msk < (1 << B);msk++){
		if(msk & imsk) continue;
		int q = -1;
		bool valid = 1;
		loop(j,B) {
			if(msk & (1 << j)) {
				q = j;
				if(A[i+1] < j+1) valid = 0;
			}
			if(imsk & (1 << j)) q = j;
		}
		
		if(!valid) continue;
		int h = A[i];
		if(q >= 0) h -= q + 1;
		if(h < 0) continue;
		
		ret = max(ret,h/2 + solve(i+1,msk) + popcnt(msk));	
	}
//	cout << i << " " << p1 << " " << p2 << ": " << ret << endl;
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);

	ll ctr[2] = {0};
	loop(i,n){
		int a = A[i]/2,b = A[i] - a;
		if(i&1) swap(a,b);
		ctr[0] += a;
		ctr[1] += b;
	}
	cout << min(ctr[0],ctr[1]) << endl;
	
	return 0;
}
