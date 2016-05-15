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

int T,n,m;
map<string,int> M;
int dp[20][1 << 18];
int msk[18],W[18];
char line[1000];
queue<string> Q;

void read(){
	fgets(line,1000,stdin);
	char *token = strtok(line," \n");
	while(token){
		Q.push(string(token));
		token = strtok(NULL," \n");
	}
}

int read_next_int(){
	while(Q.empty()) read();
	int a ;
	sscanf(Q.front().c_str(),"%d",&a);
	Q.pop();
	return a;
}

string read_next_string(){
	while(Q.empty()) read();
	string s = Q.front(); Q.pop();
	return s;
}
string read_next_comp_string(){
	string ret = "";
	while(Q.empty()) read();
	while(!Q.empty() && !isdigit(Q.front()[0]) && Q.front()[0] != '-'){
		if(!ret.empty()) ret += " ";
		ret += Q.front();
		Q.pop();
	}
	if(!Q.empty() && Q.front()[0] == '-') Q.pop(); 
	return ret;
}


int solve(int d,int mask){
	if(d == n + 1) return 0;
	if(dp[d][mask] != -1) return dp[d][mask];
	loop(i,n){
		int u = mask & (1 << i),v = msk[i] | mask;
		if(!u && v == mask) dp[d][mask] = max(dp[d][mask],solve(d + 1,mask | (1 << i)) + W[i]*d);
	}
	return dp[d][mask];
}

int main(){
	T = read_next_int();
	while(T--){
		n = read_next_int();
		m = read_next_int();
		loop(i,n) msk[i] = 0;
		loop(i,n + 1) loop(j,1 << n) dp[i][j] = -1;
		M.clear();
		loop(i,n) {
			string u = read_next_comp_string();
			//cerr << u << endl;
			W[i] = read_next_int();
			M[u] = i;	
		}	
		while(m--){
			string u = read_next_comp_string();
			string v = read_next_comp_string();
			msk[M[v]] |= 1 << M[u];
		}
		printf("%d\n",solve(1,0));
	}
	return 0;
}
