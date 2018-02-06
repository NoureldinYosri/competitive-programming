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


const string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
struct node{
	int cnt[62],siz;
};
const int MAXN = 200*1000 + 10,MAX = 1 << 18;
node ST[MAX*2];
ll lazy[MAX*2];
char str[MAXN];

node merge(node l,node r) {
	node ret;
	ret.siz = l.siz + r.siz;
	loop(i,sz(alphabet)) ret.cnt[i] = l.cnt[i] + r.cnt[i];
	return ret;
}

void build(int cur,int s,int e) {
	if(s == e) {
		int c = lower_bound(all(alphabet),str[s-1]) - alphabet.begin();
		ST[cur].cnt[c]++;
		ST[cur].siz++;
		return ;
	}
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
	ST[cur] = merge(ST[left],ST[right]);
}

void update(int cur,int c) {
	if(ST[cur].cnt[c] == 0) return;
	ST[cur].siz -= ST[cur].cnt[c];
	ST[cur].cnt[c] = 0;
	lazy[cur] |= 1LL << c;
}

void push(int cur) {
	if(!lazy[cur]) return;
	int left = 2*cur + 1,right = left + 1;
	loop(i,sz(alphabet))
		if((lazy[cur] >> i) & 1)
			update(left,i),update(right,i);
	lazy[cur] = 0;
}

void update(int cur,int s,int e,int l,int r,int c) {
	if(ST[cur].cnt[c] == 0) return;
	if(l <= s && e <= r) return update(cur,c);
	push(cur);
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(r <= m) update(left,s,m,l,r,c);
	else if(m < l) update(right,m+1,e,l,r,c);
	else update(left,s,m,l,m,c),update(right,m+1,e,m+1,r,c);
	ST[cur] = merge(ST[left],ST[right]);
}

int lowerBound(int cur,int s,int e,int pos) {
	if(s == e) return s;
	push(cur);
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(ST[left].siz >= pos) return lowerBound(left,s,m,pos);
	return lowerBound(right,m+1,e,pos - ST[left].siz);
}

void dfs(int cur,int s,int e) {
	if(ST[cur].siz == 0) return ;
	if(s == e) {
		loop(i,sz(alphabet)) if(ST[cur].cnt[i]) putchar(alphabet[i]);
		return;
	}
	push(cur);
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	dfs(left,s,m);
	dfs(right,m+1,e);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int n,m; scanf("%d %d",&n,&m);
	scanf("%s",str);
	build(0,1,n);
	while(m--) {
		int l,r; char c;
		scanf("%d %d %c",&l,&r,&c);
		l = lowerBound(0,1,n,l);
		r = lowerBound(0,1,n,r);
//		cerr << l << " " << r << endl;
		update(0,1,n,l,r,lower_bound(all(alphabet),c) - alphabet.begin());
	}
	dfs(0,1,n);
	puts("");
	return 0;
}
