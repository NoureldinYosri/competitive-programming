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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 2500 + 10;
pi P[MAX],Q[2*MAX];
int n;

pi operator - (const pi & a,const pi & b){
	return pi(a.first - b.first,a.second - b.second);
}


pi operator + (const pi & a,const pi & b){
	return pi(b.first + a.first,b.second + a.second);
}


int getHalf(const pi & a) {
	if(a.second > 0) return 0;
	if(a.second < 0) return 1;
	assert(a.first);
	return (a.first > 0) ? 0 : 1;
}

ll cross(pi a,pi b) {
	return a.first*(ll)b.second - a.second*(ll)b.first;
}

auto cmp = [](const pi & a,const pi & b) {
	if(getHalf(a) != getHalf(b)) return getHalf(a) < getHalf(b);
	return cross(a,b) > 0;
};

ll C(ll n,int k){
	if(k == 1) return n;
	if(k == 2) return n*(n-1)/2;
	return (n*(n-1)*(n-2))/6;
}

ll solve(int pivot) {
	int m = 0;
	loop(i,n){
		if(i != pivot)
			Q[m++] = P[i] - P[pivot];
	}
	sort(Q,Q + m,cmp);
//	cout << pivot << " sorted ";
//	loop(i,m) cout << Q[i] << " ";
//	cout << endl;
	loop(i,m) Q[i+m] = Q[i];
	int j = 0;
	ll cnt = 0;
	loop(i,m){
		int l = i+1;
		if(cross(Q[i],Q[l]) < 0) continue;
		j = max(j,l);
		while(j < 2*m && cross(Q[i],Q[j]) > 0) j++;
		ll len = j-i-1;
		cnt += C(len,2);
//		cout << P[pivot] << ": " << Q[l]+P[pivot] << " " << Q[j]+P[pivot] << " " << m-1-len << endl;
	}
//	cout << P[pivot] << ": " << cnt << " " << C(m,3) << endl;
	cnt = C(m,3) - cnt;
//	assert(cnt%3 == 0);
//	cnt /= 3;
	return cnt;
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",&P[i].first,&P[i].second);

	ll ans = 0;
	loop(i,n) ans += solve(i);
	
	ll tmp = n - 4;
	if(ans%2 == 0) ans >>= 1;
	else tmp >>= 1;
	cout << ans * tmp << endl;

	return 0;
}
