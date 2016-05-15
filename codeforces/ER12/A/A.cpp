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

vector<pi> AB,BA;

void simulate(int f,int T,vector<pi> & route){
	int t = 5*60;
	while(t < 24*60){
		route.pb(mp(t,t + T));
		t += f;
	}
}

int inter(int x,int y,int a,int b){
	if(x > a) swap(x,a),swap(y,b);
	return a < y;
}

int main(){
	int a,ta,b,tb,h,m,t;
	scanf("%d %d",&a,&ta); //simulate(a,ta,AB);
	scanf("%d %d",&b,&tb); simulate(b,tb,BA);
	scanf("%d:%d",&h,&m) ; t = h*60 + m; 		
	int ctr = 0;
	for(auto bus : BA) ctr += inter(t,t + ta,bus.xx,bus.yy); 
	cout << ctr << endl;
	return 0;
}
