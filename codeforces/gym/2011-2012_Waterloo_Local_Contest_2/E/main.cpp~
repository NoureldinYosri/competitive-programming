#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

int A[40][40];
int m,n,T;

void solve(int m,int n){
	if(m == 1 && n == 1) {
		A[0][0] = 0;
		return;
	}
	int c = 1 - (n & 1);
	c |= (n & 1) && (m > n);
	c &= m & 1;
	if(c){	
		int u = m >> 1;
		solve(u,n);
		loop(i,n) A[u][i] = 0;
		loop(i,u) loop(j,n) A[u + i + 1][j] = A[i][j]; 
	}
	else if(n & 1){
		int u = n >> 1;
		solve(m,u);
		loop(i,m) A[i][u] = 0;
		loop(i,m) loop(j,u) A[i][j + u + 1] = A[i][j];
	}
	else{
		loop(i,m) loop(j,n) A[i][j] = 0;
	}
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&m,&n);	
		solve(m,n);
		loop(i,m) loop(j,n) printf("%d%s",A[i][j],(j == n - 1) ? "\n" : " ");
	}	
	return 0;
}
