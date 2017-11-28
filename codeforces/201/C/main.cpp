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
int n;
int A[MAX];
ll goLeftAndDontReturn[MAX];
ll goRightAndDontReturn[MAX];
ll goLeftAndReturn[MAX];
ll goRightAndReturn[MAX];



int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	range(i,2,n) scanf("%d",A + i);
	for(int i = 2;i <= n;i++){
		int x = A[i];
		if(x == 1) continue;
		goLeftAndReturn[i] = goLeftAndReturn[i - 1] + x - (x&1);
	}
	for(int i = n-1;i >= 1;i--) {
		int x = A[i + 1];
		if(x == 1) continue;
		goRightAndReturn[i] = goRightAndReturn[i + 1] + x - (x&1);
	}
	for(int i = 2;i <= n;i++){
		int x = A[i];
		goLeftAndDontReturn[i] = goLeftAndDontReturn[i-1] + x - (x%2 == 0);
		goLeftAndDontReturn[i] = max(goLeftAndDontReturn[i],goLeftAndReturn[i]);
	}
	for(int i = n-1;i >= 1;i--) {
		int x = A[i + 1];
		goRightAndDontReturn[i] = goRightAndDontReturn[i + 1] + x - (x%2 == 0);
		goRightAndDontReturn[i] = max(goRightAndDontReturn[i],goRightAndReturn[i]);
	}
//	prArr(goLeftAndReturn+1,n,ll);
//	prArr(goLeftAndDontReturn+1,n,ll);
//	prArr(goRightAndReturn+1,n,ll);
//	prArr(goRightAndDontReturn+1,n,ll);
	ll ans = 0;
	range(i,1,n) {
		ans = max(ans,goLeftAndReturn[i]  + goRightAndDontReturn[i]);
		ans = max(ans,goRightAndReturn[i] + goLeftAndDontReturn[i]);
	}
	cout << ans << endl;
	return 0;
}
