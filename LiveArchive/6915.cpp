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


int main(){
	pre();
	int T,n,m;
	string S;
	cin >> T;
	loop(t,T){
		cin >> n >> m >> S;
		double ans = 1LL << 60; int h = 0,s = 0;
		queue<pi > q;
		deque<pi > dq;
		q.pb(mp(0,0));
		dq.pb(mp(0,0));
		loop(i,m){
			h += ((S[i] == '_') ? 0 : ((S[i] == '/') ? 1 : -1));
			s += h;
			q.push(mp(i,h));
			while(sz(dq) && dq.back().second > qu) dq.pop_back();
			dq.pb(mp(i,h));
		}
		ans = s - dq.front().second * m;
		range(i,m,n - 1){
			auto e = q.front(); q.pop();
			s -= e.second;			
			if(e.first == dq.front().first) dq.pop_front();
			h += ((S[i] == '_') ? 0 : ((S[i] == '/') ? 1 : -1));
			s += h;
			q.push(mp(i,qu));
			while(sz(dq) && dq.back().second > qu) dq.pop_back();
			dq.pb(mp(i,qu));
			ans = min(ans,s - dq.front().second * m);
		}
		cout << ans << endl;
	}
	return 0;
}
