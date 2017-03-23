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

int pref[1 << 20],suff[1 << 20];
vi sol;
string u,v; 

int main(){
	cin >> u >> v;
	if(sz(u) != sz(v) + 1){
		puts("0");
		return 0;
	}
	int n = sz(u);
	pref[0] = 1;
	for(int i = 0;i < n;i++){
		pref[i + 1] = pref[i] && (u[i] == v[i]);
	}	
	suff[n] = 1;
	for(int i = n-1;i;i--) {
		suff[i] = suff[i + 1] && (u[i] == v[i - 1]);
	}
	loop(i,n) if(pref[i] && suff[i + 1]) sol.pb(i + 1);
	printf("%d\n",sz(sol));
	for(int x : sol) printf("%d ",x);
	return 0;
}
