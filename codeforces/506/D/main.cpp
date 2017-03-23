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

const int MAX = 100'000 + 10;
int n,m;
map<int,int> ans[MAX];
int id[MAX],W[MAX];
map<int,int> CE[MAX];


int find(int a){
	return id[a] = (a == id[a]) ? a : find(id[a]);
}

void join(int a,int b){
	a = find(a), b = find(b);
	if(a == b) return ;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
}

int main(){
	scanf("%d %d",&n,&m);
	iota(id,id + m + 1,0);
	fill(W,W + m + 1,1);
	range(i,1,m){
		int a,b,c; scanf("%d %d %d",&a,&b,&c);
		int g1 = (CE[a].find(c) == CE[a].end()) ? -1 : CE[a][c];
		int g2 = (CE[b].find(c) == CE[b].end()) ? -1 : CE[b][c];
		CE[a][c] = CE[b][c] = i;
		if(g1 != -1) join(g1,i);
		if(g2 != -1) join(g2,i);
	}
	int Q; scanf("%d",&Q);
	while(Q--){
		int a,b; scanf("%d %d",&a,&b);
		if(sz(CE[a]) > sz(CE[b])) swap(a,b);
		if(ans[a].find(b) == ans[a].end()) {
			int tmp = 0;
			for(auto & p : CE[a]) {
				int c = p.xx,e1 = p.yy;
				if(CE[b].find(c) == CE[b].end()) continue;
				int e2 =  CE[b][c];
				tmp += find(e1) == find(e2);
			}
			ans[a][b] = tmp;
		}
		printf("%d\n",ans[a][b]);
	}	
	return 0;
}
