#pragma GCC optimize ("O3")
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

const int MAX = 1 << 20;
int m,n,K,T;
int A[MAX];
vector<pi> dangers[MAX];


int getReach(int p,int h){
	int r = -1;
	for(auto q : dangers[p])
		if(q.second > h)
			r = max(r,q.first);
	return r;
}

ll f(int q){
	if(q == 0) return n+1;
	ll h = A[q-1];
	int R = 0;
	ll ret = 0;
	for(int p = 0;p <= n;p++){
		R = max(R,p);
		int r = getReach(p+1,h);
		if(r > R){
			ret += 2*(r - R);
			R = r;
		}
		ret++;
	}
	return ret;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d %d",&m,&n,&K,&T);
	loop(i,m) scanf("%d",A + i);
	sort(A,A + m);
	reverse(A,A + m);
	loop(i,K){
		int l,r,d;
		scanf("%d %d %d",&l,&r,&d);
		assert(l <= r);
		dangers[l].emplace_back(r,d);
	}
	int s = 0,e = m;
	while(s < e){
		int mid = s + (e-s+1)/2;
		if(f(mid) <= T) s = mid;
		else e = mid-1;
	}
	cout << s << endl;
	return 0;
}
