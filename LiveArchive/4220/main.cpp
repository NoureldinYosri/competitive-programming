#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

using namespace std;
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>


int n, a[10001], NEXT[10001], perimeter, biggest;

void divisores(int x, vector<int> &d){
  for (int i=1; i*i<=x; ++i){
    if (x % i == 0){
      d.push_back(i);
      if (i*i < x) d.push_back(x / i);
    }
  }
  sort(d.begin(), d.end());
  
}

int f(const vector<int> &div){
  for (int k=div.size()-1; k>=0; --k){
    const int &divisor = div[k];
    if (divisor >= 3){
      //Ver si funciona con este divisor
      int sum = perimeter / divisor;

      if (biggest > sum) continue;
      //Cada segmentito debe sumar sum
      int i=0, j=0, acum=0;
      do{
	if (acum == sum){
	  NEXT[i] = j;
	  acum  -= a[i];
	  i = i+1;
	}else if (acum > sum){
	  NEXT[i] = -1;
	  acum -= a[i];
	  i = i+1;
	}else{
	  acum += a[j];
	  j = (j+1)%n;
	}
      }while (i < n);
      

 for (int pivot=0; pivot<n; ++pivot){
	int i = pivot;
	while (i != -1){
	  i = NEXT[i];
	  if (i == pivot) return n - divisor;
	}
      }
    }
  }
  
  return -1;
}

int main(){
  while (scanf("%d", &n) && n){
    
    biggest = -1;
    perimeter = 0;
    for (int i=0; i<n; ++i){
      scanf("%d", &a[i]);
      perimeter += a[i];
      if (a[i] > biggest) biggest = a[i];
    }

    if (n < 3){
      printf("-1\n");
      continue;
    }

    vector<int> div;
    divisores(perimeter, div);
    
    printf("%d\n", f(div));

  }
  return 0;
}

