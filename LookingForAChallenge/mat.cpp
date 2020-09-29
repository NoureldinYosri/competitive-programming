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


const int MAX = 1000*1000 + 10;
int S[MAX], H[MAX], n, m;
int R[MAX];

int fail[MAX];

int pref[MAX], suff[MAX];

void build(){
	map<int, int> M;
	loop(i, n){
		auto ptr = M.upper_bound(R[i]);
		if(ptr == M.end()) suff[i] = -1;
		else suff[i] = i - ptr->second;
				
		if(ptr == M.begin()) pref[i] = -1;
		else {
			ptr--;
			pref[i] = i - ptr->second;
		}
		M[R[i]] = i;
	}
//	prArr(pref, n, int);
//	prArr(suff, n, int);
}


bool check(int l, int i, int *A){
	int d1 = pref[l], d2 = suff[l];
	if(d1 != -1 && A[i-d1] > A[i]) return 0;
	if(d2 != -1 && A[i-d2] < A[i]) return 0;
	return 1;
}

int get_len(int l, int i, int *A){
	while(l && !check(l, i, A))
		l = fail[l-1];
	l += check(l, i, A);
	return l;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n) {
		scanf("%d", S + i);
		R[S[i]-1] = i;
	}
	loop(i, m) scanf("%d", H + i);
	
	
	build();
	
	for(int i = 1, len = 0; i < n; i++)
		fail[i] = len = get_len(len, i, R);
	
/*	
	prArr(R, n, int);
	prArr(fail, n, int);
	prArr(H, m, int);
*/	
	vi ans;
	for(int i = 0, len = 0; i < m; i++){
		len = get_len(len, i, H);
//		cerr << i << " " << len << endl;
		if(len == n){
			ans.pb(i+1);
			len = fail[n-1];
		}
	}
	printf("%d\n", sz(ans));
	for(int x : ans) printf("%d ", x-n+1);
	puts("");
	return 0;
}
