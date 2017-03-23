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

ll convert(ll x,ll b,ll & y){
	if(!x){
		y = 0;
		return 1;
	}
	ll t ;
	if(x%b <= 9 && convert(x/b,b,t)){
		y = t*10 + x%b;
		return 1;
	}
	else return 0;
}

bool LESS(ll b,ll *A,ll n){
	ll x = 0;
	loop(i,4){
		if(x > n/b) return 0;
		x = x*b + A[i];
	}
	return x < n;
}
bool EQUAL(ll b,ll *A,ll n){
	ll x = 0;
	loop(i,4){
		if(x > n/b) return 0;
		x = x*b + A[i];
	}
	return x == n;
}
int main(){
	ll n,l;	cin >> n >> l;
	int MAX = 1000*100;
	for(ll b = n;n - b < MAX;b--){
		ll y;
		if(convert(n,b,y) && y >= l){
			cout << b << endl;
			return 0;
		}
	}
	ll ans = 0;
	range(t,min(l,9999LL),9999){
		ll A[4],x = t;
		for(int i = 0;i < 4;i++){
			A[i] = x%10;
			x /= 10;
		}
		reverse(A,A + 4);
		x = 1; int p = 3;
		loop(i,4) if(A[i]) {
			x = A[i];
			p = 3-i;
			break;
		}
		ll b = max(1.0,pow(n*1.0/x,1.0/p) - 10);
		while(LESS(b,A,n)) b++;
		if(EQUAL(b,A,n)) ans = max(ans,b);
	}

	for(ll b = MAX;b ;b--){
		ll y;
		if(convert(n,b,y) && y >= l){
			ans = max(ans,b);
			cout << ans << endl;			
			return 0;
		}
	}

	return 0;
}
