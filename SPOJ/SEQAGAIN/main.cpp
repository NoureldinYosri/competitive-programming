#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define EPS 1e-15
#define MOD 1000000007
 
/*
*
*Zaiiiin
*
*/
 
using namespace std;
 
typedef pair<int,int> ii;
typedef vector<pair<int,int>> vii;
typedef vector<int> vi;
 
const long double pi = acos(-1);
const int n_ = 1e5 + 5;
 
ll n, k, a[2][2], b[2][2], x, y, p1, p2;
 
void cpy(ll dis[2][2], ll src[2][2]){
  for(int i=0; i<2; i++)
    for(int j=0; j<2; j++)
      dis[i][j] = src[i][j];
}
 
void mul(ll dis[2][2], ll src[2][2]){
  ll ans[2][2];
  memset(ans, 0, sizeof ans);
  for(int i=0; i<2; i++)
    for(int j=0; j<2; j++)
      for(int f=0; f<2; f++)
        ans[i][j] = (ans[i][j] + (dis[i][f] * src[f][j]) % MOD) % MOD;
  cpy(dis, ans);
}
 
void MatPow(ll arr[2][2], ll p){
  if(p == 1) return;
  ll s[2][2];
  cpy(s, arr);
  mul(arr, arr);
  MatPow(arr, p / 2);
  if(p & 1ll) mul(arr, s);
}
 
ll pow(ll x, ll p){
  if(p == 1) return x;
  if(!p) return 1;
  ll ret = (x * x) % MOD;
  if(p & 1ll) ret = (ret * x) % MOD;
  return ret;
}
 
int main()
{
  int T;
  scanf("%d", &T);
  while(T--){
    scanf("%lld %lld %lld %lld", &x, &y, &n, &k);
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    a[0][1] = 1;
    b[0][0] = b[1][0] = k;
    b[1][1] = 1;
    if(n == 0){
      printf("%lld\n", x);
      continue;
    }
    if(n == 1){
      printf("%lld\n", y);
      continue;
    }
    --n;
    MatPow(b, n);
    mul(a, b);
    p1 = a[0][0];
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    a[0][0] = 1;
    b[0][0] = b[1][0] = k;
    b[1][1] = 1;
    MatPow(b, n);
    mul(a, b);
    p2 = a[0][0];
    x = pow(x, p1);
    y = pow(y, p2);
    printf("%lld\n", (x * y) % MOD);
  }
  return 0;
}
