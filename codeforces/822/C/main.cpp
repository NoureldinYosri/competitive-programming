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
#define pl pair<ll,ll>
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

const int MAX = 200*1000 + 10;
ll mnCost[MAX];
int n,x;
int L[MAX],R[MAX],price[MAX];
bool valid[MAX];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&n,&x);
	fill(mnCost,mnCost + MAX,INT_MAX);
	ll ans = INT_MAX;
	vector<pair<pi,int> > V;
	V.reserve(2*n);
	loop(i,n){
		scanf("%d %d %d",L + i,R + i,price + i);
		R[i]++;
		V.pb(mp(mp(L[i],0),i));
		V.pb(mp(mp(R[i],-1),i));
	}
	bool found = 0;
	sort(all(V));
	for(auto e : V){
		int idx = e.yy,type = e.xx.yy,len = R[idx] - L[idx];
		if(len > x) continue;
		if(type == -1) {
			mnCost[len] = min(mnCost[len],price[idx] + 0LL);
			valid[len] = 1;
		}
		else {
			ans = min(ans,price[idx] + mnCost[x - len]);
			found |= valid[x - len];
		}
	}
	if(!found) ans = -1;
	cout << ans << endl;
	return 0;
}
