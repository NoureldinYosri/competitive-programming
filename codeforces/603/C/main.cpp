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

map<int,int> dp;
int n,k;
int A[1 << 20];

int f(int val){
	if(val == 0) return 0;
	if(val == 1) return 1;
	if(val > 10 && val%2) return 0;
	if(dp.find(val) != dp.end()) return dp[val];
	if(val%2) return dp[val] = !f(val - 1);
	int x = k*f(val/2),y = f(val - 1);
	for(int mix = 0;mix < 3;mix++)
		if(mix != x && mix != y){
			return dp[val] = mix;
		}
	assert(0);
}

string out[2] = {"Nicky","Kevin"};

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&k);
	k &= 1;
	int ans = 0;
	loop(i,n){
		int x; scanf("%d",&x);
		ans ^= f(x);
	}
	ans = ans > 0;
	cout << out[ans] << endl;
	return 0;
}
