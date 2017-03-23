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
#define point pair<double,double>
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

char G[101][103];
int dx[] = {0,-1,0,1},dy[] = {-1,0,1,0};

char get_color(int i, int j){
	if(G[i][j]) return G[i][j];	
	for(char color = 'A'; color <= 'Z'; color++){
		bool take = 1;
		loop(k,4) take &= G[i + dx[k]][j + dy[k]] != color;
		if(take) return color;
	}
	assert(1 == 0);
}

int main(){
	int n,m; scanf("%d %d",&n,&m);

	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(G[i][j]) continue;
			char color = get_color(i, j);
			int len = 0;
			while(i + len <= n && j + len <= m && get_color(i, j + len) == color) len ++;
			loop(x,len) loop(y,len) G[i + x][j + y] = color;
		}
	}
	range(i,1,n) puts(G[i] + 1);
//	range(i,1,n) cerr << G[i] + 1 << endl;
	return 0;
}
