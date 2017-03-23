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

int dx [] = {1,0,-1,0},dy [] = {0,1,0,-1};

bool onsegment(int x,int y,int ox,int oy,int tx,int ty){
	if(y == oy){
		if(y != ty) return 0;
		return min(x,ox) <= tx && tx <= max(x,ox);
	}
	else{
		if(x != tx) return 0;
		return min(y,oy) <= ty && ty <= max(y,oy);
	}
}

int main(){
	int tx,ty,x = 0,y = 0,dir = 0,l = 1; cin >> tx >> ty;
	if(tx == 0 && ty == 0) puts("0");
	else{
		int ans = 0;
		for(;;l++){
			int nx = x + dx[dir]*l,ny = y + dy[dir]*l;
			if(onsegment(x,y,nx,ny,tx,ty)) break;
			ans++;
			x = nx,y = ny; dir = (dir == 3) ? 0 : (dir + 1);
			nx = x + dx[dir]*l,ny = y + dy[dir]*l;
			if(onsegment(x,y,nx,ny,tx,ty)) break;
			ans++;
			x = nx,y = ny; dir = (dir == 3) ? 0 : (dir + 1);
		}
		cout << ans << endl;
	}
	
	
	return 0;
}
