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


const int MAX = 610;
int L[MAX],R[MAX];
int n;

int dp[MAX][MAX];
int C[MAX][MAX];


int solve(int i,int len) {
	if(len == 0) return 1;
	int & ret = dp[i][len];
	if(ret != -1) return ret;
	ret = 0;
	for(int k = 0;k < len;k++) {
		int dist = 2*k + 1;
		if(L[i] <= dist && dist <= R[i]){
			int tmp = solve(i+1,k) && solve(i+1+k,len-1-k);
			if(tmp) {
				C[i][len] = k;
				ret = tmp;
			}
		}
	}
	ret = ret ? 1 : 0;
	return ret;
}

char S[100*100];

void recon(int i,int len,int offset) {
	if(!len) return;
	int k = C[i][len];
	S[offset] = '(';
	S[offset + 2*k + 1] = ')';
	recon(i+1,k,offset+1);
	recon(i+1+k,len-1-k,offset + 2*k + 2);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	cin >> n;
	loop(i,n) cin >> L[i] >> R[i];
	memset(dp,-1,sizeof dp);
	if(solve(0,n)) {
		recon(0,n,0);
		puts(S);
	}
	else puts("IMPOSSIBLE");
	return 0;
}
