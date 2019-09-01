#ifdef ACTIVE
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
using namespace std;


int I[3][1 << 20];
pair<int,pi> P[1 << 20];
int n;

int ST[1 << 20];

void update(int cur,int s,int e,int p,int v) {
	ST[cur] = max(ST[cur],v);
	if(s == e) return;
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
}
int query(int cur,int s,int e,int p) {
	if(p <= s) return ST[cur];
	int m = (s + e) >> 1,left = 2*cur + 1,right = left + 1;
	if(m < p) return query(right,m+1,e,p);
	int a = query(left,s,m,p);
	int b = query(right,m+1,e,p);
	return max(a,b);
}

void compress(int *A){
	vi aux {A,A + n};
	sort(all(aux));
	aux.resize(unique(all(aux)) - aux.begin());
	loop(i,n) A[i] = upper_bound(all(aux),A[i]) - aux.begin();
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(j,3) {
		loop(i,n) scanf("%d",&I[j][i]);
		compress(I[j]);
	}
	loop(i,n) {
		P[i].first = I[0][i];
		P[i].second.first = I[1][i];
		P[i].second.second = I[2][i];
	}
	sort(P,P + n);
	reverse(P,P + n);
	int ans = 0;
	for(int i = 0;i < n;) {
		int j = i;
		while(j < n && P[i].first == P[j].first) {
			ans += query(0,1,n+1,P[j].second.first+1) > P[j].second.second;
			j++;
		}
		for(;i < j;i++) {
			auto p = P[i].second;
			update(0,1,n+1,p.first,p.second);
		}
	}

	cout << ans << endl;
	return 0;
}
#endif
