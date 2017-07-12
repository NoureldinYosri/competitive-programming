#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

long long G[250][250];
long long T[250*250 << 4];

bool disjoint(int ix,int iy,int sx,int sy){
	return (iy < sx) || (sy < ix);
}

void init(int node,int sx,int sy,int ex,int ey){
	if(sx == sy && ex == ey){
		T[node] = G[sx][ex];
		return ;
	}
	if(sx == sy){
		int m = (ex + ey) >> 1;
		init((node << 2) - 2,sx,sy,ex,m);
		init((node << 2) - 1,sx,sy,m + 1,ey);
		T[node] = 0;
		loop(i,2) T[node] = max(T[node],T[(node << 2) - i - 1]);
	}
	else if(ex == ey){
		int m = (sx + sy) >> 1;
		init((node << 2) + 0,sx,m,ex,ey);
		init((node << 2) + 1,m + 1,sy,ex,ey);
		T[node] = 0;
		loop(i,2) T[node] = max(T[node],T[(node << 2) + i]);
	}
	else{
		int sm = (sx + sy) >> 1,em = (ex + ey) >> 1;
		init((node << 2) - 2,sx,sm,ex,em);
		init((node << 2) - 1,sm + 1,sy,ex,em);
		init((node << 2) + 0,sx,sm,em + 1,ey);
		init((node << 2) + 1,sm + 1,sy,em + 1,ey);
		T[node] = 0;
		loop(i,4) T[node] = max(T[node],T[(node << 2) + i - 2]);
	}
}

long long query(int node,int sx,int sy,int ex, int ey,int ix,int iy,int jx,int jy){
	if(ix <= sx  && sy <= iy && jx <= ex && ey <= jy) return T[node];
	if(disjoint(ix,iy,sx,sy) || disjoint(jx,jy,ex,ey)) return 0;
	if(sx == sy){
		int m = (ex + ey) >> 1;
		return max(query((node << 2) - 2,sx,sy,ex,m,ix,iy,jx,jy),query((node << 2) - 1,sx,sy,m + 1,ey,ix,iy,jx,jy));
	}
	else if(ex == ey){
		int m = (sx + sy) >> 1;
		return max(query((node << 2) + 0,sx,m,ex,ey,ix,iy,jx,jy),query((node << 2) + 1,m + 1,sy,ex,ey,ix,iy,jx,jy));
	}
	else{
		int sm = (sx + sy) >> 1,em = (ex + ey) >> 1,A[4],ans = 0;
		A[0] = query((node << 2) - 2,sx,sm,ex,em,ix,iy,jx,jy);
		A[1] = query((node << 2) - 1,sm + 1,sy,ex,em,ix,iy,jx,jy);
		A[2] = query((node << 2) + 0,sx,sm,em + 1,ey,ix,iy,jx,jy);
		A[3] = query((node << 2) + 1,sm + 1,sy,em + 1,ey,ix,iy,jx,jy);
		loop(i,4) ans = max(ans,A[i]);
		return ans;
	}
}

int main(){
	
}

