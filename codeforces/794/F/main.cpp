#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcountll(x)
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

const int MAX = 1e5 + 1e2;
ll ST[MAX << 2][10];
int IN[MAX << 2][10];
int A[MAX],n,m;

void build(int node,int s,int e){
	loop(i,10) IN[node][i] = 1 << i;
	if(s == e){
		for(int x = A[s],p10 = 1;x > 0;x /= 10,p10 *= 10)
			ST[node][x%10] += p10;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	loop(i,10) ST[node][i] = ST[left][i] + ST[right][i];
}


void update(int node,int child){
	ll auxS[10] = {0};
	int auxC[10] = {0};
	for(int y = 0;y < 10;y++)
		for(int x = 0;x < 10;x++)
			if(IN[node][y] & (1 << x)){
				auxS[y] += ST[child][x];
				auxC[y] |= IN[child][x];
			}

	loop(i,10) {
		ST[child][i] = auxS[i];
		IN[child][i] = auxC[i];
	}
}

void push(int node,int s,int e){
	int left = node << 1,right = left | 1;
	update(node,left);
	update(node,right);
	loop(i,10) IN[node][i] = 1 << i;
}

void update(int node,int s,int e,int l,int r,int x,int y){
	if(l <= s && e <= r) {
		ST[node][y] += ST[node][x];
		ST[node][x] = 0;
		IN[node][y] |= IN[node][x];
		IN[node][x] = 0;
		return;
	}
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r,x,y);
	else if(m < l) update(right,m+1,e,l,r,x,y);
	else update(left,s,m,l,m,x,y),update(right,m+1,e,m+1,r,x,y);
	loop(i,10) ST[node][i] = ST[left][i] + ST[right][i];
}

ll eval(int node){
	ll ret = 0;
	loop(i,10) ret += ST[node][i] * i;
	return ret;
}

ll query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return eval(node);
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	else if(m < l) return query(right,m+1,e,l,r);
	else return query(left,s,m,l,m) + query(right,m+1,e,m+1,r);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&m);
	range(i,1,n) scanf("%d",A + i);
	build(1,1,n);
	while(m--){
		int type,l,r; scanf("%d %d %d",&type,&l,&r);
		if(type == 1){
			int x,y; scanf("%d %d",&x,&y);
			if(x == y) continue;
			update(1,1,n,l,r,x,y);
		}
		else printf("%lld\n",query(1,1,n,l,r));
	}
	return 0;
}
