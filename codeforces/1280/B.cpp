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

const int MAX = 66;
char G[MAX][MAX];
int R,C;
int col[MAX], row[MAX];
ll row_msk[MAX], col_msk[MAX];

bool are_complementry(ll msk, ll ground, int m){
	static vi aux;
	aux.clear();
	loop(i,m) if(!(ground & (1LL << i))) aux.push_back(i);
	assert(!aux.empty());
	int s = aux[0], e = aux.back();
	ll sub = (1LL << e) - 1;
	if(s) sub ^= (1LL << (s - 1)) - 1;	
	return (sub & msk) == sub;
}

bool try1(){
	return row[0] == C || row[R-1] == C || col[0] == R || col[C-1] == R;
}

bool try2(){
	ll tot_col = (1LL << C) - 1;
	ll tot_row = (1LL << R) - 1;
	loop(r,R) {
		ll cand[] = {row_msk[0], row_msk[R-1]};
		loop(i,2) {
			if((row_msk[r] | cand[i]) != tot_col) continue;
			if(are_complementry(row_msk[r], cand[i], C)) return 1;
		}
	}
	loop(c, C) {
		ll cand[] = {col_msk[0], col_msk[C-1]};
		loop(i,2) {
			if((col_msk[c] | cand[i]) != tot_row) continue;
			if(are_complementry(col_msk[c], cand[i], R)) return 1;
		}
	}
	return G[0][0] == 'A' || G[0][C-1] == 'A' || G[R-1][0] == 'A' || G[R-1][C-1] == 'A';
}

bool try3(){
	if(row[0] || row[R-1] || col[0] || col[C-1]) return 1;
	ll tot_col = (1LL << C) - 1;
	ll tot_row = (1LL << R) - 1;
	loop(r1, R) loop(r2, r1){
		if((row_msk[r1] | row_msk[r2]) != tot_col) continue;
		if(are_complementry(row_msk[r1], row_msk[r2], C)) return 1;
	}
	loop(c1, C) loop(c2, c1){
		if((col_msk[c1] | col_msk[c2]) != tot_row) continue;
		if(are_complementry(col_msk[c1], col_msk[c2], R)) return 1;
	}
	return 0;
}

int solve(){
	int cnt_a = 0;
	fill(col,col + C,0);
	fill(row,row + R,0);
	fill(row_msk, row_msk + R,0);
	fill(col_msk, col_msk + C,0);
	loop(r,R) loop(c,C) if(G[r][c] == 'A'){
		cnt_a ++;
		row[r] ++;
		col[c] ++;
		row_msk[r] |= 1LL << c;
		col_msk[c] |= 1LL << r;
	}
	if(cnt_a == 0) return -1;
	if(cnt_a == R*C) return 0;
	
	if(try1()) return 1;
	if(try2()) return 2;
	if(try3()) return 3;
	return 4;	
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d %d",&R,&C);
		loop(r,R) scanf("%s",G[r]);
		int ans = solve();
		if(ans == -1) puts("MORTAL");
		else printf("%d\n",ans);
	}
	return 0;
}
