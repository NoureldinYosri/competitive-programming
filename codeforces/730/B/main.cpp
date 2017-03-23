#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
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

void write(char c,int x,int y){
	printf("%c %d %d\n",c,x,y);
	fflush(stdout);
}

int read(){
	char c;
	scanf(" %c",&c);
	return (c == '>') - (c == '<');
}

void get(int & x,int & y,int s,int e){
	write('?',s,e);
	int t = read();
	if(t == -1) x = s,y = e;
	else x = e,y = s;
}

void solve(int s,int n,int & x,int & y){
	if(n == 1) x = y = s;
	else if(n == 2) get(x,y,s,s+1); 
	else if(n == 3){
		get(x,y,s,s + 1);
		int t;		
		get(x,t,x,s + 2);
		get(t,y,y,s + 2);
	}
	else{
		int p2 = 1;
		while(p2*2 <= n) p2 <<= 1;
		int a,b;
		solve(s,n/2,x,y);
		solve(s+n/2,n/2,a,b);
		get(x,a,x,a);
		get(b,y,b,y);
		if(p2 == n) return;
		solve(s + p2,n - p2,a,b);
		get(x,a,x,a);
		get(b,y,b,y);
	}
}

int main(){
	int T,n; scanf("%d",&T);	
	while(T--){
		scanf("%d",&n);
		int x,y;		
		solve(1,n,x,y);
		write('!',x,y);
	}
	
	return 0;
}
