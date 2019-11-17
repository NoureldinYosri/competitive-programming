#ifdef ACTIVE
#include <bits/stdc++.h>
using namespace std;


using pi = pair<int,int>;
const int MAX = 1e5;
int n,K;
int A[MAX];
vector<int> G[MAX];
bool vis[MAX];
int H[MAX],siz[MAX];
int inDeg[MAX];

struct cmp{
	bool operator () (const int & a,const int & b) const {
		int na = -siz[a],nb = -siz[b];
		return tie(siz[a],na,a) < tie(siz[b],nb,b);
	}
};

set<int,cmp> S;

void dfs(int u,int d) {
	// cout << u << " " << d << endl;
	H[u] = d;
	siz[u] = 1;
	for(int v : G[u]) {
		dfs(v,d + 1);
		siz[u] += siz[v];
	}
}

int main(){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d",&n,&K);
	for(int i = 1;i <= n;i++){
		scanf("%d",A + i);
		// cout << i << " " << A[i] << endl;
		if(A[i]) {
			G[A[i]].push_back(i);
			inDeg[i]++;
		}
	}
	// cout << "here" << endl;
	for(int i = 1;i <= n;i++)
		if(!vis[i])
			dfs(i,0);
	for(int i = 1;i <= n;i++)
		if(inDeg[i] == 0)
			S.insert(i);
	// for(auto p : S) cout << p.first << " " << p.second << ", ";
	// 	cout << endl;
	vector<int> aux;
	int day = 0;
	while(!S.empty()){
		day++;
		aux.clear();
		int L = min(K,(int)S.size());
		for(int k = 0;k < L;k++) {
			int p = *S.begin();
			S.erase(p);
			aux.push_back(p);
		}
		for(int u : aux) {
			for(int v : G[u]) {
				inDeg[v]--;
				if(inDeg[v] == 0)
					S.insert(v);
			}
		}
	}
	cout << day << endl;
	return 0;
}
#endif
