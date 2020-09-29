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


ll A[1 << 20];
bool inQ[1 << 20];
int n;

void smooth(){
	deque<int> dq;
	for(int i = n-1; i; i--) {
		ll s = A[i-1] + A[i];
		ll a = s >> 1;
		if(a != A[i-1]) {
			dq.pb(i);
			inQ[i] = true;
		}
	}
	int ctr = 0;
	deque<ll> hist;
	while(!dq.empty()){
		ctr++;
		if(ctr%1000000 == 0) {
			cerr << ctr/1000000 << " million" << endl;
			print(hist, ll);
		}
		int i = dq.front(); 
		dq.pop_front(); inQ[i] = false;
		
		ll s = A[i-1] + A[i];
		ll a = s >> 1,  b = s - a;
		if(A[i-1] != a){
			hist.pb(max(abs(a-A[i-1]), abs(b - A[i])));
			A[i-1] = a;
			A[i] = b;
			if(i-1 > 0 && !inQ[i-1]) dq.push_front(i - 1), inQ[i - 1] = true;
			if(i+1 < n && !inQ[i+1]) dq.push_back (i + 1), inQ[i + 1] = true;
		}
		if(sz(hist) > 10) hist.pop_front();
	}	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%lld", A + i);
	ll sum = 0;
	loop(i, n) sum += A[i];
	ll S = (n*(n - 1LL)) >> 1;
	assert(sum >= S);
	ll ds = sum - S;
	loop(i, n) A[i] = i + ds/n;
	ds %= n;
	
	loop(i, ds) A[i]++;

	smooth();

	loop(i, n) printf("%lld%c", A[i], " \n"[i==n-1]);
	return 0;
}
