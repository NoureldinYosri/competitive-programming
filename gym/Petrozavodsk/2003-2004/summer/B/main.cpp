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

char G[40][40];
int name[40][40];
int n;
int mark[400];
int P[400];
int X[400],Y[400];
int OX[400],OY[400];
int aux[400];
int R[400];
int DX[1600],DY[1600];

int main(){
	freopen("divide.in","r",stdin);
	freopen("divide.out","w",stdout);
	cin >> n; int m = 0;
	loop(i,n){
		cin >> G[i];
		loop(j,n) if(G[i][j] == '1') {
			P[m] = i*n + j;
			X[m] = OX[m] = i;
			Y[m] = OY[m] = j;
			m++;		
			name[i][j] = m;
		}
	}	
	if(m & 1) {
		puts("NO");
		return 0;
	}
	int q = 0;
	loop(cx,2*n) loop(cy,2*n) if((cx+cy)%2 == 0) {
		DX[q] = cx;
		DY[q] = cy;
		q++;
	}

	loop(j,q) {
		int cx = DX[j],cy = DY[j];

		loop(rot,4) {		
			int mxX = 0,mxY = 0;
			loop(i,m){
				int t = -Y[i] + (cx + cy)/2;	
				Y[i] = X[i] + (cy - cx)/2;
				X[i] = t;	
				mxX = max(mxX,X[i]); mxY = max(mxY,Y[i]);
			}
			
			loop(dx,20) {
				int z = 0;
				loop(i,m) z += X[i] + dx >= n;
				if(z > m/2) break;
			loop(dy,20){
				int cm = m,ctr = 0,ctr2 = 0;
				memset(mark,0,sizeof mark);
				loop(i,m){
					if(mark[i]) continue;
					mark[i] = 1;
					int x = X[i] + dx,y = Y[i] + dy;
					if(x < 0 || x >= n || y < 0 || y >= n || !name[x][y]) {
						ctr++;
						ctr2 += x >= n || y >= n;
						if(X[i] < 0 || X[i] >= n || Y[i] < 0 || Y[i] >= n) break;
						mark[i] = 3;
					}
					else{
						int other = name[x][y] - 1;
						if(mark[other] == 3) mark[other] = 2,ctr--;
						else if(mark[other] == 0) mark[other] = 2;
						else {
							ctr++;
							mark[i] = 3;
						} 
					}
				}
				if(!ctr){
					puts("YES");
					loop(i,m) if(mark[i] == 2) G[OX[i]][OY[i]] = '0';
					loop(i,n) puts(G[i]);
					return 0;
				}
				if(ctr2 > m/2) break;
			}}
		}
		
	}
	puts("NO");
	return 0;
}
