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

const int MAX = 100'010;
int H[MAX];
int n;
vi V,ST,aux;
int diff[MAX];

int main(){
	int q; scanf("%d %d",&n,&q);	
	loop(i,n) scanf("%d",H + i);
	loop(i,n-1) {
		diff[i] = abs(H[i + 1] - H[i]),V.pb(diff[i]);
	sort(all(V));
	V.resize(unique(all(V)) - V.begin());
	loop(i,n-1) diff[i] = lower_bound(all(V),diff[i]) - V.begin();
	loop(t,q){
		int l,r; scanf("%d %d",&l,&r); l--,r--;
		V.clear();
		for(int i = l;i < r;i++) V.pb(diff[i]);
		print(V,int);
		vi L(sz(V)),R(sz(V));
		ST.clear();
		for(int i = 0; i < sz(V);i++){
			while(!ST.empty() && V[ST.back()] <= V[i]) ST.pop_back();
			L[i] = ST.empty() ? -1 : ST.back();
			ST.pb(i);
		}
		ST.clear();
		for(int i = sz(V)-1;i >= 0;i--){
			while(!ST.empty() && V[ST.back()] <= V[i]) ST.pop_back();
			R[i] = ST.empty() ? sz(V) : ST.back();
			ST.pb(i);
		}
		ll ans = 0;
		for(int i = 0;i < sz(V);i++){
			ans += V[i] *1LL* (i - L[i]) *1LL* (R[i] - i);
		}
		cerr << ans << endl;
	}
	
	return 0;
}
