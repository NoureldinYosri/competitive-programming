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

const int MAX = 50*1000 + 10,mod = 1e9 + 7;
struct node{
    int cnt1[10],cnt2[10][10],cnt3L[10][10],cnt3R[10][10];
    int tot,len;
    node(){
    	memset(this,0,sizeof *this);
    }
};

char S[MAX];
int n,m;
node ST[MAX*4];

inline int add(int a,int b) {
	a += b;
	if (a >= mod) a -= mod;
	return a;
}
inline int mul(int a,int b) {
	return (a*1LL*b)%mod;
}
inline node merge(node L,node R) {
	node ret;
	ret.len = L.len + R.len;

	loop(d,10) ret.cnt1[d] = add(L.cnt1[d],R.cnt1[d]);

	ret.tot = L.tot + R.tot;
	loop(d1,10) loop(d2,10) ret.tot = add(ret.tot,mul(L.cnt2[d1][d2],R.cnt2[d2][d1]));
	loop(d1,10) loop(d2,10) ret.tot = add(ret.tot,mul(L.cnt3L[d1][d2],R.cnt1[d1]));
	loop(d3,10) loop(d4,10) ret.tot = add(ret.tot,mul(L.cnt1[d4],R.cnt3R[d3][d4]));

	loop(d1,10) loop(d2,10)
		ret.cnt2[d1][d2] = add(add(L.cnt2[d1][d2],R.cnt2[d1][d2]),mul(L.cnt1[d1],R.cnt1[d2]));

	loop(d1,10) loop(d2,10){
		int & val = ret.cnt3L[d1][d2];
		val = add(L.cnt3L[d1][d2],R.cnt3L[d1][d2]);
		val = add(val,mul(L.cnt1[d1],R.cnt2[d2][d2]));
		val = add(val,mul(L.cnt2[d1][d2],R.cnt1[d2]));
	}

	loop(d1,10) loop(d2,10){
		int & val = ret.cnt3R[d1][d2];
		val = add(L.cnt3R[d1][d2],R.cnt3R[d1][d2]);
		val = add(val,mul(L.cnt1[d1],R.cnt2[d1][d2]));
		val = add(val,mul(L.cnt2[d1][d1],R.cnt1[d2]));
	}

	return ret;
}

void build(int cur,int s,int e){
	if (s == e) {
		ST[cur].len = 1;
		int d = S[s] - '0';
		ST[cur].cnt1[d]++;
		return;
	}
	int m = (s+e) >>1,left = 2*cur + 1,right = left + 1;
	build(left,s,m);
	build(right,m+1,e);
	ST[cur] = merge(ST[left],ST[right]);
}

void update(int cur,int s,int e,int pos,int d) {
	if (s == e) {
		int od = S[s] - '0';
		S[s] = d + '0';
		ST[cur].cnt1[od]--;
		ST[cur].cnt1[d]++;
		return;
	}
	int m = (s+e) >> 1,left = 2*cur+1,right = left + 1;
	if (pos <= m) update(left,s,m,pos,d);
	else update(right,m+1,e,pos,d);
	ST[cur] = merge(ST[left],ST[right]);
}

node query(int cur,int s,int e,int l,int r) {
	if (l <= s && e <= r) return ST[cur];
	int m = (s+e) >> 1,left = 2*cur+1,right = left + 1;
	if (r <= m) return query(left,s,m,l,r);
	if (m < l) return query(right,m+1,e,l,r);
	return merge(query(left,s,m,l,m),query(right,m+1,e,m+1,r));
}




int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%s",S);
	n = strlen(S);
	build(0,0,n-1);

	int m; scanf("%d",&m);
	while (m-- > 0){
		int type; scanf("%d",&type);
		if (type == 1) {
			int l,r; scanf("%d %d",&l,&r); --l,--r;
			auto res = query(0,0,n-1,l,r);
			assert (res.len == r-l+1);
			printf("%d\n",res.tot);
		}
		else {
			int pos,d; scanf("%d %d",&pos,&d); --pos;
			update(0,0,n-1,pos,d);
		}
	}


	return 0;
}
