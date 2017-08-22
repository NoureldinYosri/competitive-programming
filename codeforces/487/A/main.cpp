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
#define popcnt(x) __builtin_popcount(x)
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

ll M[3],Y[3];
ll h,a,d;
ll oo = 1LL << 60;
int INF = 1 << 30;
ll weight[3];

ll solve(int T){
	ll ans = oo;
	int ord[3] = {0,1,2},inv[3],val[3];
	sort(ord,ord + 3,[](const int & a,const int & b){
		return weight[a] < weight[b];
	});
	loop(i,3) inv[ord[i]] = i;
	for(val[0] = 0;val[0] <= T && val[0]*weight[ord[0]] < ans;val[0]++){
		for(val[1] = 0;val[0] + val[1] <= T && val[0]*weight[ord[0]] +  val[1]*weight[ord[1]] < ans;val[1]++){
			for(val[2] = 0;val[0] + val[1] + val[2] <= T && val[0]*weight[ord[0]] + val[1]*weight[ord[1]] +  val[2]*weight[ord[2]] < ans;val[2]++){
				int x = val[inv[1]],y = val[inv[2]],z = val[inv[0]];
				ll A = max(0LL,Y[1] + x - M[2]);
				ll t1 = INF;
				if (A) t1 = (M[0] + A - 1)/A;
				ll B = max(0LL, M[1] - Y[2] - y);
				ll t2 = INF;
				if (B) t2 = (Y[0] + z + B - 1)/B;
				ll cost = x*a + y*d + z*h;
				if(t1 < t2) ans = min(ans,cost);
			}
		}
	}
	return ans;
}



int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	loop(i,3) cin >> Y[i];
	loop(i,3) cin >> M[i];
	loop(i,3) cin >> weight[i];
	h = weight[0];
	a = weight[1];
	d = weight[2];
	cout << solve(1500) << endl;
	return 0;
}
