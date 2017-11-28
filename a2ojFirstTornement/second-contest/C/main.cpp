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

int n;
int A[50];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> n;
	loop(i,n) cin >> A[i];
	vi V{A,A + n - 1};
	int T = A[n-1],ans = 0;
	while(V.size() > 1) {
		int siz =sz(V);
		ll tmp = V[siz-1] + V[siz-2];
		if(tmp < T) {
			V.pop_back();
			V.back() = tmp;
			ans++;
		}
		else {
			T = V.back();
			V.pop_back();
		}
	}
	cout << ans << endl;
	return 0;
}
