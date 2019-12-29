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

int n,T,a,b; 
pi P[1 << 20];

int getCount(int T,int *cnt){
	if(T < 0) return 0;
	int d1 = min(T/a,cnt[0]);
	int d2 = min((T-d1*a)/b,cnt[1]);
	return d1 + d2;	
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int m; scanf("%d",&m);
	while(m--){
		scanf("%d %d %d %d",&n,&T,&a,&b);
		loop(i,n) scanf("%d",&P[i].second);
		loop(i,n) scanf("%d",&P[i].first);
		sort(P,P + n);
		int cnt[2] = {0};
		loop(i,n) cnt[P[i].second]++;
		ll duration = 0;
		int ans = getCount(P[0].first - 1,cnt);
		for(int i = 0;i < n;){
			int j = i;
			int t = P[i].first;
			while(j < n && P[j].first == t){
				duration += P[j].second ? b : a;
				cnt[P[j].second]--;
				j++;
			}
			int nt = (j < n) ? (P[j].first-1) : T;
			if(duration <= nt) ans = max(ans, j + getCount(nt - duration, cnt));			
			i = j;
		}
		printf("%d\n",ans);
	}
	return 0;
}
