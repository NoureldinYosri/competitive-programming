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

const int MAXB = 6;
int n, K;
int A[1 << 20];
vi I;
vi tmp;
int big[1 << 20];
int pref[1 << 20], suff[1 << 20];

bool solve(){
	I.clear();
	loop(i, n) if(A[i] == K) I.pb(i);
	if(I.empty()) return 0;
	if(n == 1) return !I.empty();
	loop(i, sz(I)-1) if(I[i]+1 == I[i+1] || I[i]+2 == I[i+1]) return 1;
	for(int p : I){
		for(int L = 2; L <= MAXB; L++){
			for(int st = p-L+1; st <= p; st++){
				if(st < 0) continue;
				if(st + L > n) break;
				tmp.clear();
				loop(i, L) tmp.pb(A[st + i]);
				sort(all(tmp));
				if(tmp[(L+1)/2 - 1] == K) return 1;
			}
		}
	}
	
	loop(p, n){
		pref[p] = p ? pref[p-1] : 0;
		for(int L = 2; L <= MAXB && !pref[p]; L++){
			int st = p - L + 1;
			if(st >= 0 && st + L <= n){
				tmp.clear();
				loop(i, L) tmp.pb(A[st + i]);
				sort(all(tmp));
				pref[p] |= tmp[(L+1)/2 - 1] >= K;				
			}
		}
	}

	suff[n] = 0;
	loop(q, n){
		int p = n-1-q;
		suff[p] = suff[p+1];
		for(int L = 2; L <= MAXB && !suff[p]; L++){
			int st = p;
			if(st >= 0 && st + L <= n){
				tmp.clear();
				loop(i, L) tmp.pb(A[st + i]);
				sort(all(tmp));
				suff[p] |= tmp[(L+1)/2 - 1] >= K;				
			}
		}
	}
	

	for(int i : I) {
		if(i && pref[i-1]) return 1;
		if(i+1 < n && suff[i+1]) return 1;
	}
	return 0;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d", &T);
	while(T--){
		scanf("%d %d", &n, &K);
		loop(i, n) scanf("%d", A + i);
		puts(solve() ? "yes" : "no");
	}
	return 0;
}
