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
#define pl pair<ll,ll>
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

int N;
int freq[1 << 20];
ll suff[1 << 20];
ll pref[1 << 20];

ll ans[1 << 20];
void solve(){
	ll cur = 0,tot_del = 0;
	suff[N] = 0;
	for(int i = N-1;i >= 0;i--) suff[i] = freq[i] + suff[i + 1];
	loop(i,N) pref[i] = freq[i] + (i ? pref[i - 1] : 0);
	for(int i = 0;i < N;i++) {
		if(cur + freq[i] >= suff[i+1]) {
			if(cur >= suff[i]){
				ans[i] = tot_del += cur - suff[i] + 1;
				cur = suff[i] - 1;
				cur += freq[i];
			}
			else {
				ans[i] = 0;
				cur += freq[i];
			}
		}
		else {
			cur += freq[i];
			ans[i] = 1LL << 60;
		}
//		cerr << cur << endl;
	}
//	prArr(ans,N,ll);
	cur = tot_del = 0;
	for(int i = N-1;i >= 0;i--){
		ll prv = i ? pref[i - 1] : 0;
		if(prv < cur + freq[i]) {
			if(prv + freq[i] < cur){
				ans[i] = tot_del += cur - pref[i];
				cur = pref[i];
				cur += freq[i];
			}
			else {
				ans[i] = 0;
				cur += freq[i];
			}
		}
		else{
			cur += freq[i];
		}
	}
	//prArr(ans,N,ll);
	loop(i,N) printf("%lld%c",ans[i]," \n"[i==N-1]);
}

int main(){
	freopen("difficult.in", "r", stdin);
	int T; scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		loop(i,N) scanf("%d",freq + i);
		solve();
	}
	return 0;
}
