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

ll n,K;

vi N;
vi pref;
const int MAXB = 70;
ll dp[MAXB][MAXB][2];
int vis[MAXB][MAXB][2],visNum;

vi conv(ll x){
	if(!x) return vi();
	vi ret;
	while(x){
		ret.push_back(x&1);
		x >>= 1;
	}
	reverse(all(ret));
	return ret;
}

ll solve(int i,int j,bool are_eq){
	if(i == sz(N) && j == sz(pref)) return 1;
	if(i == sz(N)) return 0;
	ll & ret = dp[i][j][are_eq];
	if(vis[i][j][are_eq] == visNum) return ret;
	ret = 0;
	vis[i][j][are_eq] = visNum;
	
	int cand[2] = {-1,-1};
	
	if(j < sz(pref))cand[0] = pref[j];
	else {
		cand[0] = 0;
		cand[1] = 1;
	}
	loop(k,2) if(cand[k] != -1){
		int d = cand[k];
		if(are_eq && d > N[i]) continue;
		ret += solve(i+1,j+(j < sz(pref)),are_eq && d == N[i]);
	}
	
	if(j == 0) ret += solve(i+1,0,are_eq && (N[i] == 0));
	
	return ret;
}

ll f(ll val){
	pref = conv(val);
	visNum++;
	return solve(0,0,1);
}

ll solveEven(){
	ll s = 1,e = n/2;
	if(e < s) return 0;
	if(f(2) + f(3) < K) return 0;
	while(s < e){
		ll m = s + (e-s+1)/2;
		if(f(2*m) + f(2*m+1) >= K) s = m;
		else e = m-1;
	}	
	return 2*s;
}

ll solveOdd(){
	ll s = 0,e = n/2;
	while(2*e+1 > n) e--;
//	cout << s << " " << e << endl;
	if(e < s) return 0;
	
	while(s < e){
		ll m = s + (e-s+1)/2;
		if(f(2*m+1) >= K) s = m;
		else e = m-1;
	}
	return 2*s + 1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n >> K;
	N = conv(n);
	cout << max(solveEven(),solveOdd()) << endl;
//	cout << f(2) << " " << f(3) << endl;
//	cout << solveEven() << endl;
	return 0;
}
