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

bool solve(string u,string v){
	int i = 0,j = 0;
	while(i < len(u)){
		while(i < len(u) && j < len(v) && u[i] == v[j]) j++,i++;
		i++;
	}
	return j == len(v);
}

int main(){
	int T; string u,v;
	cin >> T;
	while(T--){
		cin >> u >> v;
		puts(solve(u,v) ? "YES" : "NO");
	}
	return 0;
}
