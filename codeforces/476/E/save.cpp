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

const int oo = 1 << 28;
int dp[2][2001][501];

char S1[2001],S2[501];
int n,m;
int dp2[501][128],pf[501];


int GetLen(char c,int l,char *P,int *pf){
	if(dp2[l][c] != -1) return dp2[l][c];
	int & ret = dp2[l][c];
	while(l && P[l] != c) l = pf[l - 1];
	if(P[l] == c) l++;
	return ret = l;
}
 
void BuildFailure(char *P,int *pf){
	pf[0] = 0;
	for(int i = 1,L = strlen(P);i < L;i++)
		pf[i] = GetLen(P[i],pf[i - 1],P,pf);
}



int main(){
	scanf("%s %s",S1,S2);
	n = strlen(S1),m = strlen(S2);
	memset(dp2,-1,sizeof dp2);
	BuildFailure(S2,pf);


	for(char c = 'a';c <= 'z';c++)
		for(int i = 0;i < m;i++)
			GetLen(c,i,S2,pf);

	int val,one = 0,other = 1;

	for(int del = 0;del <= n;del++){
		for(int mtch = 0;mtch < m;mtch++)
			dp[one][n][mtch] = 0;
	//	for(int i = n-1;n-i < del;i--)
	//		for(int mtch = 0;mtch < m;mtch++)
	//			dp[one][i][mtch] = 0;
	//	for(int mtch = 0;mtch < m;mtch++)
	//			dp[one][n-del][mtch] = dp[other][n - del + 1][mtch];
		for(int i = n-1;i >= 0;i--)
			for(int mtch = 0;mtch < m;mtch++){
				int nm = dp2[mtch][S1[i]];
				val = (nm == m) + dp[one][i+1][(nm == m) ? 0 : nm];
				if(del) val = max(val,dp[other][i+1][mtch]);
				if(n-i == del) val = dp[other][i+1][mtch];
				if(n-i < del) val = 0;				
				dp[one][i][mtch] = val;	
			}
		printf("%d%c",dp[one][0][0]," \n"[del == n]);
		swap(one,other);		
	}		

	return 0;
}
