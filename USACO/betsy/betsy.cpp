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


int n;
int dx[] = {0,0,-1,1},dy[] = {-1,1,0,0};

int solve(int x,int y,ll mask){
	cerr << x << " " << y << " " << mask << " " << n << endl;
	mask |= 1LL << (x*n + y);
	if(mask == (1LL << (n*n)) - 1) return x == n - 1 && y == 0;
	if(x == n - 1 && y == 0) return 0;
	int ans=  0;
	loop(i,4){
		int nx = x + dx[i],ny = y + dy[i];
		if(nx < 0 || ny == n || ny < 0 || ny == n) continue;
		int l = nx * n + ny;
		if(mask & (1LL << l)) continue;	
		ans += solve(nx,ny,mask);
	}
	return ans;
}


int main(){
	freopen("betsy.in","r",stdin);
	freopen("betsy.out","w",stdout);	
	scanf("%d",&n);
	printf("%d\n",solve(0,0,0));	
	return 0;
}
