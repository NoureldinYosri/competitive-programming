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
int lim[MAXN], n, m;
int A[MAXN];
vi test[MAXN];


bool can(int K){
	loop(i, K) test[i].clear();
	
	int j = 0;
	loop(i, n){
		if(j == K) j = 0;
		int v = A[i];
		test[j].pb(v);
		if(lim[v] < sz(test[j])) return 0;		
		j++;
	}
	return 1;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n) scanf("%d", A + i);
	loop(i, m) scanf("%d", lim + i + 1);
	
	sort(A, A + n);
	reverse(A, A + n);
	
	int s = 1, e = n;
	while(s < e){
		int mid = s + (e-s)/2;
		if(can(mid)) e = mid;
		else s = mid+1;
	}
	
	printf("%d\n", s);
	can(s);
	loop(i, s) {
		printf("%d", sz(test[i]));
		for(int x : test[i]) printf(" %d", x);
		puts("");
	}
	
	return 0;
}
