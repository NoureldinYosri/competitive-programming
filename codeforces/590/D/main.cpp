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

int A[150];
vi suff[150];
int n,k,s;
vi aux;

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d %d",&n,&k,&s);
	loop(i,n) scanf("%d",A + i);
	loop(i,n) sort(all(suff[i]));
	int len = 1;
	while((len + 1LL)*(len + 1LL) <= s) len++;
	ll ans = LLONG_MAX;
	for(int i = 0;i < n;i++) {
		ll tmp = 0;
		loop(j,i) tmp += A[j];
		for(int j = 0;i + j < n && j < len;j++)
			aux.pb(A[i + j]);
		if(i + sz(aux) < k) continue;
		sort(all(aux));
		for(int j = 0;j < sz(aux) && i + j < k;j++)
			tmp += aux[j];
		print(aux,int);
		cerr << i << " " << tmp << endl;
		ans = min(ans,tmp);
		aux.clear();
	}
	cout << ans << endl;
	return 0;
}
