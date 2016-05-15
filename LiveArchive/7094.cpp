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

int state[10001];

bool is_prime(int n){
	for(int i = 2;i*i <= n;i++)
		if(n%i == 0)
			return 0;
	return n > 1;
}

int is_happy(int n){
	if(state[n] >= 0) return state[n];
	if(state[n] == -2) return 0;
	state[n] = -2;
	int s = 0,z = n;
	while(z) s += (z%10) * (z%10),z /= 10;
	return state[n] = is_happy(s);
}

int main(){
	pre();
	fill(state,state + 10001,-1);
	state[1] = 1;
	int T,a,b;
	cin >> T;
	while(T--){
		cin >> a >> b;
		cout << a << " " << b << " " << ((is_prime(b) && is_happy(b)) ? "YES" : "NO") << endl;
	}
	return 0;
}

