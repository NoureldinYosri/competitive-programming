#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

int main(){
  ull A[3],ans;
  for(int i = 0;i < 3;i++)
    cin >> A[i];
  sort(A,A + 3);
  if((A[0]+A[1])<=A[2]/2)    
    ans=A[0]+A[1];  
  else  
    ans=(A[0]+A[1]+A[2])/3;  
  cout << ans << "\n";
  return 0;
}

