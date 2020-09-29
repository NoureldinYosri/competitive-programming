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

int N, T, K;
int S[18], C[18];
int seq[100];
ll tot[1 << 18];
char lg[1 << 18];
int dp[100][1 << 18];
char best[100][1 << 18];

int solve(int i, int msk){
	if(i == K) return 0;
	int & ret = dp[i][msk];
	if(ret != -1) return ret;
	int q = seq[i];
	if(tot[msk | (1 << q)] <= T){
		best[i][msk] = -1;
		if(msk & (1 << q)){
			ret = solve(i + 1, msk);
		} else {
			ret = solve(i + 1, msk | (1 << q)) + C[q];
		}
	} else {
		ret = 1 << 29;
		loop(j, N) if((msk >> j) & 1) {
			int tmp = solve(i, msk ^ (1 << j));
			if(tmp < ret){
				ret = tmp;
				best[i][msk] = j;
			}
		}
	}
	return ret;
}


int main(){
	freopen("cache.in", "r", stdin);
#ifndef HOME
	freopen("cache.out", "w", stdout);
#endif
	scanf("%d %d %d", &N, &T, &K);
	loop(i, N) scanf("%d", S + i);
	loop(i, N) scanf("%d", C + i);
	loop(i, K) {
		scanf("%d", seq + i);
		seq[i]--;
	}
	for(int i = 0; i < N; i++) lg[1 << i] = i;
	for(int msk = 1; msk < (1 << N); msk++){
		int b = lg[LSOne(msk)];
		tot[msk] = tot[msk ^ LSOne(msk)] + S[b];
	}
	memset(dp, -1, sizeof dp);
	cout << solve(0, 0) << endl;
	char i = 0;
	int msk = 0;
	vi tmp;
	while(i < K){
		tmp.clear();
		while(best[(int)i][msk] != -1){
			tmp.pb(best[(int)i][msk]);
			msk ^= 1 << best[(int)i][msk];
		}
		printf("%d", sz(tmp));
		for(int x : tmp) printf(" %d", x+1);
		puts("");
		msk |= 1 << seq[(int)i];
		i++;
	}
	return 0;
}
