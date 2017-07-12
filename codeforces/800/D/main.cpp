#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
using namespace std;


const int MAX = 100*1000 + 10;
int A[MAX],N;
int ST[MAX << 2],H[MAX];
ll ans = 0;
auto cmp = [](const int & a,const int & b){
	return H[a] < H[b];
};

void update(int node,int s,int e,int p,int v){
	if(s == e) {
		H[s] += v;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
	ST[node] = max(ST[left],ST[right],cmp);
}

int queryPrefix(int node,int s,int e,int p){
	if(e <= p) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) return queryPrefix(left,s,m,p);
	return max(queryPrefix(left,s,m,p),queryPrefix(right,m + 1,e,p),cmp);
}
int querySuffix(int node,int s,int e,int p){
	if(p <= s) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(m < p) return querySuffix(right,m+1,e,p);
	return max(querySuffix(left,s,m,p),querySuffix(right,m+1,e,p),cmp);
}


void update(int pos,int v){
	ll h = H[pos];
	int l = queryPrefix(1,0,N+1,pos - 1);
	int r = querySuffix(1,0,N+1,pos + 1);
	if(h < min(H[l],H[r])){
		ll d = min(H[l],H[r]) - h;
		d = min(d,v + 0LL);
		ans -= d;
	}
	else{

	}
	update(1,0,N+1,pos,v);
	h += v;
	if(min(H[l],H[r]) <= h && h <= max(H[l],H[r])) {
		ll d = h - min(H[l],H[r]);
		ll w = 0;
		if(H[l] <= H[r]) w = r - pos - 1;
		else w = pos - l - 1;
		ans += d * w;
	}
	cerr << "set " << pos << " to " << h << " and ans to " << ans << endl;
}

void build(){
	memset(ST,0,sizeof ST);
	memset(H,0,sizeof H);
	range(i,1,N) update(i,A[i]);
}



int main(){
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	int T; scanf("%d",&T);
	while(T--){
		int Q; scanf("%d %d",&N,&Q);
		range(i,1,N) scanf("%d",A + i);
		ans = 0;
		build();
		cerr << ans << endl;
		printf("%lld\n",ans);
		break;
	}
	return 0;
}

