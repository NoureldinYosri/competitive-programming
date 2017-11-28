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
int A[100];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> n;
	int tot_one = 0,tot_zero = 0;
	loop(i,n) {
		cin >> A[i];
		tot_one += A[i];
		tot_zero += !A[i];
	}
	int ans = 0,one = 0,zero = 0;
	loop(i,n) {
		ans = max(ans,n - (one + (tot_zero - zero)));
		one += A[i];
		zero += !A[i];
	}
	ans = max(ans,one);
	ans = max(ans,zero);
	cout << ans << endl;
	return 0;
}
