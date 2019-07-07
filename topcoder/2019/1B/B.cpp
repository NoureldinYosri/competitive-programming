#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define ll long long

using namespace std;


class EllysTeleport{
	int teleport(int X,int A,int B,int M) {
		return (A*(ll)X + B)%M;
	}
	int dfs(int u,vi & F,vector<int> & vis,vi & f) {
		if(u == -1) return 0;
		if(vis[u] == 2) return 0;
		if(vis[u] == 1) return f[u];
		vis[u] = 2;
		f[u] = 1 + dfs(F[u],F,vis,f);
		vis[u] = 1;
		return f[u];
	}
public:

	int getMax(int N, int H1, int A, int B, int P, int Q, int M){
		vector<ll> H(N,H1);
		map<int,int> R;
		R[H1] = 0;
		for(int i = 1;i < N;i++){
			H[i] = teleport(H[i-1],A,B,M);
			R[H[i]] = i;
		}
		vector<int> goTo(N),InDeg(N,0);
		for(int i = 0;i < N;i++) {
			int x = teleport(H[i],P,Q,M);
			auto ptr = R.upper_bound(x);
			if(ptr == R.begin()) goTo[i] = -1;
			else {
				--ptr;
				goTo[i] = ptr->second;
				InDeg[goTo[i]]++;
			}
		}
		queue<int> q;
		for(int i = 0;i < N;i++)
			if(InDeg[i] == 0)
				q.push(i);
		int ans = 0;
		vector<int> f(N,0),vis(N,0);
		for(;!q.empty();q.pop()) {
			int u = q.front();
			vis[u] = 1;
			f[u] ++;
			ans = max(ans,f[u]);
			int v = goTo[u];
			if(v == -1) continue;
			f[v] = max(f[v],f[u]);
			InDeg[v]--;
			if(InDeg[v] == 0) q.push(v);
		}
		for(int i = 0;i < N;i++) {
			if(vis[i]) continue;
			int mx = 0,len = 0;
			int u = i;
			stack<int> Q;
			while(!vis[u] && u != -1) {
				Q.push(f[u]);
				mx = max(mx,f[u]);
				len++;
				vis[u] = 1;
				u = goTo[u];
			}
			if(u != -1)
				ans = max(ans,mx + len);
			else {
				len = 0;
				mx = 0;
				while(!Q.empty()) {
					mx = Q.top();
					len++;
					Q.pop();
					ans = max(ans,len + mx);
				}
			}
		}
		return ans;
	}
};
