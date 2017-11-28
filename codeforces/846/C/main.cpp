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

vi IDX[1 << 20];
int n;
int A[1 << 20];


ll get_cnt(vi & V){
	int lst = -1;
	ll ret = 0;
	for(int x : V) {
		ll l = x - lst - 1;
		ret += l*(l + 0LL);
		lst = x;
	}
	ll l = n - lst - 1;
	ret += l*(l + 0LL);
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) {
		scanf("%d",A + i);
		IDX[A[i]].pb(i);
	}
	ll ans = 0;
	ll tot = n*1LL*n;
	for(int i = 0;i < (1 << 20);i++)
		if(!IDX[i].empty()){
			ll tmp = tot - get_cnt(IDX[i]);
		//	cerr << i << " " << tmp << endl;
			ans += tmp;
		}
	printf("%.10f\n",ans*1.0/tot);
	return 0;
}
