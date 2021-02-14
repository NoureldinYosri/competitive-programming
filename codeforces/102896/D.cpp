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


const int MAX = 3e5 + 10;
int n;
int ones[MAX], zeros[MAX];
vi adj[MAX];
bool result[MAX];

void read(int i){
	static char buffer[10];
	scanf("%s", buffer);
	ones[i] = zeros[i] = 0;
	loop(j, 8){
		ones[i] |= (buffer[j] == 'W') << j;
		zeros[i] |= (buffer[j] == 'R') << j;
	}
}

int dp[MAX][256];

int get_val(int i, int msk){
	int ret = 0;
	for(int j : adj[i]){
		int d = j - i - 1;
		if((msk >> d) & 1) continue;
		ret = 1;
		break;
	}
	return ret;
}

int solve(int i, int msk){
	msk &= 255;
	int v = get_val(i, msk);
	if(i == 0) return v;
	int & ret = dp[i][msk];
	if(ret != -1) return ret;
	ret = solve(i - 1, 	(msk << 1) | v);
	return ret;
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	memset(dp, -1, sizeof dp);
	scanf("%d", &n);
	loop(i, n) {
		read(i);
		for(int d = 1; d <= 8 && i - d >= 0; d++){
			int j = i - d;
			int common = popcnt(ones[i] & ones[j]) + popcnt(zeros[i] & zeros[j]);
			if(d <= common) {
				adj[j].push_back(i);
			}
		}
		result[i] = solve(i, 255);
	}

	loop(i, n) putchar(2-result[i] + '0');
	puts("");
	return 0;
}
