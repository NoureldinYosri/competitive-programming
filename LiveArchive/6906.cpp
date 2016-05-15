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

int id[1 << 10],W[1 << 10],ans;

int find(int a){
	return id[a] = (id[a] == a) ? a : find(id[a]);
}

void join(int a,int b){
	a = find(a),b = find(b);
	if(a == b) return;
	ans--;
	if(W[a] > W[b]) swap(a,b);
	W[a] += W[b];
	id[b] = a;
}

int main(){
	pre();
	int T,N,K;
	vi V;
	cin >> T;
	loop(t,T){
		cin >> N >> K;
		V.resize(N);
		loop(i,N) id[i] = i,W[i] = 1;
		ans = N;			
		loop(i,N){
			cin >> V[i];
			loop(j,i)
				if(abs(V[i] - V[j]) <= K) join(i,j);
		}	
		cout << "Case #" << t + 1 << ": " << ans << "\n";
		cout << flush;	
	}
	return 0;
}

