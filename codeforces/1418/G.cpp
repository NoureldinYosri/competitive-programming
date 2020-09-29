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

const int MAXLG = 20;
int n;
int A[1 << MAXLG];
int fourth[1 << MAXLG], nxt[1 << MAXLG];
vi pos[1 << MAXLG];
int maximal[1 << MAXLG];
int ST[2][1 << MAXLG][MAXLG], lg[1 << MAXLG];

void init(){
	for(int i = n-1; i >= 0; i--){
		vi & idx = pos[A[i]];
		if(idx.empty()){
			nxt[i] = n;
		} else {
			nxt[i] = idx.back();
		}
		idx.pb(i);
		if(sz(idx) == 4) {
			rotate(idx.begin(), idx.begin() + 1, idx.end());
			fourth[i] = idx.back();
			idx.pop_back();
		} else {
			fourth[i] = n;
		}
	}
	lg[0] = -1;
	for(int i = 1; i <= n; i++) lg[i] = lg[i-1] + (i == LSOne(i));
	loop(i, n) {
		ST[0][i][0] = fourth[i];
		ST[1][i][0] = nxt[i];
	}
	loop(c, 2){
		loop(k, MAXLG-1){
			loop(i, n){
				int j = i + (1 << k);
				if(j >= n) j = i;
				ST[c][i][k + 1] = max(ST[c][i][k], ST[c][j][k]);
			}
		}		
	}
}

int getMax(int s, int e, int c){
	int l = lg[e-s+1];
	return max(ST[c][s][l], ST[c][e-(1<<l)+1][l]);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d", &n);
	loop(i, n) scanf("%d", A + i);
	init();
	loop(i, n){
		int s = i, e = n-1;
		while(s < e) {
			int m = s + (e - s + 1)/2;
			if(getMax(i, m, 0) > m) s = m;
			else e = m - 1;
		}
		maximal[i] = s;
	}
	prArr(maximal, n, int);
	return 0;
}
