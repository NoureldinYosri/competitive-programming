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


typedef pair<ll,ll> line;
typedef vector<line> lines;

const int MAX = 100*1000 + 10;
int A[MAX],n;
ll pref[MAX];
lines aux,aux2;
lines ST[MAX*3];
line B[MAX];




bool cond(line A,line B,line C){
	// x1 = (B.yy - A.yy)/(A.xx - B.xx)
	// x2 = (C.yy - B.yy)/(B.xx - C.xx)
	ll x1_t = B.yy - A.yy,x1_b = A.xx - B.xx;
	ll x2_t = C.yy - B.yy,x2_b = B.xx - C.xx;
	// x1_t/x1_b > x2_t/x2_b
	return x1_t*x2_b > x2_t*x1_b;
}

vector<line> build_CH(int l,int r){
	int len = r - l + 1;
	vector<line> CHT;
	loop(i,len) {
		int j = i + l;
		aux2.pb(B[j]);
	}
	sort(all(aux2));
	for(int i = 0;i < sz(aux2);){
		int j = i;
		ll mn = LLONG_MAX;
		while(j < sz(aux2) && aux2[i].xx == aux2[j].xx){
			mn = min(mn,aux2[j].yy);
			j++;
		}
		aux.pb(mp(aux2[i].xx,mn));
		i = j;
	}
	reverse(all(aux));
	int siz = 0;
	for(line A : aux) {
		while(siz > 1 && cond(CHT[siz-2],CHT[siz-1],A)) {
			CHT.pop_back();
			siz--;
		}
		CHT.pb(A);
		siz++;
	}

	aux.clear();
	aux2.clear();
	return CHT;
}

void build(int node,int s,int e){
	ST[node] = build_CH(s,e);
	assert(!ST[node].empty());
	if(s == e) return;
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
}


ll eval(line A,int x){
	return A.xx * x + A.yy;
}

ll get_min(vector<line> & CH,int x){
	int s = 0,e = sz(CH) - 1;
	while(e - s > 1) {
		int m1 = s + (e - s + 1)/3,m2 = m1 + (e - s + 1)/3;
		if(eval(CH[m1],x) < eval(CH[m2],x)) e = m2 - 1;
		else s = m1 + 1;
	}
	ll ret = min(eval(CH[s],x),eval(CH[e],x));
	return ret;
}

ll query(int node,int s,int e,int l,int r,int x){
	if(l <= s && e <= r) return get_min(ST[node],x);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,x);
	if(m < l) return query(right,m+1,e,l,r,x);
	return min(query(left,s,m,l,m,x),query(right,m+1,e,m+1,r,x));
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,1,n) {
		scanf("%d",A + i);
		pref[i] = pref[i - 1] + A[i];
		B[i] = mp(A[i],(i + 0LL)*A[i] - pref[i]);
	}
	build(1,1,n);
	int m; scanf("%d",&m);
	while(m--){
		int i,j; scanf("%d %d",&i,&j);
		int x = i - j;
		i = j - i + 1;
		ll ans = pref[j] + query(1,1,n,i,j,x);
		printf("%lld\n",ans);
	}
	return 0;
}
