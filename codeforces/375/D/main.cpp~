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
vi G[MAX];
int ord[MAX],color[MAX],in[MAX],out[MAX],dfs_time,n;
int L[MAX],R[MAX],CNT[MAX],ans[MAX],qblk[MAX],K[MAX],qord[MAX],blkSize,m;
int ant_cnt[MAX];

void move_forward(int p){
	ant_cnt[p+1]++;
//	cerr << "move forward ant @" << p << endl;
}

void move_backward(int p){
	ant_cnt[p]--;
//	cerr << "move back ant @" << p << endl;
}


void dfs(int u,int p){
	in[u] = dfs_time;
	ord[dfs_time++] = color[u];
	for(int v : G[u]) if(v != p) dfs(v,u);
	out[u] = dfs_time - 1;
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",color + i);
	loop(i,n-1){
		int a,b; scanf("%d %d",&a,&b); a--,b--;
		G[a].pb(b);
		G[b].pb(a);
	}
	dfs(0,-1);
	blkSize = sqrt(n) + 5;
	blkSize = min(blkSize,n);
	loop(i,m){
		int a,b; scanf("%d %d",&a,&b); a--;
		L[i] = in[a]; R[i] = out[a]; K[i] = min(b,n+1);
		qblk[i] = L[i]/blkSize;
		qord[i] = i;
	}
	sort(qord,qord + m,[](const int & a,const int & b){
		return tie(qblk[a],R[a]) < tie(qblk[b],R[b]);
	});

	for(int blk = 0,i = 0;i < m;blk++){
		int l = 0,r = -1;
		memset(ant_cnt,0,sizeof ant_cnt);
		memset(CNT,0,sizeof CNT);
		for(;i < m && blk == qblk[qord[i]]; i++){
			int tl = L[qord[i]],tr = R[qord[i]];
			for(;r < tr;r++) move_forward(CNT[ord[r+1]]++);
			for(;l < tl;l++) move_backward(CNT[ord[l]]--);
			for(;l > tl;l--) move_forward(CNT[ord[l-1]]++);
			ans[qord[i]] = ant_cnt[K[qord[i]]];
		}
	}

	loop(i,m) printf("%d\n",ans[i]);
	return 0;
}

