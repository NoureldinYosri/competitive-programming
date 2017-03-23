#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

ll n,m,k,x,y;
ll f = 0,t = 0,l = 0;


int main(){
	cin >> n >> m >> k >> x >> y;
	if(n >= 4){
		//2*m*q + (q + 1)*(n - 2)*m <= k
		//q*(2*m + n*m - 2*m) + (n - 2)*m <= k
		ll q = max((k - m*(n - 2))/(n*m),1LL);
		if(k >= q*2*m+(q+1)*m*(n - 2)){
			cerr << q << endl;
			int pos = (q & 1) ? n : 1;
			k -= q*(n - 2) - 2*q;
			int r = k/m; k -= r*m;
			ll f = q,t = q + 1 + (r || k),s = -1;
			if(pos == 1) {
				pos += r + (k > 0);
				if(x <= pos){
						if(x == 1) s = q;
						else if(x < pos) s = q + 2;
						else s = q + 1 + (y <= k);
				}
				else if(x == n) s = q;
				else s = q + 1;
			}
			else {
				pos -= r + (k > 0);
				if(x >= pos){
						if(x == n) s = q;
						else if(x > pos) s = q + 2;
						else s = q + 1 + (y <= k);
				}
				else if(x == 1) s = q;
				else s = q + 1;
			}
			assert(s != -1);
			cerr << t << " " << f << " " << s << endl;
		}
		else {
			q = k/(n*m); int pos = 1;
			assert(q <= 1);
			if(q) pos = n;
			k -= n*m;
			
			
		}
	}	
	return 0;
}
