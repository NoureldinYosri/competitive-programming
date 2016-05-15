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

const int MAX = 1 << 20;
int A[MAX];
pi B[MAX];

int main(){
	pre();
	int T,N;
	cin >> T;
	loop(t,T){
		cin >> N;
		set<int> S;
		loop(i,N) {
			cin >> A[i] >> B[i].first >> B[i].second;
			S.insert(A[i]);
		}
		vector<pi> V;
		loop(i,N){
			auto u = S.lower_bound(B[i].first);
			if(u == S.end()) V.pb(B[i]);
			else{
				if(*u == A[i]) ++u;
				if(u == S.end() || *u > B[i].second) V.pb(B[i]);
			}
		}
		sort(all(V));
		int ctr = 0;
		if(sz(V)){
			int s = V[0].first,e = V[0].second;
			for(auto p : V){
				s = max(s,p.first);
				if(s > e) ++ctr;
				e = max(e,p.second);
			}
			++ctr;
		}
		cout << "Case #" << t + 1 << ": "<< ctr + sz(S) << endl;
	}	
}
