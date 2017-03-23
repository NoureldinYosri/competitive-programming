#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
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

const double PI = acos(-1),S2 = sqrt(2);
set<pi> P;
set<pair<pi,pair<pi,pi> > > S;
int A[30],n;

bool visited(int x,int y){
	bool c = P.find(mp(x,y)) != P.end();
	if(!c) P.insert({x,y});
	return c;
}

bool visited(int x,int y,int dx,int dy,int p,int r){
	pair<pi,pair<pi,pi> > tmp = {{x,y},{{dx,dy},{p,r}}};
	bool c = S.find(tmp) != S.end();
	if(!c) S.insert(tmp);
	return c;
}

void rotate(int dx,int dy,int & ux,int & uy,int c){
	double t = atan2(dy,dx);
	t += c ? PI/4 : -PI/4;
	ux = round(cos(t) * S2);
	uy = round(sin(t) * S2);
}

int dfs(int x,int y,int dx,int dy,int p,int r){
	if(p == n || visited(x,y,dx,dy,p,r)) return 0;
	if(r == A[p]) {
		int ux,uy,vx,vy;
		rotate(dx,dy,ux,uy,1);
		rotate(dx,dy,vx,vy,0);
		return !visited(x,y) + dfs(x + ux,y + uy,ux,uy,p+1,1) + dfs(x + vx,y + vy,vx,vy,p+1,1);
	}
	else return !visited(x,y) + dfs(x + dx,y + dy,dx,dy,p,r+1);	
}



int main(){
	cin >> n;
	loop(i,n) cin >> A[i];
	cout << dfs(0,0,0,1,0,1) << endl;
	
	return 0;
}
