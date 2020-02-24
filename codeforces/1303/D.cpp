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




int A[1 << 20], n;
ll S;
set<ll> ST;

int solve(){
	ll sum = 0;
	loop(i, n) sum += A[i];
	if(sum < S) return -1;
	map<int, int> freq;
	loop(i, n){
		int x = A[i];
		int b = 0;
		while(x > 1){
			b++;
			x >>= 1;
		}
		freq[b]++;
	}
	
//	for(auto p : freq) cerr << p ;
//	cerr << endl;
	
	int ans = 0;
	for(int b = 0; S; b++){
		assert(freq.begin()->second);
		ll v = 1LL << b;
		if(freq.begin()->first == b){
			if(S & v){
				freq[b]--;
				S ^= v;
			}
			int x = freq[b];
			if(x > 1)
				freq[b+1] += x >> 1;
			freq.erase(freq.begin());
		}
		if(S & v){
			int bt = freq.begin()->first;
			freq[bt]--;
			if(!freq[bt]) freq.erase(freq.begin());
			bt--;
			ans++;
			S ^= v;
			while(bt > b) freq[bt--]++, ans++;
		}
//		cerr << "@" << b << ": ";
//		for(auto p : freq) cerr << p ;
//		cerr << endl;
	}
	return ans;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%lld %d", &S, &n);
		loop(i, n) scanf("%d", A+i);
		printf("%d\n", solve());
	}
	return 0;
}
