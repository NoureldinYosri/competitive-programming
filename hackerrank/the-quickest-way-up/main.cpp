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

vi ladder[101],snake[101];
int dist[101];

int bfs(){
	memset(dist,-1,sizeof dist);
	deque<int> q;
	q.pb(1); dist[1] = 0;
	while(!q.empty()){
		int u = q.front(); q.pop_front();
		assert(sz(ladder[u]) + sz(snake[u]) <= 1);
		if(sz(ladder[u]) || sz(snake[u])){
			int v = sz(ladder[u]) ? ladder[u].back() : snake[u].back();
			if(dist[v] == -1){
				dist[v] = dist[u];
				q.push_front(v);
			}
			continue;
		}
		range(i,1,6) {
			int v = u + i;
			if(v > 100) break;
			if(dist[v] == -1){
				dist[v] = dist[u] + 1;
				q.pb(v);
			}
		}
	}
	return dist[100];
}

int main(){
	int T; scanf("%d",&T);
	while(T--){
		range(i,1,100) ladder[i].clear(),snake[i].clear();
		int n; scanf("%d",&n);
		while(n--){
			int a,b; scanf("%d %d",&a,&b);
			ladder[a].pb(b);
		}
		scanf("%d",&n);
		while(n--){
			int a,b; scanf("%d %d",&a,&b);
			snake[a].pb(b);
		}
		printf("%d\n",bfs());
	//	cout << dist[100] << endl;
	}	
	
	
	return 0;
}
