#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define EPS 1e-12
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

const double pi = acos(-1);
const int n_ = 1e5 + 5;

int n, m, q[n_], L[n_], R[n_], bit[35], ans[n_], st[n_ << 2];
vi mask[n_], unmask[n_];

void build(int id = 1, int l = 1, int r = n){
  if(l == r){
    st[id] = ans[l];
    return;
  }
  int mid = (l + r) >> 1;
  build(id << 1, l, mid);
  build(id << 1 | 1, mid + 1, r);
  st[id] = st[id << 1] & st[id << 1 | 1];
}

int query(int s, int e, int id = 1, int l = 1, int r = n){
  if(s <= l && r <= e) return st[id];
  if(s > r || e < l) return -1;
  int mid = (l + r) >> 1;
  return query(s, e, id << 1, l, mid) & query(s, e, id << 1 | 1, mid + 1, r);
}

int main()
{
/*
  #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
  #else
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
  #endif
*/
  scanf("%d %d", &n, &m);
  for(int i=0; i<m; i++){
    scanf("%d %d %d", &L[i], &R[i], &q[i]);
    mask[L[i]].push_back(q[i]);
    unmask[R[i] + 1].push_back(q[i]);
  }

  int x = 0;
  for(int i=1; i<=n; i++){
    for(int y: mask[i]){
      for(int j=0; j<30; j++){
        if((1 << j) & y){
          if(!bit[j]) x ^= (1 << j);
          ++bit[j];
        }
      }
    }
    for(int y: unmask[i]){
      for(int j=0; j<30; j++){
        if((1 << j) & y){
          --bit[j];
          if(!bit[j]) x ^= (1 << j);
        }
      }
    }
    ans[i] = x;
  }
  build();
  for(int i=0; i<m; i++){
	if(query(L[i], R[i]) != q[i]){
      puts("NO");
      return 0;
    }
  }
  puts("YES");
  for(int i=1; i<=n; i++)
    printf("%d%c", ans[i]," \n"[i==n]);

 return 0;
}
