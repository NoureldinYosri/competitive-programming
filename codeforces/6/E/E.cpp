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

const int MAX = 2e5;
pi ST[MAX << 2];
int H[MAX],n,k;

pi merge(pi a,pi b){
	return mp(min(a.xx,b.xx),max(a.yy,b.yy));
}

pi build(int node,int s,int e){
	if(s == e) return ST[node] = mp(H[s],H[s]);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	return ST[node] = merge(build(left,s,m),build(right,m + 1,e));
}

pi get(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return get(left,s,m,l,r);
	if(m  < l) return get(right,m + 1,e,l,r);
	return merge(get(left,s,m,l,m),get(right,m+1,e,m+1,r));
}

int main(){
	scanf("%d %d",&n,&k);
	loop(i,n) scanf("%d",H + i);
	build(1,0,n - 1);
	int mx = 0;
	vector<pi> pos;
	loop(i,n){
		int s = i,e = n - 1;
		while(s < e){
			int m = s + ((e - s + 1) >> 1);
			pi q = get(1,0,n - 1,i,m);
			if(q.yy - q.xx <= k) s = m;
			else e = m - 1;
		}
		if(s - i + 1 > mx) {
			mx = s - i + 1;
			pos.clear();
			pos.pb(mp(i,s));
		}
		else if(s - i + 1 == mx) pos.pb(mp(i,s));
	}
	printf("%d %lu\n",mx,sz(pos));
	for(auto p : pos) printf("%d %d\n",p.xx + 1,p.yy + 1);
	return 0;
}
