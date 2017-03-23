#pragma GCC optimize("O3")
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

const int mod = 1000*1000*1000 + 7;
int dp[31][901];
int C[31][31];

int solve(int n,int ik){
    if(ik < n) return 0;
    if(n == 0) return (ik == 0) ? 1 : 0;
    if(dp[n][ik] != -1) return dp[n][ik];
    int ret = 0;
    int rk = ik - n;
    for (int i = 0;i < n;i++){
        int l = i,r = n - 1 - i;
        for (int k = 0;k <= rk;k++){
           	int tmp = (solve(l,k)*1LL*solve(r,rk - k))%mod;
            tmp = (tmp *1LL* C[n - 1][l])%mod;
            ret += tmp;
            if(ret >= mod) ret -= mod;
        }
    }
    dp[n][ik] = ret;
    return ret;
}

int main(){
   for (int n = 0;n <= 30;n++){
        C[n][0] = C[n][n] = 1;
        for(int k = 1;k < n;k++){
            C[n][k] = C[n - 1][k] + C[n - 1][k - 1];
            if(C[n][k] >= mod) C[n][k] -= mod;
        }
    }

	int N,K; scanf("%d %d",&N,&K);
	
	dp[0][0] = 1;
	for(int n = 1;n <= N;n++){
		for(int ik = n,L = n*(n + 1)/2;ik <= L;ik++){
			int & ret = dp[n][ik];
			int rk = ik - n;
			for (int i = 0;i < n;i++){
				int l = i,r = n - 1 - i;
				for (int k = 0;k <= rk;k++){
				   	int tmp = (dp[l][k]*1LL*dp[r][rk - k])%mod;
				    tmp = (tmp *1LL* C[n - 1][l])%mod;
				    ret += tmp;
				    if(ret >= mod) ret -= mod;
				}
			}
		}
	}


	printf("%d\n",dp[N][K]);
	return 0;
}
