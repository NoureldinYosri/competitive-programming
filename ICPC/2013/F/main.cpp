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

int A[1 << 20],n,k;

bool can(int Th) {
	int cnt = 0;
	int capacity = 0;
	for(int i = 0;i < 2*n*k;) {
		if(i + 1 < 2*n*k && A[i + 1] - A[i] <= Th) {
//			cerr << "increase capcity to " << capacity + 2*k - 2 << " by creating piles " << A[i] << " and " << A[i + 1] << endl;
			cnt++;
			i += 2;
			capacity += 2*k - 2;
		}
		else {
			if(capacity == 0) {
//				cerr << "cant discard " << A[i] << endl;
				return 0;
			}
			capacity--;
//			cerr << "discard " << A[i] << endl;
			i++;
		}
	}
	return cnt >= n;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&k);
	loop(i,2*n*k) scanf("%d",A + i);
	sort(A,A + 2*k*n);

	int s = 0,e = 1e9;
	while(s < e) {
		int m = s + (e - s)/2;
		if(can(m)) e = m;
		else s = m + 1;
	}
	cout << s << endl;
	return 0;
}
