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

const int MAX = 100*1000 + 10, MAXLG = 20;
int n;
int A[MAX];
int L[MAX], R[MAX];
int pref[MAX], suff[MAX];
int lg[MAX];
pi ST[MAX][MAXLG];

void build(){
	vi ST;
	loop(i, n) {
		while(!ST.empty() && A[ST.back()] <= A[i]) ST.pop_back();
		L[i] = ST.empty() ? -1 : ST.back();
		ST.pb(i);
	}
	ST.clear();
	for(int i = n-1; i >= 0;i--){
		while(!ST.empty() && A[ST.back()] <= A[i]) ST.pop_back();
		R[i] = ST.empty() ? n : ST.back();
		ST.pb(i);		
	}
	int s = 0;
	loop(i, n) {
		s += A[i];
		pref[i] = s;
	}
	s = 0;
	loop(j, n){
		int i = n-1-j;
		s += A[i];
		suff[i] = s;
	}
	lg[0] = -1;
	for(int i = 1; i <= n; i++)
		lg[i] = lg[i-1] + (i == LSOne(i));
	for(int i = 0; i < n; i++)
		::ST[i][0] = pi(pref[i], suff[i]);
	loop(k, MAXLG-1){
		loop(i, n){
			int j = i + (1 << k);
			if(j >= n) j = i;
			::ST[i][k+1].first = max(::ST[i][k].first, ::ST[j][k].first);
			::ST[i][k+1].second = max(::ST[i][k].second, ::ST[j][k].second);
		}
	}
}


pi get_max(int s, int e){
	int l = lg[e-s+1];
	pi ret(INT_MIN, INT_MIN);
	ret.first = max(ST[s][l].first, ST[e-(1 << l)+1][l].first);
	ret.second = max(ST[s][l].second, ST[e-(1 << l)+1][l].second);
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	build();
	int ans = 0;
	loop(i, n){
		int r = get_max(i, R[i]-1).first - pref[i];
		int l = get_max(L[i]+1, i).second - suff[i];
		ans = max(ans, l + r);
	}
	cout << ans << endl;
	return 0;
}
