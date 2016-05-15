#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
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
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

int n,A,cf,cm; ll m;
int arr[1 << 20];
int tmp[1 << 20];

ll f(int x){	
	ll _m = m,ctr = 0;
	loop(i,n) tmp[i] = arr[i];
	loop(i,n) {
		if(tmp[i] > x) break;
		if(x - tmp[i] > _m) break;
		_m -= x - tmp[i];
		tmp[i] = x;
	} 
	loop(i,n){
		if(A - tmp[n - 1 - i] > _m) break;
		++ctr;
		_m -= A - tmp[n - 1 - i];
	}
	return ctr * cf + cm * x * (tmp[0] == x);
}

int main(){
	int s = INT_MAX,e;
	scanf("%d %d %d %d %lld",&n,&A,&cf,&cm,&m);
	loop(i,n) scanf("%d",arr + i),s;
	sort(arr,arr + n);
	e = A;
	s = arr[0];
	while(e - s > 1){
		int m1 = s + (e - s + 1) / 3,m2 = m1 + (e - s + 1)/3;
		if(f(m1) < f(m2)) e = m2 - 1;
		else s = m1 + 1;	
	}
	cerr << s << " " << e << endl;
	cerr << f(s) << " " << f(e) << endl;
	return 0;
}
