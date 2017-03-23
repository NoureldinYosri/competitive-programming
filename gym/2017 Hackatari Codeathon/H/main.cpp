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
int val[MAX],ord[MAX],n;

int main(){
	scanf("%d",&n);


	ll sum = 0;
	range(i,1,n){
		scanf("%d",val + i);
		ord[i-1] = i;
		sum += val[i];
	}
	sort(ord,ord + n,[](const int & a,const int & b){
		return val[a] < val[b];
	});
	ll ans = 0;
	loop(j,n-1){
		int i = ord[j];
		ans += (sum -= val[i]);	
	}
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
