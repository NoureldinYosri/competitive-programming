#include <bits/stdc++.h>
using namespace std;

int A[500],N;

int f(int p){
	int c = 0;
	for(int i = 0;i < N;i++) c += abs(A[i] - p);
	return c;
}

int main(){
	int T;
	cin >> T;
	while(T--){
		cin >> N;
		for(int i = 0;i < N;i++) cin >> A[i];
		int u = 0,v = 30000;
		while(v - u > 1){
			int m1 = u + (v - u)/3,m2 = m1 + (v - u)/3;
			if(f(m1) < f(m2)) v = m2 - 1;
			else u = m1 + 1;
		}
		cout << min(f(u),f(v)) << endl;
	}
}
