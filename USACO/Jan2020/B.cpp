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
template<class T>
std::ostream& operator << (std::ostream& st,const std::vector<T> V) {
	st << "{";
	bool first = 1;
	for(auto x : V){
		if(!first) st << ", ";
		first = 0;
		st << x; 
	}
	st << "}";
	return st;
}

using namespace std;


const int MAXK = 20, MAXN = 50*1000 + 10, MAXST = 1 << 17, mod = 1e9 + 7;
int A[MAXN], n, m;
pair<vector<vi>, vector<vi>> ST[MAXST];
int K;

int add(int a,int b){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b){
	return (a*(ll)b)%mod;
}

void work(const vector<vi> & A, vector<vi> & B){
	B = vector<vi>(K, vi(K, 0));
	for(int k = K-1;k >= 0;k--)
		for(int r = k;r < K;r++){
			B[k][r] = A[k][r];
			if(k+1 <= r) B[k][r] = add(B[k][r], B[k+1][r]);
		}
}

void merge(const vector<vi> & L, const pair<vector<vi>, vector<vi>> & R, vector<vi> & F){
	F = vector<vi>(K, vi(K, 0));
	for(int a = 0;a < K;a++)
		for(int c = a;c < K;c++){
			F[a][c] = add(L[a][c], R.first[a][c]);
			for(int b = a; b <= c;b++)
				F[a][c] = add(F[a][c], mul(L[a][b], R.second[b][c]));
			}
}

void build(int cur,int s,int e){
	if(s == e){
		ST[cur].first = vector<vi>(K, vi(K, 0));
		ST[cur].first[A[s]][A[s]] = 1;
		work(ST[cur].first, ST[cur].second);
//		cerr << ST[cur] << endl;
		return;
	}
	int m = (s+e) >> 1, left = 2*cur + 1, right = left + 1;
	build(left, s, m);
	build(right, m+1, e);
	merge(ST[left].first, ST[right], ST[cur].first);
	work(ST[cur].first, ST[cur].second);
//	cout << ST[left].first << " + " << ST[right].second << " = " << ST[cur].first << endl;
}

pair<vector<vi>, vector<vi>> query(int cur,int s, int e, int l, int r){
	if(l <= s && e <= r) return ST[cur];
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) return query(left, s, m, l, r);
	if(m < l) return query(right, m+1, e, l, r);
	auto L = query(left, s, m, l, m);
	auto R = query(right, m+1, e, m+1, r);
	pair<vector<vi>, vector<vi>> F;
	merge(L.first, R, F.first);
	work(F.first, F.second);
	return F;
}


int main(){
	freopen("nondec.in", "r", stdin);
	freopen("nondec.out", "w", stdout);
	scanf("%d %d", &n, &K);
	loop(i, n){
		scanf("%d",A + i);
		A[i]--;
	}
	build(0, 0, n-1);
	scanf("%d",&m);
	loop(i, m){
		int l, r; scanf("%d %d", &l, &r);
		l--,r--;
		auto f = query(0, 0, n-1, l, r);
//		cout << f << endl;
		int ans = 1;
		loop(b, K) ans = add(ans, f.second[0][b]);
		printf("%d\n",ans);
	}
	return 0;
}
