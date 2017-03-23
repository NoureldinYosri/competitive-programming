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

int vis[3010][3010];
int A[3010],canKill[3010],canNotKill[3010],n,k;
queue<pi> q; 

void insert(int i,int j,int t){
	if(t > k) return;
	if(vis[i][j] == -1){
		vis[i][j] = t;
		q.push(mp(i,j));
	}
}

void killi(int i,int j,int t){
	if(canKill[j] && A[i] != 100) insert(j,j+1,t);
}

void killj(int i,int j,int t){
	if(A[i] && canNotKill[j]) insert(i,j+1,t);
}

void killBoth(int i,int j,int t){
	if(A[i] && canKill[j]) insert(j+1,j+2,t);
}

int bfs(){
	memset(vis,-1,sizeof vis); insert(0,1,0);
	int ans = 0;
	while(!q.empty()){
		int i = q.front().xx,j = q.front().yy; q.pop();
		ans++;		
		if(j >= n) continue;
		killBoth(i,j,vis[i][j] + 1);
		killi(i,j,vis[i][j] + 1);
		killj(i,j,vis[i][j] + 1);
	}
	return ans;
}

int main(){
	scanf("%d %d",&n,&k);
	loop(i,n) scanf("%d",A + i);
	for(int i = n-1;i >= 0;i--) canKill[i] = max(canKill[i + 1],A[i]);
	canNotKill[n] = 1;
	for(int i = n-1;i >= 0;i--) canNotKill[i] = (A[i] != 100) && canNotKill[i + 1]; 
	cout << bfs() << endl;
	
	return 0;
}
