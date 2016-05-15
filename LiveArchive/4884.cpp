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

void gen(int p,int taken,int & ctr,vector<string> & IN,vi & fro,vi & to){
	to.resize(10);
	set<vi> S;
	loop(i,10) to[i] = i;
	do{
		int a,b = 0,c;
		loop(i,sz(IN)){
			if(to[lower_bound(all(fro),IN[i][len(IN[i]) - 1]) - fro.begin()] == 0) continue;
			a = 0;
			for(char ch : IN[i]) a = a * 10 + to[lower_bound(all(fro),ch) - fro.begin()];
			if(i == sz(IN) - 1) c = a;
			else b += a;
		}
		if(b == c){
			vi tt;
			loop(i,sz(fro)) tt.pb(to[i]);
			S.insert(tt);
		}	
	}while(next_permutation(all(to)));
	cout << "here" << endl;
	for(auto p = S.begin(); p != S.end();p++) {auto & s = *p;print(s,int);}	
	ctr = sz(S);
}

int main(){
	pre();
	int T; vi fro,to;
	vector<string> IN;
	while(cin >> T){		
		cout << "here" << endl;
		fro.clear(); IN.resize(T);
		loop(i,T) {
			cin >> IN[i];
			reverse(all(IN[i]));
			for(int c : IN[i]) fro.pb(c);
		}
		cout << "here2" << endl;	
		sort(all(fro));
		fro.resize(unique(all(fro)) - fro.begin());
		cout << sz(fro) << endl;		
		if(sz(fro) > 10) cout << "0\n";
		else{
			to.resize(sz(fro));
			int ctr = 0;
			gen(0,0,ctr,IN,fro,to);
			cout << ctr << "\n";	
		}
	}
	return 0;
}
