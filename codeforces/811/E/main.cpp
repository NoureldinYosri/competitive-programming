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

const int MAX = 100*1000 + 10;
int grid[10][MAX];
int n;

struct vertex{
	int L[10],R[10];
	int cnt;
};



vertex ST[MAX << 2];
int color[1 << 20];
int W[20],ID[20],aux[20];


inline int find(int a){
	return ID[a] = (a == ID[a]) ? a : find(ID[a]);
}

inline int join(int a,int b){
	a = find(a),b = find(b);
	if(a == b) return 0;
	if(W[a] < W[b]) swap(a,b);
	W[a] += W[b];
	ID[b] = a;
	return 1;
}


vertex merge(vertex A,vertex B,bool debug = 0){
	int m = 0;
	for(int i = 0;i < n;i++) aux[m++] = A.R[i];
	for(int i = 0;i < n;i++) aux[m++] = B.L[i];
	sort(aux,aux + m);
	m = unique(aux,aux + m) - aux;
	for(int i = 0;i < m;i++) ID[i] = i,W[i] = 1;
	vertex ret;
	ret.cnt = A.cnt + B.cnt;
	for(int i = 0;i < n;i++) if(color[A.R[i]] == color[B.L[i]]){
		int x = A.R[i],y = B.L[i];
		x = lower_bound(aux,aux + m,x) - aux;
		y = lower_bound(aux,aux + m,y) - aux;
		ret.cnt -= join(x,y);
	}
	for(int i = 0;i < n;i++){
		int x = A.L[i];
		if(binary_search(aux,aux + m,x)) {
			x = lower_bound(aux,aux + m,x) - aux;
			x = find(x);
			x = aux[x];
		}
		ret.L[i] = x;
	}
	for(int i = 0;i < n;i++){
		int x = B.R[i];
		if(binary_search(aux,aux + m,x)) {
			x = lower_bound(aux,aux + m,x) - aux;
			x = find(x);
			x = aux[x];
		}
		ret.R[i] = x;
	}
	return ret;
}

void init(int *V,int col,int & ctr){
	static int cnt = 0;
	ctr = 0;
	for(int i = 0;i < n;){
		++cnt;
		++ctr;
		int j = i;
		color[cnt] = grid[i][col];
		while(j < n && grid[i][col] == grid[j][col]) {
			V[j] = cnt;
			j++;
		}
		i = j;
	}
}

void build(int node,int s,int e){
	if(s == e) {
		init(ST[node].L,s,ST[node].cnt);
		copy(ST[node].L,ST[node].L + n,ST[node].R);
	}
	else {
		int m = (s + e) >> 1,left = node << 1,right = left | 1;
		build(left,s,m);
		build(right,m+1,e);
		ST[node] = merge(ST[left],ST[right]);
	}
}

vertex query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return merge(query(left,s,m,l,m),query(right,m+1,e,m+1,r));
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int q,m; scanf("%d %d %d",&n,&m,&q);
	loop(i,n) loop(j,m) scanf("%d",&grid[i][j]);

	build(1,0,m-1);
	while(q--){
		int l,r; scanf("%d %d",&l,&r);
		l--,r--;
		printf("%d\n",query(1,0,m-1,l,r).cnt);
	}
	return 0;
}
