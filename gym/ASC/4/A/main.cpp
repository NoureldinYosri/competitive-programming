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

vector<pl> G[801];
ll dist[801];
int cnt[801];
int n;

int main(){
	freopen("attack.in","r",stdin);
	freopen("attack.out","w",stdout);
	int m,A,B; scanf("%d %d %d %d",&n,&m,&A,&B);
	loop(i,m){
		int a,b,c; scanf("%d %d %d",&a,&b,&c);
		G[a].pb(mp(c,b));
		G[b].pb(mp(c,a));
	}
	fill(dist,dist + 801,1LL << 60);
	PQ<pl,vector<pl>,greater<pl> > pq;
	pq.push(mp(0,A)); dist[A] = 0; cnt[A] = 1;
	while(!pq.empty()){
		int u = pq.top().yy; ll d = pq.top().xx; pq.pop();
		if(dist[u] != d) continue;
		for(auto e : G[u]){
			e.xx += d;
			if(e.xx < dist[e.yy]){
				dist[e.yy] = e.xx;
				pq.push(e);
				cnt[e.yy] = 0;
			}
			cnt[e.yy] += cnt[u] * (e.xx == dist[e.yy]);
		//	cnt[e.yy] = min(cnt[e.yy],2);
		}
	}
	puts((cnt[B] == 1) ? "UNIQUE" : "AMBIGUOUS");
	return 0;
}
