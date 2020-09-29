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

const int MAXN = 200*1000 + 10;

int P[MAXN], Q[MAXN], n;
int R[MAXN], K;
char ans[MAXN];



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &K);
	loop(i, n) scanf("%d", P + i), P[i]--;
	loop(i, n) scanf("%d", Q + i), Q[i]--;
	loop(i, n) R[P[i]] = i;
	
	vp V;
	int q = -1;
	loop(i, n){
		int a = Q[i];
		int j = R[a];
		if(j < q) V.emplace_back(j, q);
		q = max(q, j);
	}
	
	
	loop(i, n) V.emplace_back(i, i);
	
	
	sort(all(V));
		
	vp Q;
	int s = -1, e = -1;
	for(auto [l, r] : V) {
		if(l <= e) e = max(e, r);
		else {
			if(e != -1) Q.emplace_back(s, e);
			
			s = l;
			e = r;
		}
	}
	if(e != -1) Q.emplace_back(s, e);
	
	if(sz(Q) < K){
		puts("NO");
		return 0;
	}
	
	int k = 0;
	for(auto [s, e] : Q){
		for(int i = s; i <= e; i++)
			ans[P[i]] = 'a' + k;
		k = min(k+1, 25);
	}
	puts("YES");
	puts(ans);
	
	return 0;
}
