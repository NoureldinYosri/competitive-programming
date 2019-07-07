#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
using namespace std;

class EllysPearls{
	vector<int> P;
public:
	int getCost(int target,int alive) {
		static vector<int> aux;
		aux.clear();
		aux.push_back(0);
		for(int x : P) {
			if(x == target) {
				if(aux.back() >= 0) aux.back()++;
				else aux.push_back(1);
			}
			else if ((alive >> x) & 1){
				if(aux.back() >= 0) aux.push_back(-1);
				else aux.back() --;
			}
		}
		static vi suff;
		suff = vi(sz(aux),0);
		for(int i = sz(aux)-1;i >= 0;i--) {
			suff[i] = max(aux[i],0);
			if(i+1 < sz(aux)) suff[i] += suff[i+1];
		}
		int loss = 0;
		int best = INT_MAX;
		for(int i = 0;i < sz(aux);i++){
			if(aux[i] >= 0) {
				int tmp = loss;
				if(i + 1 < sz(aux)) tmp += suff[i+1];
				best = min(best,tmp);
			}
			else loss -= aux[i];
		}
		return best;
	}
	bool check(int x,int alive) {
		return (alive >> x) & 1;
	}
	int m;
	vector<vi> dp;
	int solve(int msk,int j) {
		if(j == sz(P)) return 0;
		if(!msk) return 0;
//		cerr << dp[msk][j] << endl;
		if(dp[msk][j] != -1) return dp[msk][j];
		int & ret = dp[msk][j];
		ret = INT_MAX;
		if(!check(P[j],msk)) return ret = solve(msk,j+1);

		for(int target = 0;target < m;target++) {
			if(!check(target,msk)) continue;
			int tot = 0;
			for(int i = j;i < sz(P);i++)
				tot += P[i] == target;
			int ctrT = 0,ctrNT = 0;
			int nmsk = msk ^ 1 << target;
			for(int i = j;i < sz(P);i++) {
				ctrT += P[i] == target;
				ctrNT += check(P[i],nmsk);
				ret = min(ret,ctrNT + tot - ctrT + solve(nmsk,j+1));
			}
		}
//		cerr << msk << " " << j << " " << ret << endl;

		return ret;
	}
	int getMin(int N, int M, vector <int> pearls){
		for(int & x : pearls) x--;
		P = pearls;
		m = M;
		dp = vector<vi> (1 << M,vi(N,-1));
		return solve((1 << M)-1,0);
	}
};
