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


int P[1 << 20], S[1 << 20], n, m, ans, ans2;
int A[1 << 20], B[1 << 20];
vi t1, t2;



int match(int p, int s){
	int ctr = 0;
	while(s > p){
//		cerr << s << " > " << p << endl;
		ctr++;
		s = (s + 1) >> 1;
	}
//	cerr << s << " ? " << p << endl;
	if(s == p) return ctr;
	return -1;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n) scanf("%d", P + i), t1.pb(i);
	loop(i, m) scanf("%d", S + i), t2.pb(i);

	sort(all(t1), [](const int & a, const int & b){
		return P[a] < P[b];
	});
	sort(all(t2), [](const int & a, const int & b){
		return S[a] < S[b];
	});
	
	int i = 0;
	for(int c : t1){
		int p = P[c];
		while(i < m && match(p, S[t2[i]]) == -1) i++;
		if(i != m){
			ans++;
			int s = t2[i];
			B[c] = s + 1;
			ans2 += A[s] = match(p, S[s]);
			i++;
		}
	}
	printf("%d %d\n", ans, ans2);
	loop(i, m) printf("%d%c", A[i], " \n"[i==m-1]);
	loop(i, n) printf("%d%c", B[i], " \n"[i==n-1]);
	return 0;
}
