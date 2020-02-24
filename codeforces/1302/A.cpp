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

const int MAX = 1024;
pi col[MAX], row[MAX];
int m, n;
int A[MAX][MAX];


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d", &m, &n);
	//if(m > n) 
	swap(n, m);
	loop(i, m) loop(j, n) scanf("%d", &A[i][j]);
	loop(i, m) row[i] = pi(INT_MIN, INT_MIN);
	loop(i, n) col[i] = pi(INT_MAX, INT_MAX);
	
	loop(i, m) loop(j, n) {
		int x = A[i][j];
		if(x > row[i].second) {
			row[i].second = x;
			if(row[i].second > row[i].first) swap(row[i].first, row[i].second);
		}
		if(x < col[j].second){
			col[j].second = x;
			if(col[j].second < col[j].first) swap(col[j].first, col[j].second);
		}
	}
/*	loop(i, m) {
		prArr(A[i], n, int);
	}
	loop(i, m) {
		cerr << row[i] << endl;
	}
	*/
	loop(i, m) loop(j, n){
		int x = A[i][j];
		bool y = 1;
		y &= col[j].first == x && col[j].second != x;
		y &= row[i].first == x && row[i].second != x;
		if(y){
			printf("%d %d\n", i + 1, j + 1);
			return 0;
		}
	}
	
	puts("0 0");
	return 0;
}
