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

const int MAX = 100*1000 + 10;
char line[MAX];
valarray<int> ST[MAX*4];
int LA[MAX*4],n,m;

void prVal(valarray<int> V) {
	for(int x : V) cerr << x << " ";
	cerr << endl;
}

void build(int node,int s,int e) {
	LA[node] = -1;
	ST[node] = valarray<int>(26);
	if(s == e) {
		int c = line[s] - 'a';
		ST[node][c]++;
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	ST[node] = ST[left] + ST[right];
}

void update(int node,int s,int e,int x) {
	ST[node]*=0;
	ST[node][x] = e - s + 1;
	LA[node] = x;
}

void push(int node,int s,int e) {
	if(LA[node] == -1) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	update(left,s,m,LA[node]);
	update(right,m+1,e,LA[node]);
	LA[node] = -1;
}

valarray<int> query(int node,int s,int e,int l,int r) {
	if(l <= s && e <= r) return ST[node];
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return query(left,s,m,l,m) + query(right,m+1,e,m+1,r);
}

void update(int node,int s,int e,int l,int r,int x) {
	if(l <= s && e <= r) return update(node,s,e,x);
	push(node,s,e);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r,x);
	else if(m < l) update(right,m+1,e,l,r,x);
	else update(left,s,m,l,m,x),update(right,m+1,e,m+1,r,x);
	ST[node] = ST[left] + ST[right];
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	scanf("%d %d %s",&n,&m,line);
	build(1,0,n-1);
	while(m--) {
		int l,r; scanf("%d %d",&l,&r);
		--l,--r;
		valarray<int> V = query(1,0,n-1,l,r);
		int odd = 0;
		for(int i = 0;i < 26;i++)
			if(V[i] & 1)
				odd++;
		if(odd > 1) continue;


		for(int i = 0;i < 26;i++)
			if(V[i] > 1) {
				int len = V[i]/2;
				V[i] -= 2*len;

				assert(l+len-1<r-len+1);
				update(1,0,n-1,l,l+len-1,i);
				update(1,0,n-1,r-len+1,r,i);
				l += len;
				r -= len;
			}
		for(int i = 0;i < 26;i++)
			if(V[i]) {
				update(1,0,n-1,l,l,i);
				V[i] = 0;
				break;
			}
//		for(int i = 0;i < 26;i++)
//			assert(V[i] == 0);
	}
	for(int i = 0;i < n;i++) {
		valarray<int> V = query(1,0,n-1,i,i);
		int c = 0;
		for(int j = 0;j < 26;j++)
			if(V[j])
				c = j;
		putchar(c + 'a');
	}
	puts("");
	return 0;
}
