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


int n;
char S[1 << 20], T[1 << 20];

bool is_impossible(){
	int ones = 0;
	loop(i, n) ones += (S[i] == '1') - (T[i] == '1');
	return ones != 0;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %s %s", &n, S, T);
	if(is_impossible()) {
		puts("-1");
		return 0;
	}
	int ctr[2] = {0};
	loop(i, n) if(S[i] != T[i]) {
		int d = S[i] - '0';
		if(ctr[d^1] == 0) ctr[d^1]++;
		ctr[d^1]--;
		ctr[d]++;
	}
	cout << ctr[0] + ctr[1] << endl;
	return 0;
}
