#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); //cout << endl
#define vi vector<int>
#define sz(x) x.size()
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

struct pi{
	ll first,second;
public:
	pi():first(1LL << 62),second(1LL << 62){}
	pi(ll a,ll b):first(a),second(b){}
	bool operator () (const pi & p1,const pi & p2){
		return (p1.first == p2.first) ? (p1.second > p2.second) : (p1.first > p2.first);
	}
	bool operator > (const pi & p2){
		return (first == p2.first) ? (second > p2.second) : (first > p2.first);
	}
	friend ostream& operator<<(ostream &stream, const pi & p){
		stream << "(" << p.first << " ," << p.second << ")";
		return stream;
	}
};

ll F[500000];
int n;
ll A[500000];
priority_queue<pi,vector<pi>,pi> pq;


void solve(){
	if(sz(pq) == 1){
		F[pq.top().second] = n == 1;
		return;
	}
	ll u = pq.top().second,wu = pq.top().first; pq.pop();
	ll v = pq.top().second,wv = pq.top().first; pq.pop();
	//cout << "m = " << u << " " << v << endl;
	pq.push(pi(wu + wv,u));
	solve();
	F[v] = ++F[u];
	//cout << u << " " << F[u] << endl;
	//cout << v << " " << F[v] << endl;
}

int main(){
	pre();
	scanf("%d",&n);
	loop(i,n) scanf("%lld",A + i),pq.push(pi(A[i],i));
	solve();
	ll ans = 0;
	loop(i,n) ans += A[i] * F[i];
	printf("%lld\n",ans);
	return 0;
}
