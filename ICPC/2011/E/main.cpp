#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vd vector<double>
#define vp vector<pair<int,int> >
#define ll long long
#define pi pair<int,int>
#define popcnt(x) __builtin_popcountll(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
using namespace std;

const int MAX = 7000+5;
int H,W,n,Q;
pi P[1 << 20];
int mx,x,y;
int offset[MAX][MAX];

bool read(){
	scanf("%d %d %d %d",&W,&H,&n,&Q);
	return !(W==0 && H==0 && n==0 && Q==0);
}


pair<pi,pi> squares[1 << 20];

bool inside(int x,int y) {
	return 1 <=x && x <= W && 1 <= y && y <= H;
}

vi add;

void solve(int r){
	r = min(r,2000);
	int dx [] = {0,r,0,-r};
	int dy [] = {r,0,-r,0};
	loop(i,n) {
		pi corners[4];
		loop(j,4) {
			corners[j].xx = P[i].xx + dx[j];
			corners[j].yy = P[i].yy + dy[j];
		}
		// rotate
		loop(j,4) {
			int x = corners[j].xx,y = corners[j].yy;
			corners[j].xx = x - y;
			corners[j].yy = x + y;
		}
		int minX = INT_MAX,minY = INT_MAX;
		int maxX = INT_MIN,maxY = INT_MIN;
		loop(j,4) {
			minX = min(minX,corners[j].xx);
			minY = min(minY,corners[j].yy);
			maxX = max(maxX,corners[j].xx);
			maxY = max(maxY,corners[j].yy);
		}
		assert(maxX - minX == maxY-minY);
		squares[i] = mp(mp(minX,maxX),mp(minY,maxY));
	}
	int minX = -H,minY = 0;
	int maxX = W,maxY = W+H;

	loop(i,n) {
		minX = min(minX,squares[i].xx.xx);
		minY = min(minY,squares[i].yy.xx);
		maxX = max(maxX,squares[i].xx.yy);
		maxY = max(maxY,squares[i].yy.yy);
	}
	loop(i,n){
		squares[i].xx.xx -= minX;
		squares[i].xx.yy -= minX;
		squares[i].yy.xx -= minY;
		squares[i].yy.yy -= minY;
	}
	int Rx = INT_MIN,Ry = INT_MIN;
	loop(i,n){
		int minX = squares[i].xx.xx,maxX = squares[i].xx.yy;
		int minY = squares[i].yy.xx,maxY = squares[i].yy.yy;
//		prp(mp(minX,maxX));
//		prp(mp(minY,maxY));
//		cerr << endl;
		offset[minX][minY] ++;
		offset[minX][maxY+1]--;
		offset[maxX+1][minY] --;
		offset[maxX+1][maxY+1]++;
		Rx = max(Rx,maxX+1);
		Ry = max(Ry,maxY+1);
	}
	int M = maxY - minY + 1,N = maxX - minX + 1;
	add.resize(M);
	loop(i,M) add[i] = 0;
	mx = 0;
	pi aux(INT_MAX,INT_MAX);
	loop(r,M) {
		for(int c = 0;c < N;c++)
			add[c] += offset[r][c];
		int dv = 0;
		loop(c,M) {
			dv += add[c];
			int tx = (r + minX) + (c + minY);
			int ty = -(r + minX) + (c + minY);
			if((tx&1) || (ty&1) || tx <= 0 || ty <= 0) continue;
			tx >>= 1,ty >>= 1;
			if(!inside(tx,ty)) continue;
			if(dv > mx) {
				mx = dv;
				aux = mp(INT_MAX,INT_MAX);
			}
			if(dv == mx) {
				pi tmp(ty,tx);
				aux = min(aux,tmp);
			}
		}
	}
	x = aux.yy,y = aux.xx;
	if(mx == 0) x = y = 1;
//	loop(i,min(M+1,MAX)) loop(j,min(N+1,MAX)) offset[i][j] = 0;
	loop(i,Rx+1) loop(j,Ry+1) offset[i][j] = 0;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int cn = 1;read();cn++) {
		loop(i,n) scanf("%d %d",&P[i].xx,&P[i].yy);
		printf("Case %d:\n",cn);
		loop(q,Q) {
			int r; scanf("%d",&r);
			solve(r);
			printf("%d (%d,%d)\n",mx,x,y);
		}
	}
	return 0;
}
