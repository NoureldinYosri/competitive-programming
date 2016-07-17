#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define vi vector<int>
#define vl vector<long>
#define vd vector<double>
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
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

char line[1 << 10];
char tmp[1 << 10];
ll eval2(const char *p){
	strcpy(tmp,p);
	char deli [] = " *x",*token = strtok(tmp,deli);	
	ll v = 1,t;
	for(;token;token = strtok(0,deli)){
		sscanf(token,"%lld",&t);
		v *= t;
	}	
	return v;
}

pair<ll,ll> eval(char *p){
	char deli [] = "+\n",*token = strtok(p,deli);	
	ll x = 0,y = 0;
	vector<string> X,Y;	
	for(;token;token = strtok(0,deli)){
		int type = 0;
		for(auto *c = token;*c;c++) type |= *c == 'x';		
		if(type) X.pb(string(token));
		else Y.pb(string(token));
	}
	for(auto s : X) x += eval2(s.c_str());
	for(auto s : Y) y += eval2(s.c_str());
	return mp(x,y);
}

int main(){
	fgets(line,1 << 10,stdin);
	char *p = line;
	for(;*p && *p != '=';p++);
	if(!*p){
		puts("No Solution");
		return 0;
	}	
	*p = 0;
	pl A = eval(line),B = eval(p + 1);
	prp(A); cerr << endl; prp(B);
	if(A.xx == B.xx){
		puts("No Solution");
		return 0;
	}	
	A.xx -= B.xx;
	A.yy = B.yy - A.yy;
	ll g = __gcd(A.xx,A.yy);
	A.xx /= g;
	A.yy /= g;
	if(A.xx < 0) A.yy *= -1,A.xx *= -1;
	printf("%lld / %lld",A.yy,A.xx);
	return 0;
}
