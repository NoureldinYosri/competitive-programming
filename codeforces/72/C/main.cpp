#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
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

pair<pl,int> P[1 << 20];
int was_hit[1 << 20];

bool hit(int i,ll x,ll y){
	return (P[i].xx.xx - x)*(P[i].xx.xx - x) + y*y <= P[i].xx.yy*P[i].xx.yy;
}



int main(){
	int n,m;
	scanf("%d",&n); fill(was_hit,was_hit + n,INT_MAX);
	loop(i,n) scanf("%I64d %I64d",&P[i].xx.xx,&P[i].xx.yy),P[i].yy = i;
	sort(P,P + n);
	scanf("%d",&m);
	loop(i,m){
		ll x,y;
		scanf("%I64d %I64d",&x,&y);
		auto p = upper_bound(P,P + n,mp(mp(x,0LL),0)) - P;
		int ans = -1;
		if(hit(p,x,y)) was_hit[P[p].yy] = min(was_hit[P[p].yy],i + 1);
		if(--p != -1 && hit(p,x,y)) was_hit[P[p].yy] = min(was_hit[P[p].yy],i + 1);
	}
	int ctr = 0;
	loop(i,n) ctr += was_hit[i] != INT_MAX;
	printf("%d\n",ctr);
	loop(i,n) printf("%d%s",(was_hit[i] == INT_MAX)?-1:was_hit[i],(i == n - 1) ? "\n" : " ");
	return 0;
}
