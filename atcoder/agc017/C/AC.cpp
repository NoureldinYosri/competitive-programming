/*#include <bits/stdc++.h>

using namespace std;

const int N = 1234567;

int a[N], cnt[N], b[N];

int main() {
  int n, tt;
  scanf("%d %d", &n, &tt);
  int empty = n;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    cnt[a[i]]++;
    int pos = a[i] - cnt[a[i]] + 1;
    if (pos >= 1) {
      if (b[pos] == 0) {
        empty--;
      }
      b[pos]++;
    }
  }
  while (tt--) {
    int x, y;
    scanf("%d %d", &x, &y);
    {
      int pos = a[x] - cnt[a[x]] + 1;
      if (pos >= 1) {
        b[pos]--;
        if (b[pos] == 0) {
          empty++;
        }
      }
    }
    cnt[a[x]]--;
    a[x] = y;
    cnt[a[x]]++;
    {
      int pos = a[x] - cnt[a[x]] + 1;
      if (pos >= 1) {
        if (b[pos] == 0) {
          empty--;
        }
        b[pos]++;
      }
    }
    printf("%d\n", empty);
  }
  return 0;
}
*/
