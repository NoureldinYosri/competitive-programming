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
#define vi deque<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
using namespace std;

int A[500 * 500];
map<int,int> M;

vector<int> V;

int valid(int a){
	bool c = 1;
	for(int v : V)
		if(M.count(__gcd(v,a)))
			M[__gcd(v,a)] -= 2;
		else
			c = 0;
	M[a]--;
	for(int v : V)
		if(M.count(__gcd(v,a)))
			c &= M[__gcd(v,a)] >= 0;
		else
			c = 0;
	for(int v : V)
		if(M.count(__gcd(v,a)))
			M[__gcd(v,a)] += 2;
		else
			c = 0;
	M[a]++;
	return c;
}

int main(){
	int n;
	scanf("%d",&n);
	loop(i,n*n) {
		scanf("%d",A + i);
		if(M.find(A[i]) == M.end()) M[A[i]] = 0;
		++M[A[i]];
	}
	loop(i,n){
		//for(auto p : M) cout << "(" << p.first << " ," << p.second << ") ";
		//cout << endl;
			
		pair<const int,int> *u = &(*M.begin());
		for(auto p = M.begin();p != M.end();p++)
			if(p->second == 1) u = &(*p);
			else if(p->second && u->second != 1){
				u = &(*p);
			}
		u->second--;
		for(int v : V) M[__gcd(u->first,v)] -= 2;
		V.pb(u->first);
		printf("%s%d",i ? " " : "",u->first);
	}
	puts("");
	return 0;
}
