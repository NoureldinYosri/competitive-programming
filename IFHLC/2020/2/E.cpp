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

int H, W;
int grid[50][50];
bool goodRow[50], goodCol[50];

void fix(vi & V){
	sort(all(V));
	V.resize(unique(all(V)) - V.begin());
}

bool greedy1(vi & ret){
	vi rows, cols;
	loop(i, H) if(goodRow[i]) rows.pb(i);
	loop(i, H) loop(j, W) if(grid[i][j] && !goodRow[i]) {
		if(goodCol[j]) {
			cols.pb(j);
		} else {
			return false;
		}
	}
	fix(rows);
	fix(cols);
	for(int x : rows) ret.pb(-(x+1));
	for(int x : cols) ret.pb(x+1);
//	cerr << "g1 ";
//	print(ret, int);
	return true;
}

bool greedy2(vi & ret){
	vi rows, cols;
	loop(j, W) if(goodCol[j]) cols.pb(j);
//	print(cols, int);
	loop(i, H) loop(j, W) if(grid[i][j] && !goodCol[j]) {
		if(goodRow[i]) {
			rows.pb(i);
		} else {
			return false;
		}
	}
	fix(rows);
	fix(cols);
	for(int x : rows) ret.pb(-(x+1));
	for(int x : cols) ret.pb(x+1);
//	cerr << "g2 ";
//	print(ret, int);
	return true;
}


int main(){
	freopen("bwsquare.in", "r", stdin);
	freopen("bwsquare.out", "w", stdout);

	scanf("%d %d", &H, &W);
	loop(i, H) goodRow[i] = true;
	loop(j, W) goodCol[j] = true;
	loop(i, H) loop(j, W) {
		scanf("%d", &grid[i][j]);
		goodRow[i] &= grid[i][j] == 1;
		goodCol[j] &= grid[i][j] == 1;
	}
//	prArr(goodRow, H, bool);
//	prArr(goodCol, W, bool);
	vi A, B, ans;
	bool c1 = greedy1(A);
	bool c2 = greedy2(B);
	if(c1 && c2) {
		if(sz(A) < sz(B)) ans = A;
		else ans = B;
	} else if(c1) ans = A;
	else if(c2) ans = B;
	else {
		puts("-1");
		return 0;
	}

	printf("%d\n", sz(ans));
	for(int x : ans) printf("%d ", x);
	puts("");
	return 0;
}
