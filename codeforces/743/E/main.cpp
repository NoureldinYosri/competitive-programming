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

const int MAX = 1001;
int A[MAX],n;
int dp[MAX][1 << 8],len;
int vis[MAX][1 << 8];
vi idx[9];

bool get_next(int pos,int len,int & x,vi & V){
	if(!len) {
		x = pos;
		return 1;
	}
	else{
		auto p = lower_bound(all(V),pos) - V.begin();
		if(p + len <= V.size()) {
			x = V[p + len - 1];
			return 1;
		}
		else return 0;
	}
}

int solve(int pos,int msk){
	if(!msk) return 0;
	if(vis[pos][msk]) return dp[pos][msk];
	vis[pos][msk] = 1;
	int & ret = dp[pos][msk],x; ret = !len ? 0 : -(len + 1100);
	loop(d,8) if(msk & (1 << d)){
		if(get_next(pos,len,x,idx[d])) ret = max(ret,solve(x + 1,msk ^ (1 << d)) + len);
		if(get_next(pos,len+1,x,idx[d])) ret = max(ret,solve(x + 1,msk ^ (1 << d)) + len + 1);
	}
	return ret;
}

int f(int x){
	len = x;
	memset(vis,0,sizeof vis);
	return solve(0,(1 << 8) - 1);
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i),idx[--A[i]].pb(i);
	int s = 0,e = n;
	while(s < e){
		int m = s + (e - s + 1)/2;
		if(f(m) > 0) s = m ;
		else e = m - 1;
	}
	s = 0;
	while(e - s > 1){
		int m1 = s + (e - s + 1)/3,m2 = m1 + (e - s + 1)/3;
		if(f(m1) < f(m2)) s = m1 + 1;
		else e = m2 - 1;
	}
	cout << max(f(s),f(e)) << endl;	
	return 0;
}
