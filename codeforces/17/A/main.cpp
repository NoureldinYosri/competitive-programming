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

char out[2][10] = {"NO","YES"};

int main(){
	vi P;
	range(i,1,1000) {
		bool c = i != 1;
		range(j,2,i-1) if(i%j == 0) c = 0;
		if(c) P.pb(i);
	}
	vi S;
	loop(i,sz(P) - 1) if(binary_search(all(P),P[i] + P[i + 1] + 1)) S.pb(P[i] + P[i + 1] + 1);
	//print(S,int);
	int n,k; cin >> n >> k;
	cout << out[upper_bound(all(S),n) - S.begin() >= k] << endl;

	return 0;
}
