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

const ll MAX = 10000*100000LL*100000;
const int MAXS = 17910;
pair<ll,int> A[MAXS]; int cnt = 0;
void gen(){
	queue<pair<ll,int> > q;
	range(i,1,9) q.push(mp(i+0LL,i));
	while(!q.empty()){
		ll u = q.front().xx; int s = q.front().yy; q.pop();
		if(u > MAX) continue;		
		A[cnt++] = mp(u,s);
		u *= 10;
		loop(d,10){
			ll v = u + d;
			if(v%(s + d) == 0) q.push(mp(v,s+d));
		}
	}
//	cerr << cnt << endl;
}

bool is_prime(ll x){
	for(ll i = 2;i*i <= x;i++)
		if(x%i == 0)
			return 0;
	return x > 1;
}

bool cond(ll u,int s,int d){
	return is_prime(u/s) && (u*10 + d) <= MAX && is_prime(u*10+d);
}

int main(){
	gen();
	ll ans = 0;
	loop(i,cnt) {
		ll u = A[i].xx; int s = A[i].yy;
		loop(d,10) if(cond(u,s,d)){
			ans += u*10 + d;
//			cerr << u*10 + d << endl;
		}
	}
	cerr << "-------------------" << endl;
	cerr << ans << endl;
	return 0;
}
