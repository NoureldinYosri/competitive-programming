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

vi L;
int n;

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	map<int,int> cnt;
	loop(i,n) {
		int x; scanf("%d",&x);
		cnt[x]++;
	}
	int mx = 0,mx2 = 0;
	for(auto ptr = cnt.rbegin();ptr != cnt.rend();ptr++){
		if(ptr->second >= 2) {
			mx = ptr->xx;
			break;
		}
	}
	cnt[mx] -= 2;
	for(auto ptr = cnt.rbegin();ptr != cnt.rend();ptr++){
		if(ptr->second >= 2) {
			mx2 = ptr->xx;
			break;
		}
	}
	cnt[mx2]--;
	cout << mx*1LL*mx2 << endl;
	return 0;
}
