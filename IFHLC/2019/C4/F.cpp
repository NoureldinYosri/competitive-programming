#ifdef ACTIVE
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

const int MAX = 1 << 10;
using point = complex<double>;
using poly = point[MAX];

int G[2][MAX][MAX];
int ctr = 0;

struct grid{
	int height,width;
	int id;
	friend istream & operator  >> (istream & is,grid & g) {
		is >> g.width >> g.height;
		g.id = ctr++;
		loop(r,g.height) loop(c,g.width) cin >> G[g.id][r][c];
		return is;
	}
	void flip(){
		for(int r = 0;r < height;r++)
			for(int c = 0;2*c < width;c++)
				swap(G[id][r][c],G[id][r][width-1-c]);
		for(int c = 0;c < width;c++)
			for(int r = 0;2*r < height;r++)
				swap(G[id][r][c],G[id][height-1-r][c]);
	}
	void getRow(int r,int inv,poly ret) {
		loop(i,MAX) ret[i] = 0;
		loop(c,width) ret[c] = G[id][r][c] ^ inv;
	}
};
vp ans;


void fft(poly & f,int n,bool inv) {
	static poly W[2][10];
	static bool ready = 0;
	if(!ready){
		for(int sgn = 0;sgn < 2;sgn++){
			loop(k,10) {
				int m = 1 << k;
				double theta = PI/m * (2*sgn - 1);
				for(int i = 0;i < m;i++)
					W[sgn][k][i] = polar(1.0,i*theta);
			}
		}
		ready = 1;
	}
	for(int i = 1,j = 0;i+1 < n;i++) {
		for(int k = n >> 1; !(k & (j ^= k));k >>= 1);
		if(i < j) swap(f[i],f[j]);
	}
	for(int m = 1,k = 0;2*m <= n;m <<= 1,k++) {
		const poly & w = W[inv][k];
		for(int s = 0;s < n;s += 2*m) {
			for(int i = 0;i < m;i++) {
				point a = f[s + i],b = f[s + i + m];
				f[s + i] = a + w[i]*b;
				f[s + i + m] = a - w[i]*b;
			}
		}
	}
	if(inv){
		loop(i,n) f[i] /= n;
	}
}

void fft2d(poly G[MAX],bool inv) {
	static poly f;
	loop(i,MAX) fft(G[i],MAX,inv);
	loop(c,MAX) {
		loop(r,MAX) f[r] = G[r][c];
		fft(f,MAX,inv);
		loop(r,MAX) G[r][c] = f[r];
	}
}

poly txt[2][MAX],patt[2][MAX];

int sum[MAX][MAX];

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	grid A,B;
	cin >> A >> B;
	A.flip();
	loop(r,A.height) loop(i,2) A.getRow(r,i,patt[i][r]);
	loop(r,B.height) loop(i,2) B.getRow(r,i,txt[i][r]);
	loop(i,2) {
		fft2d(patt[i],0);
		fft2d(txt[i],0);
	}
	loop(k,2) loop(i,MAX) loop(j,MAX) txt[k][i][j] *= patt[k][i][j];
	loop(i,2) fft2d(txt[i],1);
	loop(k,2) loop(i,MAX) loop(j,MAX) {
		int v = round(txt[k][i][j].real());
		sum[i][j] += v;
	}
//	loop(r,10) {
//		prArr(sum[r],10,int);
//	}
	int best = -1;
	int s1 = A.height-1;
	int s2 = A.width-1;
	for(int r = 0;r <= B.height - A.height;r++)
		for(int c = 0;c <= B.width - A.width;c++) {
			int v = sum[s1 + r][s2+c];
			if(v > best){
				ans.clear();
				best = v;
			}
			if(v == best) ans.emplace_back(c,r);
		}
	sort(all(ans));
	for(auto p : ans) printf("%d %d\n",p.first,p.second);
	return 0;
}
#endif
