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

const int MAX = 200*1000 + 10;
char str[MAX];
int n,m,K;
int ST[MAX*4][10],LA[MAX*4];

void build(int node,int s,int e) {
	loop(i,K) ST[node][i] = n;
	if(s == e) {
		int x = str[s] - 'a';
		ST[node][x] = s;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	LA[node] = -1;
	loop(i,K) ST[node][i] = min(ST[left][i] ,ST[right][i]);
}

void update(int node,int s,int e,int x) {
	loop(i,K) ST[node][i] = n;
	ST[node][x] = s;
	LA[node] = x;
}

void push(int node,int s,int e) {
	if(LA[node] == -1) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	update(left,s,m,LA[node]);
	update(right,m+1,e,LA[node]);
	LA[node] = -1;
}

void update(int node,int s,int e,int l,int r,int x) {
	if(l <= s && e <= r) return update(node,s,e,x);
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r,x);
	else if(m < l) update(right,m+1,e,l,r,x);
	else update(left,s,m,l,m,x),update(right,m+1,e,m+1,r,x);
	loop(i,K) ST[node][i] = min(ST[left][i] ,ST[right][i]);
}

void query(int node,int s,int e,int l,int r,int k,int *ret) {
	if(l <= s && e <= r) {
		copy(ST[node],ST[node] + K,ret);
		return ;
	}
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,k,ret);
	else if(m < l) return query(right,m+1,e,l,r,k,ret);
	int A[10],B[10];
	query(left,s,m,l,m,A);
	query(right,m+1,e,m+1,r,B);
	loop(i,K) ret[i] = min(A[i],B[i]);

}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d %s",&n,&m,&K,str);
	build(1,0,n-1);
	loop(i,m){
		int type; scanf("%d",&type);
		if(type == 1) {
			int l,r; char c;
			scanf("%d %d %c",&l,&r,&c);
			--l,--r;
			update(1,0,n-1,l,r,c - 'a');
		}
		else {
			int ans = 1;
			int l = 1,r = n-1;
			scanf("%s",str);
			string p (str);
			for(char c : p) {
				int
			}
		}
	}
	return 0;
}
