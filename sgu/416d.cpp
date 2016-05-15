#include <bits/stdc++.h>
using namespace std;
int n = 8;
vector<int> A(n + 1);

int main(){
	for(int i = 1;i <= n;i++) A[i] = i;
	vector<vector<int> >res; int best = 0;
	do{
		int t = 0;
		for(int i = 1;i <= n;i++){
			int o = i + 2;
			if(o > n) o -= n;
			t += (A[i] - A[o])*(A[i] - A[o]);
		}
		for(int i = 1;i <= n/2;i++){
			int o = 2*i - 1;
			t += (A[2*i - 1] - A[2*i])*(A[2*i - 1] - A[2*i]);
		}	
		if(t > best){
			best = t;
			res.clear();
			res.push_back(A);
		}
		else if(t == best)
			res.push_back(A);
	}while(next_permutation(A.begin() + 1,A.end()));
	for(auto Q : res){
		for(int i = 1;i <= n;i++) cout << Q[i] << " ";
		cout << endl << best << endl;
	}
}