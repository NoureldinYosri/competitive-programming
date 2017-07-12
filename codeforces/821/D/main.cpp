#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
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
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;


const int MAX = 10*1000 + 10;
int m,n,k;
int X[MAX],Y[MAX];
vi zero[MAX],one[MAX];
int dist[MAX];


int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&m,&n,&k);
	range(i,1,k) {
		scanf("%d %d",X + i,Y + i);
		X[i]--,Y[i]--;
	}
	++k;
	X[k] = m-1;
	Y[k] = n-1;
	loop(i,k+1) loop(j,k+1) {
		if(i == j) continue;
		int dx = abs(X[i] - X[j]),dy = abs(Y[i] - Y[j]);
		if(dx > 2 || dy > 2) continue;
		int mn = min(dx,dy);
//		int mx = max(dx,dy);

/*		cerr << "because dx = " << dx << " and dy = " << dy ;
		cerr << " add ";
		if(mn == 0) cerr << "w-0 edge " ;
		else cerr << "w-1 edge";
		cerr << "from " << i << " to " << j << endl;
*/		int c = 0;
		if(mn == 0) zero[i].pb(j);
		else if(mn ==1) one[i].pb(j),c = 1;
//		if(i < j) cerr << i << " " << j << " " << c << endl;
	}
	deque<pi> q;
	fill(dist,dist + MAX,1 << 29);
	q.pb(mp(0,0));
	dist[0] = 0;
	while(!q.empty()){
		int u = q.front().xx,d = q.front().yy;
		q.pop_front();
		if(dist[u] != d) continue;
		cerr << u << " " << d << endl;
		for(int v : zero[u]) {
			if(d < dist[v]){
				dist[v] = d;
				q.push_front(mp(v,d));
			}
		}
		for(int v : one[u]) {
			if(d+1 < dist[v]){
				dist[v] = d+1;
				q.push_back(mp(v,d+1));
			}
		}
	}
	cout << dist[k] << endl;
	return 0;
}
