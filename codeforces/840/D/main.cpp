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


const int MAXN = 300*1000 + 10,B = 11;
const int MAXST = 1 << 20;
int n,Q;
vi ST[MAXST];
int A[MAXN];
vi IDX[MAXN];

void work(int s,int e,vi & V) {
	static vi aux;
	aux.clear();
	for(int i = s;i <= e;i++)
		aux.push_back(A[i]);
	sort(all(aux));
	int target = (e-s+1)/B;
	for(int i = 0;i < sz(aux);) {
		int j = i;
		while(j < sz(aux) && aux[i] == aux[j]) j++;
		int cnt = j-i;
		if(cnt >= target)
			V.push_back(aux[i]);
		i = j;
	}
}

void build(int cur,int s,int e) {
	if(s == e) {
		ST[cur].push_back(A[s]);
		return;
	}
	int m = (s+e) >> 1,left = 2*cur+1,right = left+1;
	build(left,s,m);
	build(right,m+1,e);
	work(s,e,ST[cur]);
}

inline int getCount(int x,int l,int r) {
	const vi & V = IDX[x];
	return upper_bound(all(V),r) - lower_bound(all(V),l);
}

int ans;
int lst[MAXN],cur_time;

void query(int cur,int s,int e,int l,int r,int target) {
	if(l <= s && e <= r){
		for(int x : ST[cur]) {
			if(x >= ans) break;
			if(lst[x] == cur_time) continue;
			lst[x] = cur_time;
			int cnt = getCount(x,l,r);
			if(cnt > target){
				ans = x;
				return;
			}
		}
		return ;
	}
	int m = (s+e) >> 1,left = 2*cur+1,right = left+1;
	if(min(r,e) <= m) return query(left,s,m,l,r,target);
	else if(m < max(s,l)) return query(right,m+1,e,l,r,target);
	else {
		query(left,s,m,l,r,target);
		query(right,m+1,e,l,r,target);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d",&n,&Q);
	for(int i = 1;i <= n;i++) {
		scanf("%d",A + i);
		IDX[A[i]].push_back(i);
	}
	build(0,1,n);
	while(Q--) {
		int l,r,k;
		scanf("%d %d %d",&l,&r,&k);
		int target = (r-l+1)/k;
		ans = INT_MAX;
		cur_time++;
		query(0,1,n,l,r,target);
		if(ans == INT_MAX) ans = -1;
		printf("%d\n",ans);
	}
	return 0;
}
