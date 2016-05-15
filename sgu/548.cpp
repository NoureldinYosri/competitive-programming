#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

pair<char,int> V[1 << 20];

int main(){
	pre();
	int n;
	cin >> n;
	range(i,1,n - 1) cin >> V[i].first >> V[i].second;
	priority_queue<pi,vector<pi>,greater<pi> > pq;
	range(i,1,n - 2){
		if(V[i].first == 'd') pq.push(mp(V[i].second,i));
		else while(sz(pq) && sz(pq) >= V[i].second) pq.pop();
	}
	ll ans = 0;
	vi Q;
	while(!pq.empty()){
		ans += pq.top().first;
		Q.pb(pq.top().second);
		pq.pop();
	}
	sort(all(Q));
	if(sz(Q) >= V[n - 1].second) {
		printf("%lld\n%lu\n",ans,sz(Q));
		loop(i,sz(Q)){
			if(i) putchar(' ');
			printf("%d",Q[i] + 1);
		}
		puts("");
	}
	else cout << -1 << endl;
	return 0;
}
