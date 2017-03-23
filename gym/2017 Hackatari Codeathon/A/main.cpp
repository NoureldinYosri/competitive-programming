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

int vis[3][3][3],cnt;
int dx[] = { -1 ,0 ,0 ,0 ,0 ,1 };
int dy[] = { 0 ,-1 ,0 ,0 ,1 ,0 };
int dz[] = { 0 ,0 ,-1 ,1 ,0 ,0 };
string path;

#define inRange(x) (0 <= x && x < 3)



bool bt(int x,int y,int z,int l = -1,int idx = 0){
	if(cnt == 26) return 1;
	cnt++;
	vis[x][y][z] = 1;

	loop(i,6){
		
		if((!idx || idx == 26) || ((path[idx] == 'I' && l == i) || (path[idx] == 'L' && l != i))){
			int nx = x + dx[i],ny = y + dy[i],nz = z + dz[i];
			if(inRange(nx) && inRange(ny) && inRange(nz) && !vis[nx][ny][nz]){
				if(bt(nx,ny,nz,i,idx+1)) return 1;
			}
		}
	}
	cnt--;
	vis[x][y][z] = 0;
	return 0;
}


int main(){
	cin >> path;
	bool ans = bt(0,0,0) || bt(0,1,0) || bt(1,1,0);
	puts(ans ? "YES" : "NO");
	return 0;
}
