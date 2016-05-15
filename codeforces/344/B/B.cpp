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

pi row[6000],col[6000];
int G[6000][6000];
int ROW[6000],COL[6000];

int main(){
	int m,n,k,a,b,c;
	scanf("%d %d %d",&m,&n,&k);
	loop(i,k){
		scanf("%d %d %d",&a,&b,&c); b--;
		int *p; pi *q;
		if(a == 1) p = ROW,q = row;
		else p = COL,q = col;
		p[b] = 1;
		q[b] = mp(c,i);
	}
	loop(i,m) loop(j,n){
		b = -1,c = 0;
		if(ROW[i] && row[i].yy > b) c = row[i].xx,b = row[i].yy;
		if(COL[j] && col[j].yy > b) c = col[j].xx,b = col[j].yy;
		printf("%d%s",c,(j == n - 1) ? "\n" : " ");
	}
	return 0;
}
