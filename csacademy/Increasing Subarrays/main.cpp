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

int n,H[1 << 20];
ll A[1 << 20];
int nxt[1 << 20];
ll M;
ll pref[1 << 20];

void preprocess(){
	loop(i,n){
		A[i] = H[i] - i;
		pref[i] = A[i] + (i ? pref[i-1] : 0);
	}
	vi ST;
	for(int i = n-1;i >= 0;i--){
		while(!ST.empty() && A[ST.back()] < A[i]) ST.pop_back();
		nxt[i] = ST.empty() ? n : ST.back();
		ST.pb(i);
	}
	ST.clear();
}

ll brute_force(int s,int e) {
	if(s > e) return 0;
	ll h = H[s],ans = 0;
	for(int i = s;i <= e;i++) {
		ans += max(h - H[i],0LL);
		h = max(h,H[i]+0LL);
		h++;
	}
	return ans;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %lld",&n,&M);
	loop(i,n) scanf("%d",H + i);
	preprocess();
	ll ans = 0,cost = 0;
	multiset<int> MS;
//	prArr(nxt,n,int);
	for(int i = 0,j = 0;i < n;i++){
		while(j < n && cost <= M) {
			ll tmp = cost;
			if(!MS.empty() && *MS.rbegin() > A[j]){
				tmp += *MS.rbegin() - A[j];
			}
			if(tmp > M) {
				j--;
				break;
			}
			cost = tmp;
			MS.insert(A[j]);
			cerr << i << " to " << j << " cost = " << cost << endl;
			if(cost != brute_force(i,j)) {
				cerr << "expected " << brute_force(i,j) << " found " << cost << endl;
			}
			assert(cost == brute_force(i,j));
//			print(MS,int);
			j++;
		}
		j = min(j,n-1);
//		cerr << i << " " << j << endl;
		assert(j >= i);
		assert(cost == brute_force(i,j));
		ans += j - i + 1;
		if(nxt[i] <= j) {
			cerr << "left was " << A[i] << " nxt wall is " << nxt[i] << " with " << A[nxt[i]] << endl;
			ll contrib = A[i]*(nxt[i]-i-1LL) - (pref[nxt[i]-1] - pref[i]);
			cost -= contrib;
			assert(contrib == brute_force(i,nxt[i]-1));
		}
		else {
			cost -= A[i]*(j-i+0LL) - (pref[j] - pref[i]);
		}
		assert(sz(MS) == j-i+1);
		assert(MS.find(A[i]) != MS.end());
		MS.erase(MS.find(A[i]));
		assert(cost == brute_force(i+1,j));
		j++;
	}
	ans += n - 2;
	cout << ans << endl;
	return 0;
}
