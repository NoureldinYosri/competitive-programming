#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0,_ = (n);i < _;i++)
#define range(i,a,b) for(int i = (a),_ = (b);i <= _;i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b),_ = (a);i >= _;i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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

char G[510][510];
int n,k;
int V[510][510];
int QC[510][510],size[510*510];
int dx[] = {0,0,-1,1},dy [] = {1,-1,0,0};
int cand[4*510];
int S[510][510];

int dfs(int x,int y,int c){
	if(x < 0 || x >= n || y < 0 || y >= n) return 0;
	if(V[x][y] || G[x][y] == 'X') return 0;
	QC[x][y] = c;
	size[c] ++;
	V[x][y] = 1;
	int ret = 1;	
	loop(i,4) ret += dfs(x + dx[i],y + dy[i],c);
	return ret;
}

int main(){
	int ans = 0;
	scanf("%d %d",&n,&k);
	loop(i,n) scanf("%s",G[i]);
	loop(i,n) loop(j,n) {
		S[i][j] = G[i][j] != 'X';
		if(i) S[i][j] += S[i - 1][j];
		if(j) S[i][j] += S[i][j - 1];
		if(i && j) S[i][j] -= S[i - 1][j - 1];
	}
	int z = 1;
	loop(i,n) loop(j,n) if(!V[i][j]) dfs(i,j,z++);
	loop(i,n - k + 1) loop(j,n - k + 1){
		int idx = 0;
		if(i) {	loop(q,k) {if(QC[i - 1][j + q]) cand[idx++] = QC[i - 1][j + q];}}
		if(i + k < n) {loop(q,k) {if(QC[i + k][j + q]) cand[idx++] = QC[i + k][j + q];}}
		if(j) {	loop(q,k) {if(QC[i + q][j - 1]) cand[idx++] = QC[i + q][j - 1];}}
		if(j + k < n) {loop(q,k) {if(QC[i + q][j + k]) cand[idx++] = QC[i + q][j + k];}}
		
		sort(cand,cand + idx);
		idx = unique(cand,cand + idx) - cand;
		ll tmp = k*k;	
		loop(q,idx) tmp += size[cand[q]];
		int s = S[i + k - 1][j + k - 1];
		if(i) s -= S[i - 1][j + k - 1];
		if(j) s -= S[i + k - 1][j - 1];
		if(i && j) s += S[i - 1][j - 1];
		tmp -= s;
		ans = max(ans + 0LL,tmp);
	}
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
