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

const int MAX = 1000*1000;
ll ST[MAX << 2],LA[MAX << 2];
int A[MAX],n;


pair<ll,int> get_min(pair<ll,int> a,pair<ll,int> b){
	if(a.xx < b.xx) return a;
	else return b;
}


void update(int node,int s,int e,int l,int r,ll v){
	if(l <= s && e <= r) {
		ST[node] += (e - s + 1LL)*v;
		LA[node] += v;
		return ;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) update(left,s,m,l,r,v);
	else if(m < l) update(right,m+1,e,l,r,v);
	else update(left,s,m,l,m,v),update(right,m+1,e,m+1,r,v);
	ST[node] = ST[left] + ST[right] + (e - s + 1LL)*LA[node];
}

ll get(int node,int s,int e,int p){
	if(s == e) return A[s] + LA[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) return get(left,s,m,p) + LA[node];
	else return get(right,m+1,e,p) + LA[node];
}


ll query(int node,int s,int e,int l,int r){
	if(l <= s && e <= r) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	ll ret = 0;
	if(r <= m) ret = query(left,s,m,l,r);
	else if(m < l) ret = query(right,m+1,e,l,r);
	else ret = query(left,s,m,l,m) + query(right,m+1,e,m+1,r);
	ret += (r - l + 1)*LA[node];
	return ret;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	ll M;
	scanf("%d %d",&n,&M);
	loop(i,n) scanf("%d",A + i);
	ll ans = 0;
	int lst = 0;
	int j = n-1;
	for(int i = n-1;i >= 0;i--){
		if(i != n-1 && A[i] >= lst){
			int s = i+1,e = n-1;
			while(s < e) {
				int m = s + (e - s + 1)/2;
				if(get(1,0,n-1,m) <= A[i] + m - i) s = m;
				else e = m - 1;
			}
			cerr << i << " -> " << s << endl;
			update(1,0,n-1,i+1,s,A[i] - lst + 1);
		}
		lst = A[i];
		while (i < j && query(1,0,n-1,i,j) > M) j--;
		ans += j - i + 1;
		cerr << i << " " << j << " " << query(1,0,n-1,i,j) << endl;
	}
	cout << ans << endl;
	return 0;
}
