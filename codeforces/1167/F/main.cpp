#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAX = 500*1000 + 10,mod = 1e9 + 7;
int A[MAX],n;
int ord[MAX];
int ST[1 << 20],LA[1 << 20];


int add(int a,int b) {
	a += b;
	if(a >= mod) a -= mod;
	if(a < 0) a += mod;
	return a;
}
int mul(int a,int b){
	return (a*(ll)b)%mod;
}

void update(int cur,int s,int e,int v) {
	ST[cur] = add(ST[cur],mul(v,e-s+1));
	LA[cur] += v;
}

void push(int cur,int s,int e) {
	if(!LA[cur]) return;
	int m = (s + e) >> 1,left = 2*cur+1,right = left + 1;
	update(left,s,m,LA[cur]);
	update(right,m+1,e,LA[cur]);
	LA[cur] = 0;
}

void update(int cur,int s,int e,int l,int r) {
	if(l <= s && e <= r) return update(cur,s,e,1);
	push(cur,s,e);
	int m = (s + e) >> 1,left = 2*cur+1,right = left + 1;
	if(r <= m) update(left,s,m,l,r);
	else if(m < l) update(right,m+1,e,l,r);
	else {
		update(left,s,m,l,m);
		update(right,m+1,e,m+1,r);
	}
	ST[cur] = add(ST[left],ST[right]);
}

int query(int cur,int s,int e,int l,int r) {
	if(l <= s && e <= r) return ST[cur];
	push(cur,s,e);
	int m = (s + e) >> 1,left = 2*cur+1,right = left + 1;
	if(r <= m) return query(left,s,m,l,r);
	if(m < l) return query(right,m+1,e,l,r);
	return add(query(left,s,m,l,m),query(right,m+1,e,m+1,r));
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
		ord[i] = i;
	}
	sort(ord,ord + n,[](const int & a,const int & b) {
		return A[a] < A[b];
	});

	int ans = 0;
	loop(j,n) {
		int i = ord[j];
		int v = A[i];
		i++;
		int f = query(0,0,n,i,n);
		int s = query(0,0,n,0,i-1);
		int t = mul(i,n+1-i);
		f = mul(f,i);
		s = mul(s,n+1-i);
//		cerr << v << ": (" << f << " - " << s << " + " << t << ") * " << v << endl;
		int tmp = add(add(f,-s),t);
		tmp = mul(tmp,v);
//		cerr << v << ": " << tmp << endl;
		ans = add(ans,tmp);
		update(0,0,n,i,n);
	}
	printf("%d\n",ans);
	return 0;
}
