#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

char G[4][5];

bool play(int x,int y){
	if(G[x][y] != '.') return 0;
	loop(l,3) {
		int r = 2 - l;
		if(y - l < 0 || y + r >= 4) continue;
		bool cond = 1;
		loop(j,l) cond &= G[x][y - j - 1] == 'x';
		loop(j,r) cond &= G[x][y + j + 1] == 'x';
		if(cond) return 1;
	}
	loop(u,3) {
		int d = 2 - u;
		if(x - u < 0 || x + d >= 4) continue;
		bool cond = 1;
		loop(j,u) cond &= G[x - j - 1][y] == 'x';
		loop(j,d) cond &= G[x + j + 1][y] == 'x';
		if(cond) return 1;
	}
	loop(l,3) {
		int r = 2 - l;
		if(x - l < 0 || y - l < 0) continue;
		if(x + r >= 4 || y + r >= 4) continue;
		bool cond = 1;
		loop(j,l) cond &= G[x - j - 1][y - j - 1] == 'x';
		loop(j,r) cond &= G[x + j + 1][y + j + 1] == 'x';
		if(cond) return 1;
	}
	loop(l,3){
		int r = 2 - l;
		if(x + l >= 4 || y - l < 0) continue;
		if(x - r < 0 || y + r >= 4) continue;
		bool cond = 1;
		loop(j,l) cond &= G[x + j + 1][y - j - 1] == 'x';
		loop(j,r) cond &= G[x - j - 1][y + j + 1] == 'x';
		if(cond) return 1;
	}
	return 0;
}

int main(){
	loop(i,4) scanf("%s",G[i]);
	bool can = 0;
	loop(i,4) loop(j,4) {
		can |= play(i,j);
	}
	puts(can ? "YES" : "NO");
	return 0;
}
