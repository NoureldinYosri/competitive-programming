#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

char s[50];
vector<string> V;
vi P,M;
vi PP,MM;

int main(){
	int n,L,minus = 0,plus = 0;
	P.pb(0);
	PP.pb(1);
	while(scanf("%s",s) == 1){
		if(s[0] == '+') minus++,P.pb(V.size()),PP.pb(1);
		if(s[0] == '-') plus++,M.pb(V.size()),MM.pb(1);
		if(isdigit(s[0])) sscanf(s,"%d",&n);
		else V.pb(string(s));
	}
	int S = sz(P) - sz(M);
	cerr << S << endl;
	loop(i,sz(P)){
		while(S < n && PP[i] < n) PP[i]++,S++;
	}
	loop(i,sz(M)){
		while(S > n && MM[i] < n) MM[i]++,S--;
	}
	cerr << S << endl;
	if(S == n){
		puts("Possible");
		int i = 0,j = 0; int pre = 0;
		for(auto v : V){
			if(v[0] == '?'){
				if(pre == 0) {
					printf("%d ",PP[i ++]);
				}
				else {
					printf("%d ",MM[j++]);
				}	
			}
			else {
				printf("%s ",v.c_str());
				if(v[0] == '+') pre = 0;
				if(v[0] == '-') pre = 1;			
			}
			
		}
		printf("%d\n",n);
	}
	else puts("Impossible"); 
	return 0;
}
