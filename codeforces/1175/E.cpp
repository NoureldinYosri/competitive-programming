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

const int MAX = 500*1000 + 10;
const int MAXLG = 20;

int R[MAX], n, m;
int lst[MAX];
int P[MAX][MAXLG];


int solve(int l, int r){
	if(lst[l] < r) return -1;
	int k = 0;
	while(k < MAXLG && P[l][k] <= r) k++;
	int ans = 0; 
	
	while(l < r){
//		cerr << l << ": "; prArr(P[l], 3, int);
		while(k && P[l][k-1] >= r) k--;
		if(k) k--;
		ans += 1 << k;
		l = P[l][k];
		if(k < MAXLG) k++;
	}
	
	return ans;
}

void build(){
	for(int i = MAX-1; i >= 0; i--){
		if(R[i] > i) {
			lst[i] = lst[R[i]];
			P[i][0] = R[i];
			loop(k, MAXLG-1) P[i][k+1] = P[P[i][k]][k];
			loop(k, MAXLG) assert(P[i][k]); 
		}
		else {	
			lst[i] = R[i];
			loop(k, MAXLG) P[i][k] = lst[i];
		}
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &n, &m);
	loop(i, n){
		int l, r; scanf("%d %d", &l, &r);
		R[l] = max(R[l], r);
	}
	for(int l = 0, r = 0;l < MAX; l++)
		R[l] = r = max(R[l], r);
	
	build();
	//prArr(R, 12, int);
	
	while(m--){
		int l, r; scanf("%d %d", &l, &r);
		printf("%d\n", solve(l, r));
	}
	
	
	return 0;
}
