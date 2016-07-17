#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long>
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

const int MAX = 1e6 + 10;
ll cube[MAX],m;

ll f(ll n){
	ll ret = 0;
	for(int k = 2;k < MAX;k++) {
		ret += n/cube[k];
		if(ret > m) return ret;
	}
	return ret;
}

int main(){
	loop(i,MAX) cube[i] = i*1LL*i*1LL*i;
	cin >> m;
	ll s = 0,e = (MAX*1LL*MAX)*MAX;
	while(s < e){
		ll mid = s + (e - s)/2;
		if(f(mid) >= m) e = mid;
		else s = mid + 1;
	}
	cerr << s << " " << f(s) << endl;
	cout << ((f(s) == m) ? s : -1) << endl;
	return 0;
}
