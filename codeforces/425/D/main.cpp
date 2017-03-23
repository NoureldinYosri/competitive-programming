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

const int MAX = 1e5 + 1e2;
pi P[MAX];
int mxY[MAX],n;
vi Y[MAX];
int vis[MAX];

bool find(int x,int y){
	if(x >= MAX) return 0;
	return binary_search(all(Y[x]),y);
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",&P[i].xx,&P[i].yy);
	loop(i,n) Y[P[i].xx].pb(P[i].yy);
	loop(x,MAX) sort(all(Y[x]));
	ll ans = 0;
	for(int x = 0;x < MAX;x++){
		if(sz(Y[x]) *1LL*sz(Y[x]) <= n){
			loop(i,sz(Y[x])) loop(j,i){
				int len = Y[x][i] - Y[x][j];
				ans += find(x + len,Y[x][i]) && find(x + len,Y[x][j]);
			}
		}
		else{
			for(int len = 1;x + len < MAX;len++){
				for(int y : Y[x + len]){
					ans += find(x,y + len) && find(x,y) && find(x + len,y + len);	
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
