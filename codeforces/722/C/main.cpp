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

const int MAX = 100*1000 + 10;
int A[MAX],L[MAX],n;
ll pref[MAX];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,1,n) {
		scanf("%d",A + i);
		pref[i] = pref[i - 1] + A[i];
	}
	set<int> S;
	multiset<ll> MS;
	L[n] = 1;
	MS.insert(pref[n]);
	S.insert(n);
	range(i,1,n){
		int pos; scanf("%d",&pos);
		int r = *S.lower_bound(pos);
		int l = L[r];
		ll sum = pref[r] - pref[l - 1];
		MS.erase(MS.find(sum));
		S.erase(r);
		if(l != pos) {
			int x = pos - 1;
			S.insert(x);
			L[x] = l;
			MS.insert(pref[x] - pref[l - 1]);
		}
		if(pos != r) {
			int x = pos + 1;
			S.insert(r);
			L[r] = x;
			MS.insert(pref[r] - pref[x - 1]);
		}
		if(MS.empty()) puts("0");
		else printf("%lld\n",*MS.rbegin());
	}
	return 0;
}
