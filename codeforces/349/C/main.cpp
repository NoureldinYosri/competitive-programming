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

char line[20000];
int done [20000][3],L;
set<string> S; 

inline bool can(int i,int l){
	if(i + l == L) return 1;
	if(L - i - l == 1) return 0;
	if(l == 3 && L - i - 1 == 2) return 1;
	bool c = 1;
	loop(j,l) c &= line[i + j] == line[i + j + l];
	return !c;
}

int solve(int i,int last = 2){
	if(i == L) return 2;
	if(i > L) return 1;
	if(done[i][last]) return done[i][last];
	done[i][last] = 1;
	if(solve(i + 2,0) == 2) {
		bool c = last != 0;
		if(last == 0 && can(i - 2,2)) c = 1;
		if(c){
			string s = "xx";
			s[0] = line[i];
			s[1] = line[i + 1];
			S.insert(s);
			done[i][last] = 2;
		}	
	}
	if(solve(i + 3,1) == 2){
		bool c = last != 1;
		if(last == 1 && can(i - 3,3)) c = 1;
		if(c){
			string s = "xxx";
			s[0] = line[i];
			s[1] = line[i + 1];
			s[2] = line[i + 2];
			S.insert(s);
			done[i][last] = 2;
		}
	}
	return done[i][last];
}

int main(){
	scanf("%s",line);
	L = strlen(line);	
	loop(i,L){	
		if(i > 4) solve(i);
	}
	printf("%lu\n",S.size());	
	for(auto s : S) printf("%s\n",s.c_str());
	return 0;
}
