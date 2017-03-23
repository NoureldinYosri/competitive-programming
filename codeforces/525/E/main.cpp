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

ll f[19];
ll S;
int n,k,m;
int A[25];
int cur[25];
map<ll,vi> M;

int main(){
	f[0] = 1;
	loop(i,18) f[i + 1] = f[i] * (i + 1);
	cin >> n >> k >> S;
	loop(i,n) cin >> A[m++];
	ll ans = 0;	
	int m1 = m/2,m2 = m - m1;
	
	loop(msk,1 << m1){
		int q = 0;
		loop(i,m1) if(msk & (1 << i)) cur[q++] = A[i];
		loop(msk2,1 << q){
			if(popcnt(msk2) > k) continue;
			ll sum = 0;
			loop(i,q) {
				if(msk2 & (1 << i)) {
					if(cur[i] > 18) sum = S + 1;
					else sum += f[cur[i]] ;
				}
				else sum += cur[i];
				sum = min(sum,S + 1);
			}
			if(sum <= S) M[sum].pb(popcnt(msk2));
		}
		
	}
	for(auto & p : M) sort(all(p.second));
	loop(msk,1 << m2){
		int q = 0;
		loop(i,m2) if(msk & (1 << i)) cur[q++] = A[i + m1];
		loop(msk2,1 << q){
			if(popcnt(msk2) > k) continue;
			ll sum = 0;
			loop(i,q) {
				if(msk2 & (1 << i)) {
					if(cur[i] <= 18)	sum += f[cur[i]] ;
					else sum = S + 1;
				}
				else sum += cur[i];
				sum = min(sum,S + 1);
			}
			if(M.find(S - sum) != M.end()){
				ans += upper_bound(all(M[S - sum]),k - popcnt(msk2)) - M[S - sum].begin();
			}
		}
	}
		
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
