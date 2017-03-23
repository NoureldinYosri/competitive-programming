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

const int MAXN = 50010,MAXQ = 250000,MAXM = 150000,MAXB = 710;
int cnt[MAXN],is_heavy[MAXN],online[MAXN];
set<int> G[MAXN],hG[MAXN];
int n,m,q,blkSize;
char type[MAXQ];
pi Q[MAXQ];
pi E[MAXM];



int main(){
	scanf("%d %d %d",&n,&m,&q);
	int o; scanf("%d",&o);
	loop(i,o){
		int u ; scanf("%d",&u);
		online[u] = 1;
	}	
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b);
		E[i] = mp(a,b);
	}
	int x = 0,y = 0;
	loop(i,q){
		scanf(" %c %d",&type[i],&Q[i].xx);
		if(type[i] == 'A' || type[i] == 'D') scanf("%d",&Q[i].yy);
		x += type[i] == 'O' || type[i] == 'F';
		y += type[i] == 'C';
	}
	if(!y) blkSize = n;
	else blkSize = sqrt(q*x*1.0/y);
	loop(i,m){
		int a = E[i].xx,b = E[i].yy;
		G[a].insert(b);
		G[b].insert(a);
		if(sz(G[a]) > blkSize) is_heavy[a] = 1;
		if(sz(G[b]) > blkSize) is_heavy[b] = 1;
	}
	loop(i,q){
		if(type[i] == 'A' || type[i] == 'D') {
			int a = Q[i].xx,b = Q[i].yy;
			if(type[i] == 'A') {
				G[a].insert(b);
				G[b].insert(a);
				if(sz(G[a]) > blkSize) is_heavy[a] = 1;
				if(sz(G[b]) > blkSize) is_heavy[b] = 1;
			}
			else {
				G[a].erase(b);
				G[b].erase(a);
			}
		}
	}

	range(i,1,n) G[i].clear();
	
	loop(i,m){
		int a = E[i].xx,b = E[i].yy;
		if(is_heavy[b]) hG[a].insert(b);
		else G[a].insert(b);
		if(is_heavy[a]) hG[b].insert(a);
		else G[b].insert(a);
		if(is_heavy[a]) cnt[a] += online[b];
		if(is_heavy[b]) cnt[b] += online[a];
	}
	loop(i,q){
		if(type[i] == 'A'){
			int a = Q[i].xx,b = Q[i].yy;
			if(is_heavy[b]) hG[a].insert(b);
			else G[a].insert(b);
			if(is_heavy[a]) hG[b].insert(a);
			else G[b].insert(a);
			if(is_heavy[a]) cnt[a] += online[b];
			if(is_heavy[b]) cnt[b] += online[a];
		}
		else if(type[i] == 'D'){
			int a = Q[i].xx,b = Q[i].yy;
			if(is_heavy[b]) hG[a].erase(b);
			else G[a].erase(b);
			if(is_heavy[a]) hG[b].erase(a);
			else G[b].erase(a);
			if(is_heavy[a]) cnt[a] -= online[b];
			if(is_heavy[b]) cnt[b] -= online[a];
		}
		else if(type[i] == 'O'){
			int u = Q[i].xx;
			assert(!online[u]);
			online[u] = 1;
			for(int v : hG[u]) cnt[v]++;
		}
		else if(type[i] == 'F'){
			int u = Q[i].xx;
			assert(online[u]);
			online[u] = 0;
			for(int v : hG[u]) cnt[v]--;
		}
		else {
			int u = Q[i].xx,ans;
			if(is_heavy[u]) ans = cnt[u];
			else{
				ans = 0;
				for(int v : G[u]) ans += online[v];
				for(int v : hG[u]) ans += online[v];
			}
			printf("%d\n",ans);
			//cerr <<  ans << endl;
		}
	}
	
	
	return 0;
}

/*
min x * num * log(n) + y*blkSize * log(n)  + (q - x - y) log(n)

num = q/blkSize

min x* q/blkSize * logn + y*blkSize * log(n) + (q - x - y) log(n)

-(x*q*log(n))/blkSize^2 + y = 0


*/
