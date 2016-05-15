#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int seat[100][2][2];
int n;

void fill(int m,int c,int offset){
	if(m == 0) return;
	int who = 0;
	loop(i,n){
		loop(j,2){
			seat[i][j][c] = offset + who;
			who++;
			if(who == m) return;	
		}	
	}
}

int main(){
	int m;
	cin >> n >> m;
	fill(min(2*n,m),0,1); m = max(0,m - 2*n);
	fill(m,1,2*n + 1);
	loop(i,n) loop(j,2) loop(k,2) if(seat[i][j][1 - k]) printf("%d ",seat[i][j][1 - k]);
	puts("");	
	return 0;
}
