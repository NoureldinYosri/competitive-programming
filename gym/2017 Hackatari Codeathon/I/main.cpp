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

const int MAX = 200'010;
int N,K,E;
char com[MAX];
pi Q[MAX];
int val[MAX],tim[MAX],blkSize;
int m;
deque<pi> blk[500];
vp aux;

void insert(int pos,pi v,int u = 0){
	for(;(u+1)*blkSize < pos;u++);
	pos -= u*blkSize;
	if(!pos) blk[u].push_front(v);
	else{	
		deque<pi> aux;
		for(;pos;pos--){
			aux.pb(blk[u].front());
			blk[u].pop_front();
		}
		aux.pb(v);
		while(!blk[u].empty()){
			aux.pb(blk[u].front());
			blk[u].pop_front();	
		}
		blk[u] = aux;
		aux.clear();
	}
	while(sz(blk[u]) > blkSize){
		blk[u + 1].push_front(blk[u].back());		
		blk[u].pop_back();
		u++;
	}
}

int LIS(int t){
	vi lis;	
	range(i,1,m){
		if(tim[i] > t) continue;
		if(lis.empty() || lis.back() < val[i]) lis.pb(val[i]);
		else *lower_bound(all(lis),val[i]) = val[i];
	}
	return sz(lis);
}

int main(){
	scanf("%d %d %d",&N,&K,&E); blkSize = sqrt(E);
	loop(i,E) {
		scanf(" %c %d",com + i,&Q[i].xx);
		if(com[i] == '+') {
			scanf("%d",&Q[i].yy);
			insert(Q[i].xx,mp(Q[i].yy,i));
		}			
	}
	for(int u = 0;!blk[u].empty();u++)
		for(auto p : blk[u]){
			++m;			
			val[m] = p.xx;
			tim[m] = p.yy;
		}
	//prArr(val+1,m,int);
	//cerr << LIS(E-1) << endl;
	if(LIS(E-1) < K) {
		set<int> S;
		for(int i = 1;i <= N;i++) S.insert(i);
		for(int p = 0;p < E;p++)
			if(com[p] == 'p'){
				S.erase(Q[p].xx);
				if(sz(S) == 1) {
					printf("%d %d",p+1,*S.begin());
					return 0;
				}
			}
		puts("-1");
	}
	else{
		int s = 0,e = E-1;
		while(s < e){
			int m = (s + e) >> 1;
			if(LIS(m) >= K) e = m;
			else s = m + 1;
		}
		//cerr << "@" << s + 1 << endl;
		set<int> S;
		for(int i = 1;i <= N;i++) S.insert(i);
		for(int p = 0;p < E;p++)
			if(com[p] == 'p'){
				if(p > s){
					printf("%d %d",p+1,Q[p].xx);
					return 0;
				}
				else S.erase(Q[p].xx);
				if(sz(S) == 1) {
					printf("%d %d",p+1,*S.begin());
					return 0;
				}
			}
		puts("-1");
	}
	return 0;
}
