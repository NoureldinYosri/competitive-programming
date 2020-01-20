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
vi P[2][2];


void solve1(vector<pi> & V);

void solve(vector<pi> & V){
	loop(i,2) loop(j,2) P[i][j].clear();
	loop(i,n){
		int x = V[i].first, y = V[i].second;
		x = (x%2 + 2)%2;
		y = (y%2 + 2)%2;
		P[x][y].push_back(i+1);
	}
	loop(i,2) loop(j,2) if(sz(P[i][j]) == n) {
		solve1(V);
		return;
	}
	int a = sz(P[0][0]) + sz(P[1][1]); 
	if(a == 0){
		a = sz(P[0][1]);
		if(a == 0) solve1(V);
		else if(a == n) solve1(V);
		else {
			printf("%d\n",sz(P[0][1]));
			for(int x : P[0][1]) printf("%d ",x);
			puts("");
		}
	}
	else if(a == n){
		a = sz(P[0][0]);
		if(a == 0){
			solve1(V);
		}
		else if(a == n){
			solve1(V);
		}
		else {
			printf("%d\n",sz(P[0][0]));
			for(int x : P[0][0]) printf("%d ",x);
			puts("");
		}
	}
	else {
		printf("%d\n",sz(P[0][0]) + sz(P[1][1]));
		for(int x : P[0][0]) printf("%d ",x);
		for(int x : P[1][1]) printf("%d ",x);
		puts("");
	}
	
}

void solve1(vector<pi> & V){
	for(auto & p : V){
		p.first >>= 1;
		p.second >>= 1;
	}
	solve(V);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	vector<pi> V;
	int mnX = INT_MAX,mnY = INT_MAX;
	loop(i,n){
		int x,y; scanf("%d %d",&x,&y);
		V.emplace_back(x,y);
		mnX = min(mnX,x);
		mnY = min(mnY,y);
	}
	for(auto & p : V){
		p.first += mnX;
		p.second += mnY;
	}
	
	solve(V);	
	return 0;
}
