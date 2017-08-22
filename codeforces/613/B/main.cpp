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

int n,A,cf,cm;
vi V,O;
ll pref [1 << 20];

void PRINT(int cnt,int mn){
	vp T;
	loop(i,n) T.pb(mp(O[i],i));
	sort(all(T));
	loop(i,cnt) {
		int j = T[n-1-i].yy;
		O[j] = A;
	}
	loop(i,n) {
		int j = T[i].yy;
		if(O[j] < mn) O[j] = mn;
	}
	loop(i,n) printf("%d%c",O[i]," \n"[i==n-1]);
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	ll m ;
	scanf("%d %d %d %d %lld",&n,&A,&cf,&cm,&m);
	V = vi(n);
	loop(i,n) scanf("%d",&V[i]);
	O = vi{all(V)};
	sort(all(V));
	loop(i,n) pref[i] = V[i] + (i ? pref[i - 1] : 0);
	ll cost = 0,ans = 0;
	int cnt = 0;
	pi choice;
	for(int i = 0;i <= n;i++){
		if(i) {
			cost += (A - V.back());
			V.pop_back();
			cnt++;
		}
		if(cost > m) break;
		if(V.empty()) {
			ll tmp = cnt*1LL*cf + cm*1LL*A;
			if(tmp > ans){
				ans = tmp;
				choice = mp(i,A);
			}
			break;
		}
		int s = 0,e = A;
		while(s < e) {
			int mid = s + (e - s + 1)/2;
			ll tmp = 0;
			auto p = upper_bound(all(V),mid) - V.begin();
			if(p != 0){
				--p;
				tmp = (mid*(p + 1LL) - pref[p]) + cost;
			}
			if(tmp <= m) s = mid;
			else e = mid - 1;
		}
		ll tmp = cnt * 1LL * cf + s*1LL*cm;
		if(tmp > ans){
			ans = tmp;
			choice = mp(i,s);
		}
	}
	cout << ans << endl;
	PRINT(choice.xx,choice.yy);
	return 0;
}
