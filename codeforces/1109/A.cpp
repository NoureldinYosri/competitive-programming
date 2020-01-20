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


vi IDX[1 << 20];
int n;
int A[1 << 20];
int B[1 << 20];

ll C(ll n){
	return (n*(n-1))/2;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	IDX[0].push_back(0);
	int b = 0;
	for(int i = 1;i <= n;i++){
		int x; scanf("%d", &x);
		A[i] = x;
		b ^= x;
		IDX[b].push_back(i);
		B[i] = b;
	}
	ll res = 0;
	for(int x = 0;x < (1 << 20);x++){
		const vi & V = IDX[x];
		int cnt[2] = {0};
		for(int v : V) cnt[v&1]++;
		res += C(cnt[0]) + C(cnt[1]);
	}
	cout << res << endl;
	
	return 0;
}
