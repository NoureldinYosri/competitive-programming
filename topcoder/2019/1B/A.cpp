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


class EllysSki{
public:

	int getMax(vector <int> height){
		int n = sz(height);
		vector<int> L(n,0),R(n,0);
		L[0] = R[n-1] = 1;
		for(int i = 1;i < n;i++){
			L[i] = 1;
			if(height[i-1] <= height[i])
				L[i] += L[i-1];
		}
		int ans = 0;
		for(int i = n-2;i >= 0;i--) {
			R[i] = 1;
			if(height[i+1] <= height[i]) R[i] += R[i+1];
			ans = max(ans,L[i]);
			ans = max(ans,R[i]);
		}
		return ans;
	}
};
