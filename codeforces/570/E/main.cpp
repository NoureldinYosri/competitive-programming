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

const int mod = 1e9 + 7;
int dp[500][500][2];
char G[501][511];
int dx[] = {0,1},dy[] = {1,0};
int m,n;
/*
int solve(int x1,int x2,int len){
	if(dp[x1][x2][len] != -1) return dp[x1][x2][len];
	int y1 = len - x1,y2 = n - 1 - (len - (m - 1 - x2));
	if(x2 == x1 && y1 == y2) return 1;
	int & ret = dp[x1][x2][len],cond = 1; ret = 0;
	if(x2 < x1 || y2 < y1) return 0;
	loop(i,2){
		int new_x1 = x1 + dx[i],new_y1 = y1 + dy[i];
		if(new_x1 == x2 && new_y1 == y2) ret = 1,cond = 0;
	}
	if(cond){
		loop(i,2) loop(j,2){
			int new_x1 = x1 + dx[i],new_y1 = y1 + dy[i];
			int new_x2 = x2 - dx[j],new_y2 = y2 - dy[j];
			if(new_x1 == m || new_y1 == n || new_x2 == -1 || new_y2 == -1) continue;
			if(G[new_x1][new_y1] != G[new_x2][new_y2]) continue;
			ret += solve(new_x1,new_x2,len + 1);
			if(ret >= mod) ret -= mod;
		}
	}
	//cerr << x1 << " " << y1 << "\t" << x2 << " " << y2 << " \t -> " << ret << endl;
	return ret;
}
*/
int solve(){
	int one = 0,other = 1;	
	for(int len = (n + m - 1)/2;len >= 0;len--){
		loop(x1,m) loop(x2,m){
			int y1 = len - x1,y2 = n - 1 - (len - (m - 1 - x2));
			int & ret = dp[x1][x2][one]; ret = 0;
			if(x2 < x1 || y2 < y1 || y1 < 0 || y2 < 0 || y2 >= n) continue;
			if(x2 == x1 && y1 == y2) ret = 1;
			else {
				int cond = 1;
				loop(i,2){
					int new_x1 = x1 + dx[i],new_y1 = y1 + dy[i];
					if(new_x1 == x2 && new_y1 == y2) ret = 1,cond = 0;
				}
				if(cond){
					loop(i,2) loop(j,2){
						int new_x1 = x1 + dx[i],new_y1 = y1 + dy[i];
						int new_x2 = x2 - dx[j],new_y2 = y2 - dy[j];
						if(new_x1 == m || new_y1 == n || new_x2 == -1 || new_y2 == -1) continue;
						if(G[new_x1][new_y1] != G[new_x2][new_y2]) continue;
						ret += dp[new_x1][new_x2][other];
						if(ret >= mod) ret -= mod;
					}
				}					
			}
	//		cerr << x1 << " " << y1 << " " << x2 << " " << y2 << " -> " << ret << endl;
		}
		swap(one,other);
	}
	return dp[0][m - 1][other];
}

int main(){
	scanf("%d %d",&m,&n);
	loop(i,m) scanf("%s",G[i]);
	if(G[0][0] != G[m - 1][n - 1]){
		puts("0");
		return 0;
	}
	cout << solve() << endl;	
	return 0;
}
