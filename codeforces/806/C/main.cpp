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

const int MAX = 1 << 20;
ll A[MAX];
int n;

bool get_log(ll v,int & lg){
	if(v != LSOne(v)) return 0;
	lg = 0;
	while(v != (1LL << lg)) lg++;
	return 1;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%lld",A + i);
	map<int,int> cnt;
	multiset<ll> MS;
	loop(i,n) {
		int lg;
		if(get_log(A[i],lg)) cnt[lg]++;
		else MS.insert(A[i]);
	}
	int e = cnt[0];
	for(auto it = cnt.begin();it != cnt.end();it++){
		auto nxt = it; nxt++;
		if(nxt == cnt.end()) break;
		if(it->xx+1 != nxt->xx) {
			puts("-1");
			return 0;
		}
		if(nxt->yy > it->yy){
			int d = nxt->yy - it->yy;
			nxt->yy = it->yy;
			it->yy = 0;
			loop(i,d) MS.insert(1LL << (nxt->xx));
		}
		else it->yy -= nxt->yy;
	}
	for(auto it = cnt.rbegin();it != cnt.rend();it++){
		ll p2 = 1LL << (it->xx);
		while(!MS.empty() && it->yy) {
			it->yy--;
			ll v = *MS.rbegin();
			if(v > p2*2) {
				puts("-1");
				return 0;
			}
			MS.erase(MS.find(*MS.rbegin()));
		}
	}
	if(!e || !MS.empty()){
		puts("-1");
		return 0;
	}
	int s = 0;
	for(auto p : cnt) s += p.yy;
	s = e;
	while(s > 1)
	for(;s <= e;++s) printf("%d%c",s," \n"[s==e]);

	return 0;
}
