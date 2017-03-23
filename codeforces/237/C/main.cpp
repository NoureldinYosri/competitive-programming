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

const int MAX = 1000*1000;
vi P;
int not_prime[MAX + 1];
int a,b,k;

void sieve(){
	for(int i = 2;i <= MAX;i++)
		if(not_prime[i] == 0){
			P.pb(i);
			for(ll j = i*1LL*i;j <= MAX;j += i)
				not_prime[j] = 1;
		}
}

bool can(int l){
	int idx = 0;
	deque<int> dq;
	for(int x = a;x <= b - l + 1;x++){
		while(idx < sz(P) && P[idx] < x + l) dq.pb(P[idx++]);
		while(!dq.empty() && dq.front() < x) dq.pop_front();
		if(dq.size() < k) return 0;
		//cerr << x << " : ";
		//print(dq,int);
	}
	return 1;
}

int main(){
	sieve();
	cin >> a >> b >> k;
	int s = 1,e = b - a + 1;
	while(s < e){
		int m = (s + e)/2;
		if(can(m)) e = m;
		else s = m +1;
	}
	if(!can(s)) cout << -1 << endl;
	else cout << s << endl;
	return 0;
}
