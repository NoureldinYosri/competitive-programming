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

const int MAX = 100*1000 + 10;
int L[MAX],R[MAX],depth[MAX],n;
int dp[MAX][2][2],mn,mx;

int solve(int u,int l,int r,int d){
    if(u == -1) {
        if(l != r) return 1 << 28;
        return (d == (mx - l)) ? 0 : (1 << 28);
    }
    if(dp[u][l][r] != -1) return dp[u][l][r];
    int & ret = dp[u][l][r]; ret =1 << 29;
	ret = min(ret,solve(L[u],l,l,d + 1) + solve(R[u],l,r,d + 1));
	ret = min(ret,solve(L[u],l,l,d + 1) + solve(R[u],r,r,d + 1));
	ret = min(ret,solve(L[u],l,r,d + 1) + solve(R[u],r,r,d + 1));

	ret = min(ret,solve(R[u],l,l,d + 1) + solve(L[u],l,r,d + 1) + 1);
	ret = min(ret,solve(R[u],l,l,d + 1) + solve(L[u],r,r,d + 1) + 1);
	ret = min(ret,solve(R[u],l,r,d + 1) + solve(L[u],r,r,d + 1) + 1);

//	cerr << u << " " << l << " " << r << " " << ret << endl;    
	return ret;
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		mn = INT_MAX;
		mx = 0;
		range(i,1,n){
			loop(x,2) loop(y,2) dp[i][x][y] = -1;		
			scanf("%d %d",L + i,R + i);
            if (L[i] == -1) {
                mx = max(mx, depth[i] + 1);
                mn = min(mn, depth[i] + 1);
            } 
			else depth[L[i]] = depth[i] + 1;
            if (R[i] == -1) {
                mx = max(mx, depth[i] + 1);
                mn = min(mn, depth[i] + 1);
            } 
			else depth[R[i]] = depth[i] + 1;
		}
        int ans = -1;
        if (mx == mn) ans = 0;
        else if (mx - mn == 1) ans = solve(1, 0, 1, 0);
		if(ans >= (1 << 28)) ans = -1;
		printf("%d\n",ans);
	}
	
	
	return 0;
}
