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


const int MAX = 1 << 20;
int n;
ll K;
int A[MAX];
ll suff[MAX];
ll pref[MAX];
int E;

ll getPrefCost(int x) {
	int i = upper_bound(A,A + n,x) - A;
	if(!i) return 0;
	i--;
	return x*(ll)(i+1) - pref[i];
}

int getE(int s,int e) {
	while(s < e) {
		int m = s + (e-s+1)/2;
		if(getPrefCost(m) <= K) s = m;
		else e = m -1;
	}
	return s;
}

ll suffCost(int x) {
	int j = upper_bound(A,A + n,x) - A;
	if(j == n) return 0;
	return suff[j] - x*(ll)(n - j);
}

int getMn(int s,ll rem) {
	int e = A[n-1];
	while(s < e) {
		int m = (s + e) >> 1;
		if(suffCost(m) <= rem) e = m;
		else s = m+1;
	}
	return s;
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %lld",&n,&K);
	loop(i,n) scanf("%d",A + i);
	sort(A,A + n);

	for(int i = n-1;i >= 0;i--)
		suff[i] = suff[i+1] + A[i];
	loop(i,n) pref[i] = A[i] + (i ? pref[i-1] : 0);




	deque<pi> dq;
	for(int i = 0;i < n;) {
		int j = i;
		while(j < n && A[i] == A[j]) j++;
		dq.emplace_back(A[i],j-i);
		i = j;
	}
//	for(auto p : dq) cout << p << " ";
//	cout << endl;
	int ans = A[n-1] - A[0];
	pi left(A[0],0);
	pi right(A[n-1],0);
	while(K > 0 && !dq.empty()){
		if(left.first == dq.front().first) {
			left.second += dq.front().second;
			dq.pop_front();
			ans = min(ans,right.first - left.first);
			continue;
		}
		if(dq.back().first == right.first) {
			right.second += dq.back().second;
			dq.pop_back();
			ans = min(ans,right.first - left.first);
			continue;
		}
		ans = min(ans,right.first - left.first);
		int d = min(dq.front().first - left.first,
					right.first - dq.back().first);
		if(left.second < right.second) {
			d = min((ll)d,K/left.second);
			d = max(d,1);
			left.first += d;
			K -= left.second*(ll)d;
		}
		else {
			d = min((ll)d,K/right.second);
			d = max(d,1);
			right.first -= d;
			K -= right.second*(ll)d;
		}
	}

	printf("%d\n",ans);
	return 0;
}
