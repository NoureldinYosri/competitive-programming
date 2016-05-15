#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int n,A[103];
int dx[4] = {0,0,-1,1},dy[4] = {-1,1,0,0};
int V[103][100010];
int r1,c1,r2,c2;
	
int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	
	scanf("%d",&n);
	loop(i,n) scanf("%d", &A[i + 1]);
	scanf("%d %d %d %d",&r1,&c1,&r2,&c2);
	
	queue<pi> q;
	q.push(mp(r1,c1));
	V[r1][c1] = 1;
	while(!q.empty()){
		pi u = q.front(); q.pop();
		if(u == mp(r2,c2)) break;
		loop(i,4){
			pi v = mp(u.xx + dx[i],u.yy + dy[i]);
			if(v.xx == 0 || v.xx == n + 1) continue;
			v.yy = min(v.yy,A[v.xx] + 1);
			v.yy = max(v.yy,1);	
			if(V[v.xx][v.yy] == 0){
				V[v.xx][v.yy] = V[u.xx][u.yy] + 1;
				q.push(v);
			}
		}
	}
	printf("%d\n",V[r2][c2] - 1);
	return 0;
}
