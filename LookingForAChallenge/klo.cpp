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

const int MAX = 1 << 20;
int n, K;
int A[1 << 20];
ll T[2][MAX];

void add(int p, ll v, ll *BIT){
	for(++p; p < MAX; p += LSOne(p))
		BIT[p] += v;
}

ll get(int p, ll *BIT){
	ll ret = 0;
	for(++p; p; p ^= LSOne(p))
		ret += BIT[p];
	return ret;
}

void update(int x, int sgn){
	add(x, sgn, T[0]);
	add(x, sgn*x, T[1]);
}


ll f(int p){
	ll leq = get(p, T[0]);
	ll sum_leq = get(p, T[1]);
	ll sum_greater = get(1000*1000, T[1]) - sum_leq;
	ll left = leq*p - sum_leq ;
	ll right = sum_greater - (K - leq)*p;
//	cerr << p << "| " << leq << " " << sum_leq << " -> " << left << " \t " 
//				<< K - leq << " " << sum_greater << " -> " << right << endl;
	return left + right;
}

void update_belief(int & p){
	while(f(p+1) < f(p)) p++;
	while(p && f(p-1) < f(p)) p--;
}

int get_median(){
	int s = 0, e = 1000*1000;
	while(s < e){
		int m = (s + e) >> 1;
		if(2*get(m, T[0]) >= K) e = m;
		else s = m+1;
	}
	return s;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &K);
	loop(i, n) scanf("%d", A + i);
	
	loop(i, K-1) update(A[i], 1);
	
	ll ans = LLONG_MAX;
	pi info;
	
	for(int i = K-1; i < n; i++){
		update(A[i], 1);
		int p = get_median();
		loop(c, 2){
			ll tmp = f(p + c);
			if(tmp < ans){
				ans = tmp;
				info = pi(i-K+1, p + c);
			}
		}
		update(A[i-K+1], -1);
	}
	printf("%lld\n", ans);
	loop(i, K) A[i + info.first] = info.second;
	loop(i, n) printf("%d\n", A[i]);
	return 0;
}
