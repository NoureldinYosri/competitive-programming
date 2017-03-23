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


const int MAX = 5010;
int T[MAX],P[MAX],TE,n;
double dp[MAX][MAX];


int main(){
	scanf("%d %d",&n,&TE);
	loop(i,n) scanf("%d %d",P + i,T + i);
	
	for(int i = n-1;i >= 0;i--){
		double p = P[i]/100.0,q = 1,tmp = 1,sum = T[i] != 1;
		
		for(int t = 0;t < T[i]-1;t++) q *= 1 - p;
		for(int t = 0;t < T[i]-2;t++) tmp *= 1 - p;
		if(T[i] == 1) for(int t = TE-1;t >= 0;t--) dp[i][t] += q*(1 + dp[i+1][t + T[i]]);
		else{
			int ctr = 1;
			for(int t = TE-1;t >= 0;t--){
				dp[i][t] = p*sum;
				if(t + T[i] <= TE) dp[i][t] += q*(1 + dp[i+1][t + T[i]]);
				++ctr;				
				if(ctr == T[i]) {
					sum -= tmp*(1 + dp[i+1][t + T[i] - 1]);
					--ctr;
				}

				sum = 1 + dp[i+1][t] + (1 - p)*sum;  
			}
		}
	}	
	printf("%.10f\n",dp[0][0]);
	return 0;
}
