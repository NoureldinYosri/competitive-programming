#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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
const ll INF = 1LL << 60;
map<int,int> M;
vp G[MAX];
map<int,ll> dist[MAX];
int idx,x0,Y0,x1,Y1,n,who[MAX];
typedef pair<ll,pi> state;

void preprocess(int row,vp & A){
	sort(all(A));
	int l = -1,r = -1; vp B;
	for(auto p : A){
		if(p.xx <= r+1) r = max(r,p.yy);
		else {
			if(r != -1) B.pb(mp(r,l));
			l = p.xx;
			r = p.yy;
		}
	}
	B.pb(mp(r,l));
	A = B;
}

void add(int a,int b,int c,int d,ll w,PQ<state,vector<state>,greater<state> > & pq){
	//fprintf(stderr,"add (%d,%d,%lld) -> (%d,%d,%lld)\n",a,b,w,c,d,	w + max(1,abs(d - b)));
	w += max(1,abs(d - b)) 	;
	map<int,ll> & D = dist[M[c]];
	if(D.find(d) == D.end()) D[d] = INF;
	if(w < D[d]) pq.push(mp(w,mp(c,d)));	
	D[d] = min(D[d],w);
}

bool can(int a,int b,int c,int d){
	if(c < a) swap(a,c),swap(b,d);
	return c <= b + 1;
}


bool canAdd(int x,int a,int b){
	auto p = *lower_bound(all(G[M[x]]),mp(a,-1));
	swap(p.xx,p.yy);
	return p.xx <= b && b <= p.yy;
}

void add_pos(int r1,int c,int r2,ll w,PQ<state,vector<state>,greater<state> > & pq){
	auto p = lower_bound(all(G[M[r1]]),mp(c,-1));
	int left = p->yy,right = p->xx;
	//fprintf(stderr,"the bounds of (%d,%d) are (%d,%d)\n",r1,c,left,right);	
	for(auto q : G[M[r2]]){
		swap(q.xx,q.yy);
		if(can(left,right,q.xx,q.yy)) {
			add(r1,c,r2,q.xx,w,pq);
			add(r1,c,r2,q.yy,w,pq);
			if(r2 == x1 && q.xx <= Y1 && Y1 <= q.yy) add(r1,c,r2,Y1,w,pq);
			if(q.xx != q.yy) {
				add(r1,c,r2,q.xx + 1,w,pq);
				add(r1,c,r2,q.yy - 1,w,pq);
			}
			if(q.xx <= c && c <= q.yy) add(r1,c,r2,c,w,pq);
			if(q.xx <= c-1 && c-1 <= q.yy) add(r1,c,r2,c-1,w,pq);
			if(q.xx <= c+1 && c+1 <= q.yy) add(r1,c,r2,c+1,w,pq);		
		}
	}
}


ll  dijkstra(int row,int col){
	ll ret = 0;
	PQ<state,vector<state>,greater<state> > pq;
	pq.push(mp(0LL,mp(row,col))); 
	dist[M[row]][col] = 0;
	while(!pq.empty()){
		ll d = pq.top().xx; int row = pq.top().yy.xx,col = pq.top().yy.yy; pq.pop();
		//cerr << row << " " << col << " " << d << endl;
		if(row == x1 && col == Y1) return d;		
		if(row == x1 && canAdd(row,col,Y1)) add(row,col,row,Y1,d,pq);
		if(M.find(row - 1) != M.end()) add_pos(row,col,row - 1,d,pq);
		if(M.find(row + 1) != M.end()) add_pos(row,col,row + 1,d,pq);
	}
	return -1;
}

int main(){
	scanf("%d %d %d %d %d",&x0,&Y0,&x1,&Y1,&n);
	loop(i,n){
		int r,a,b;
		scanf("%d %d %d",&r,&a,&b);
		if(M.find(r) == M.end()) M[r] = idx++;
		G[M[r]].pb(mp(a,b));
		who[M[r]] = r;
	}
	n = idx;
	loop(i,n) preprocess(i,G[i]);
	/*loop(i,n){
		cerr << who[i] << " : ";
		for(auto p : G[i]) prp(p);
		cerr << endl;
	}*/
	ll ans = dijkstra(x0,Y0);
	cout << ans << endl;
	return 0;
}
