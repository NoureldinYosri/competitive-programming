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

const int MAXT = 1000*1000*1000;

int n;
int X[500],R[500],B[500];
bool bad[101][101][9900];
int lcm[101][101];
int inv[101][101];

void bf(){
	static int ctr[500];
	memset(ctr,0,sizeof ctr);
	int N = MAXT/n;
	for(int t = 0;t < N;t++){
		for(int i = 0;i < n;i++){
			int ct = t + X[i];
			int ti = ct%(R[i] + B[i]);
			if(ti < R[i]) {
				ctr[i]++;
				break;
			}
		}
	}
	double fin = 1;
	loop(i,n) {
		double p = ctr[i]*1.0/N;
		p = max(p,0.0);
		if(!i) printf("%.7f ",R[i]/(R[0] + B[0]+0.0));
		printf("%.7f\n",p);
		fin -= p;
	}
	fin = max(fin,0.0);
	printf("%.7f\n",fin);
}

list<int> G[101][101][9900];
list<int> iG[101][101][9900];

int ext_gcd(int a,int b,int & x,int & y) {
	if(b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int g = ext_gcd(b,a%b,x,y);
	// b*x - (a%b)*y = g
	// b*x - [a - (a/b)*b]*y = g
	// -a*y + (x + y*(a/b))*b = g
	int t = -y;
	y = x + y*(a/b);
	x = t;
	assert(x*a - b*y == g);
	return g;
}

void init(){
	for(int a = 1;a <= 100;a++)
		for(int b = 1;b <= 100;b++)
			lcm[a][b] = a*(b/__gcd(a,b));
	for(int m1 = 1;m1 <= 100;m1++){
		for(int m2 = 1;m2 <= 100;m2++)
			for(int i = 0;i < m2;i++) {
				int v = (i*m1)%m2;
				if(v != 1) continue;
				assert(!inv[m1][m2]);
				inv[m1][m2] = i;
			}
	}
	for(int world = 1;world <= 100;world++)
		for(int blocker = 1;blocker <= 100;blocker++){
			int x,y;
			int g = ext_gcd(world,blocker,x,y);
			int l = lcm[world][blocker];
			for(int i = 0;i < world;i++)
				for(int j = 0;j < blocker;j++) {
					int diff = j-i;
					int v = x*diff/g;
					if(diff%g == 0) {
						v = (v%l + l)%l;
						G[world][blocker][i].push_back(v);
						iG[world][blocker][j].push_back(v);
					}
				}
		}

}

double get(int me){
	int world = R[me] + B[me];
	double ret = 0;
	for(int t = 0;t < R[me];t++) {
		int carTime = (t - X[me]);
		carTime = (carTime%world + world)%world;
		double tmp = 0;
		for(int blocker = 1;blocker <= 100;blocker++) {
			for(int v : G[world][blocker][carTime])
				tmp += bad[world][blocker][v];
		}
		int norm = 100*101/2;
		tmp = 1 - tmp/norm;
		ret += tmp;
	}
	ret /= world;
	return ret;
}


void update(int me) {
	int r = R[me],b = B[me],blocker = r + b;
	for(int world = 1;world <= 100;world++) {
		if(!inv[blocker][world]) continue;
		for(int t = 0;t < r;t++) {
			int carTime = (t - X[me]);
			carTime = (carTime%blocker + blocker)%blocker;
			for(int v : G[world][blocker][carTime]) {
				bad[world][blocker][v] = 1;
			}
		}
	}
}

void solve(){
	double fin = 1.0;
	loop(i,n){
//		cerr << "compute" << endl;
		double p = get(i);
		p = max(p,0.0);
		printf("%.9f\n",p);
		fin -= p;
//		cerr << "update" << endl;
		update(i);
	}
	fin = max(fin,0.0);
	printf("%.9f\n",fin);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	init();
	scanf("%d",&n);
	loop(i,n) scanf("%d %d %d",X + i,R + i,B + i);
	solve();
	return 0;
}
