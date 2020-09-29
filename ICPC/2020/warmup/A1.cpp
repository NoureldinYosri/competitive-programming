#include <bits/stdc++.h>
using namespace std;

int main(){
	freopen("sort.in", "r", stdin);
	freopen("sort.ans", "w", stdout);
	
	int n; scanf("%d", &n);
	vector<long long> A(n);
	for(auto & x : A) scanf("%lld", &x);
	sort(A.begin(), A.end());
	for(auto x : A) printf("%lld ", x);
	puts("");
}