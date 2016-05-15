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

int ctr[10][10];
vi Q[10];
int Z[10],k;

bool valid(int i){
	loop(j,k){
		if(Z[j] > 0) {
			if(ctr[i][Z[j]] == 0) return 0;
		//	else cout << Z[j] << " exists in " << i << endl;
		}
		else {
			if(ctr[i][-Z[j]] == 1) return 0;
		//	else cout << -Z[j] << " does not exist in " << i << endl;
		}
	}	
	return 1;
}

int main(){
	int n,m,a;
	pre();
	cin >> n >> m;
	loop(i,n){
		cin >> k;
		loop(j,k){		
			cin >> a;
			ctr[i][a] = 1;
			Q[i].pb(a);
		}
	}	
	loop(i,m){
		cin >> k;
		loop(j,k) {
			cin >> Z[j];
		//	cout << "(" << j << " ," << Z[j] << ")" << endl;
		}
		vi R;
		loop(j,n) if(valid(j)) R.pb(j);
		cout << sz(R) << endl;
		loop(j,sz(R)){
			int r = R[j];
			cout << sz(Q[r]);
			loop(l,sz(Q[r])){
				cout << " ";
				cout << Q[r][l];
			}
			cout << endl;
		}	
	}	
	
	return 0;
}

