#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
using vi = std::vector<int>;
using pi = std::pair<int,int>;
using ll = long long;
using namespace std;

class PBG{
public:

	int findEV(int P, int B, int G){
		return 0;
	}
};

bool in(vi & C) {
	for(int c : C) if(c == -1) return 1;
	return 0;
}

double bt(vi C) {
	if(!in(C)) return 0;
	if(C.size() == 1) return 1;
	int n = C.size();
	double ans = 0.0;
	double tot = n*(n-1)/2;
	loop(j,n) loop(i,j) {
		vi aux;
		loop(k,n) if(k != i && k != j) aux.push_back(C[k]);
		if(abs(C[i]) > abs(C[j])) {
			aux.push_back(C[i]);
			if(C[j] == -1) ans += n/tot;
			else ans += bt(aux)/tot;
		}
		else if(abs(C[i]) < abs(C[j])) {
			aux.push_back(C[j]);
			if(C[i] == -1) ans += n/tot;
			else ans += bt(aux)/tot;
		}
		else {
			vi tmp {C[i],C[j]};
			int sum = C[i] + C[j];
			for(int x : tmp) {
				int y = sum - x;
				if(y == -1) ans += n/tot/2.0;
				else {
					aux.push_back(x);
					ans += bt(aux)/tot/2.0;
					aux.pop_back();
				}
			}
		}
	}
	return ans;
}

double solve(int g,int p,int b) {
	vi C;
	loop(i,g) C.push_back(2);
	loop(i,p-1) C.push_back(1);
	loop(i,b) C.push_back(0);
	C.push_back(-1);
	return bt(C);
}

int main(){
	for(int g = 0;g <= 3;g++)
		for(int p = 1;p <= 3;p++)
			for(int b = 0;b <= 3;b++)
				cout << g << " " << p << " " << b << ": " << solve(g,p,b) << endl;
	return 0;
}
