#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;i++)
using namespace std;int A[1000][1000],dp[1000][1000],n,T;
int solve(int r,int c){if(r==n) return 0;if(dp[r][c]!=-1)return dp[r][c];return dp[r][c]=A[r][c]+max(solve(r+1,c),solve(r+1,c+1));}
int main(){scanf("%d",&T);while(T--){scanf("%d",&n);loop(i,n)loop(j,i+1)scanf("%d",&A[i][j]),dp[i][j] = -1;printf("%d\n",solve(0,0));}return 0;}
