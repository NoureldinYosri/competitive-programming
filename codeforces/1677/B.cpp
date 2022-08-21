#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using vp = std::vector<pi>;
using ll = long long;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
void tc();
auto test_cases = [](){
	int T; scanf("%d", &T);
	while(T--) tc();
};
using namespace std;


int colCnt[1 << 20];
int R, C;
char S[1 << 20];
int ans[1 << 20], N;


void solveCols() {
	fill(colCnt, colCnt + C, 0);
	int fc = 0, c = 0;
	loop(i, N) {
		fc--;
		if(fc == -1) fc += C;
		if(S[i] == '1') {
			c += colCnt[fc] == 0;
			colCnt[fc]++;
		}
		ans[i] = c;
	}
}

int delta[1 << 20];

void solveRows() {
	int prv = -1;
	fill(delta, delta + N, 0);
	loop(i, N) {
		if(S[i] == '1') {
			if(prv == -1 || i - prv > C) {
				delta[i]++;
//				cerr << i << " is an activator" << endl;
			}
			prv = i;
		} else {
			if(prv != -1 && i - prv == C) {
//				cerr << i << " is a deactivator" << endl;
				delta[i]--;
			}
		}
	}
	int r = 0;
	loop(i, N) {
		r += delta[i];
		if(i + C < N) delta[i + C] += delta[i];
		ans[i] += r;
	}
}
void tc() {
	scanf("%d %d %s", &R, &C, S);
	N = R*C;
	solveCols();
	solveRows();
	loop(i, N) printf("%d ", ans[i]);
	puts("");
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	test_cases();
	return 0;
}
