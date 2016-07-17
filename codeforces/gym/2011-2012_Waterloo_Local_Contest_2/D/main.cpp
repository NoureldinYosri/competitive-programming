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

int T,N,W,L;
int A[2000][2000],a,b;

bool f(int l){
	loop(i,N - l + 1) loop(j,N - l + 1){
		int x = i + l - 1,y = j + l - 1;
		int v = A[x][y];
		if(i) v -= A[i - 1][y];
		if(j) v -= A[x][j - 1];
		if(i && j) v += A[i - 1][j - 1];
		if(v <= L) return 1;
	}
	return 0;
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&N,&W,&L);
		loop(i,N) loop(j,N) A[i][j] = 0;
		loop(i,W){
			scanf("%d %d",&a,&b);
			A[a - 1][b - 1] = 1;
		}
		loop(i,N) loop(j,N) {
			if(i) A[i][j] += A[i - 1][j];
			if(j) A[i][j] += A[i][j - 1];
			if(i && j) A[i][j] -= A[i - 1][j - 1];
		}
		int s = 0,e = N;
		while(s < e){
			int m = s + (e - s + 1)/2;
			if(f(m)) s = m;
			else e = m - 1;		
		}
		printf("%d\n",s*s);
	}
	return 0;
}
