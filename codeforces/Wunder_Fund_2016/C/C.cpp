#include <bits/stdc++.h>
using namespace std;

pair<pair<long long,long long>,int> P[1 << 20]; int n;

int main(){
scanf("%d",&n);
for(int i = 0;i < n;i++) scanf("%I64d %I64d",&P[i].first.first,&P[i].first.second),P[i].second = i;
sort(P,P + n);
for(int i = 0;i < n - 2;i++){
pair<long long,long long > u,v;
u.first = P[i + 2].first.first - P[i].first.first,u.second =  P[i + 2].first.second - P[i].first.second;
v.first = P[i + 1].first.first - P[i].first.first,v.second =  P[i + 1].first.second - P[i].first.second;
if (u.first*v.second != u.second*v.first){
cout << P[i].second << " " << P[i + 1].second << " " << P[i + 2].second;
return 0;
}
}
return 0;
}
