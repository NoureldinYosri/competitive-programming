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

int m,n,k,s,d;
pair<pi,pi> E[5000];
vi G[1000 + 10];
bool vis[1000 + 10];
queue<int> q;

bool valid(int Th){
	memset(vis,0,sizeof vis);
	q.push(s); vis[s] = 1;
//	cerr << Th << ": ";
	while(!q.empty()) {
		int u = q.front(); q.pop();
//		cerr << u << " " ;
		if(u == d) return 1;
		for(int e : G[u]) {
			int r = E[e].xx.yy,fr = E[e].yy.xx,to = E[e].yy.yy;
			int v = fr + to - u;
//			cerr << u << " " ;
			if(r < Th || vis[v]) continue;
			vis[v] = 1;
			q.push(v);
		}
	}
//	cerr << endl;

	return 0;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&m,&k);
	scanf("%d %d",&s,&d);
	loop(i,m) scanf("%d %d %d %d",&E[i].yy.xx,&E[i].yy.yy,&E[i].xx.xx,&E[i].xx.yy);

	sort(E,E + m);
	int lst = -1,ans = 0;

	loop(i,m) {
		int a = E[i].yy.xx,b = E[i].yy.yy,l = E[i].xx.xx,r = E[i].xx.yy;
		G[a].pb(i);
		G[b].pb(i);



		if(!valid(l)) continue;

		int st = l,en = r;
		while(st < en) {
			int mid = st + (en - st + 1)/2;
			if(valid(mid)) st = mid;
			else en = mid - 1;
		}

		l = max(l,lst + 1);
//		cerr << l << " " << r << endl;
		ans += st - l + 1;
		lst = st;
	}

	printf("%d\n",ans);
	return 0;
}
