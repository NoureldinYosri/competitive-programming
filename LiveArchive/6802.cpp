#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

int dr[][2] = {{0,1},{1,0},{0,-1},{-1,0}};

char S[200];

map<pi,int> M;

int main(){
	int T,X,Y,dir;
	scanf("%d",&T);
	loop(t,T){
		M.clear();
		dir = 0;
		scanf("%d %d %s",&X,&Y,S);
		int L = strlen(S);
		M[mp(X,Y)] = 1;
		loop(i,L)
			if(S[i] == 'R') ++dir,dir = (dir == 4) ? 0 : dir;
			else if(S[i] == 'L') --dir,dir = (dir == -1) ? 3 : dir;
			else {
				X += dr[dir][0];
				Y += dr[dir][1];
				if(M.find(mp(X,Y)) == M.end()) M[mp(X,Y)] = 1;
				else M[mp(X,Y)]++;			
			}
		int ctr = 0;
		for(auto & p : M) ctr += p.second > 1;
		printf("Case #%d: %d %d %d\n",t + 1,X,Y,ctr);
	}
	return 0;
}
