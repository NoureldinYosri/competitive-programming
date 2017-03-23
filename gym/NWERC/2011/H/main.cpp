#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;


string IN[13];
int f[1 << 13],g[1 << 13];
int val[128];

bool valid(int msk){
	vector<char> V;
	loop(i,13) if(msk & (1 << i)) V.pb(IN[i][0]);
	sort(all(V),[](const char & a,const char & b){
		return val[a] < val[b];
	});
	if(sz(V) <= 4) return unique(all(V)) - V.begin() == 1;
	if(sz(V) == 5){
		int c1 = V[0] == V[1] && V[0] == V[2];
		int c2 = V[3] == V[4];
		if(c1 && c2) return 1;
		c1 = V[0] == V[1];
		c2 = V[2] == V[3] && V[2] == V[4];
		if(c1 && c2) return 1; 
	}
	loop(i,sz(V)){
		if(!i) continue;
		if(val[V[i]] != val[V[i-1]] + 1) return 0;
	}
	return 1;
}

vi aux;
vi avail;
vi G[1 << 13];

int main(){
	int k = 0;
	range(i,'2','9') val[i] = k++;
	for(char c : "TJQKA") val[c] = k++;	
	int T; cin >> T;
	while(T--){
		loop(i,13) cin >> IN[i];
		memset(f,0,sizeof f);
		avail.clear();
		loop(msk,1 << 13){
			if(valid(msk)) avail.pb(msk);
			G[msk].clear();
		}
		
		loop(msk,1 << 13)
			for(int msk2 : avail)
				if((msk2 & msk) == msk2)
					G[msk].pb(msk2);
		loop(msk,1 << 13){
			f[msk] = popcnt(msk);
			g[msk] = msk ? LSOne(msk) : 0;
			for(int sub : G[msk])
				if(1 + f[msk ^ sub] < f[msk]){
					f[msk] = f[msk ^ sub] + 1;
					g[msk] = sub;
				}
		}
		int msk = (1 << 13) - 1;
		printf("%d\n",f[msk]);
		while(msk){
			int sub = g[msk];
			loop(i,13) if(sub & (1 << i)) printf("%s ",IN[i].c_str());
			puts("");
			msk ^= sub;
		}
	}
	
	
	return 0;
}
