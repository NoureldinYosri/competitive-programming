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

const int MAX = 3e5;
int n,block_size,m;
int P[MAX],H[MAX],right_most[MAX],nxt[MAX],cost[MAX];
int ST[MAX << 2];

int build(int node,int s,int e){
	if(s == e) return ST[node] = P[s] + H[s];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m + 1,e);
	return ST[node] = max(ST[left],ST[right]);
}

int update(int node,int s,int e,int p,int v){
	if(s == e) return ST[node] = v;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m + 1,e,p,v);
	return ST[node] = max(ST[left],ST[right]);
}

int query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	else if(m < l) return query(right,m + 1,e,l,r);
	return max(query(left,s,m,l,m),query(right,m + 1,e,m + 1,r));
}

void process(int l,int r){
	r = min(r,n - 1);
	for(int i = r;i >= l;i--){
		int p = upper_bound(P + i,P + n,right_most[i]) - P;
		if(p > r) {
			nxt[i] = p;
			if(p < n) cost[i] = P[p] - right_most[i];
			else cost[i] = 0;
		}
		else{
			nxt[i] = nxt[p];
			cost[i] = cost[p] + P[p] - right_most[i];
		}
	}
}

int solve(int l,int r){
	int u = l/block_size,v = r/block_size; u *= block_size; v *= block_size;
	int ans = 0;	
	while(u < v && right_most[l] < P[r] && nxt[l] <= r){
		ans += cost[l];
		l = nxt[l];
		u = l/block_size; u *= block_size;
	}
	while(right_most[l] < P[r]){
		int p = upper_bound(P + l,P + n,right_most[l]) - P;
		ans += P[p] - right_most[l];
		l = p;	
	}
	return ans;
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",P + i,H + i);

	build(1,0,n - 1);
	for(int i = n - 1;i >= 0;i--){
		int p = upper_bound(P + i,P + n,P[i] + H[i]) - P - 1;
		right_most[i] = query(1,0,n - 1,i,p);
		update(1,0,n - 1,i,right_most[i]);
	}
	
	block_size = sqrt(n) + 2;	
	block_size = min(block_size,n);
	for(int i = 0;i < n;i += block_size) process(i,i + block_size - 1);	

	//cerr << block_size << endl;
	//loop(i,n) cerr << "I'm " << i << " @" << P[i] << " with Hight " << H[i] << " and maximum right "  << right_most[i] << " ,my nxt is " << nxt[i] << " with cost " << cost[i] << endl;
	

	scanf("%d",&m); 
	int x,y;
	while(m--){
		scanf("%d %d",&x,&y); x--,y--;
		printf("%d\n",solve(x,y));
	}
	return 0;
}
