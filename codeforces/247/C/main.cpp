#include <stdio.h>

int main(){
  unsigned long long dp[2][102] = {0};  
  int n, k, d;  
  scanf("%d %d %d",&n,&k,&d);
  if(n < d) {
    printf("0\n");
    return 0;
  }  
  dp[0][0] = 1;  
  for(int i = 1;i <= n;i++) {  
    for(int j = 1;j < ((i < k ? i : k) + 1);j++){  
      if(j < d) {
	dp[0][i] = (dp[0][i] + dp[0][i-j])%1000000007;  
	dp[1][i] = (dp[1][i] + dp[1][i-j])%1000000007;  
      } 
      else 
	dp[1][i] = (dp[1][i] + dp[0][i-j] +dp[1][i-j])%1000000007;  
    }  
  }  
  printf("%I64d\n",dp[1][n]);
  return 0;
}

