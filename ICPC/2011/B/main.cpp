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

struct point{
	int x,y;
	friend ostream& operator << (ostream& st,const point & p) {
		st << "(" << p.x << ", " << p.y << ")";
		return st;
	}
};

string int2str[] = {"no solution","equivalent solutions","inconsistent solutions"};
point I[3],R[3];

bool read(){
	bool are_zeros = 1;
	loop(i,3) scanf("%d %d",&I[i].x,&I[i].y);
	loop(i,3) are_zeros &= I[i].x == 0 && I[i].y == 0;
	if(are_zeros) return 0;
	loop(i,3) scanf("%d %d",&R[i].x,&R[i].y);
	return !are_zeros;
}

int do_round(double x) {
	return floor(x + 0.5);
}

vector<point> do_rotate(int x,int y) {
	double theta = atan2(y,x);
	auto w = polar(1.0,theta);
	vector<point> P;
	loop(i,3) {
		complex<double> p(I[i].x,I[i].y);
		p = p*w;
		int ix = round(real(p));
		int iy = round(imag(p));
		P.push_back(point({ix,iy}));
	}
 	return P;
}

int findf(int a,int b,int c,int d,int e,int f) {
	int X[] = {a,b,c};
	int Y[] = {d,e,f};

	loop(i,3) {
		int j = (i + 1)%3;
		int a = X[i] - X[j];
		int b = Y[i] - Y[j];
		if(b && a && b%a==0) return b/a;
	}

	return 1;
}

int valid(vector<point> P,vector<point> O) {
//	print(P,point);
//	print(O,point);
	int fx0 = findf(P[0].x,P[1].x,P[2].x,O[0].x,O[1].x,O[2].x);
	int fy0 = findf(P[0].y,P[1].y,P[2].y,O[0].y,O[1].y,O[2].y);
	//	cerr << fx << " " << fy << endl;
	int ret = 0;
	for(int i = -10;i <= 10;i++)
		for(int j = -10;j <= 10;j++){
		bool y = 1;
		int fx = fx0  + i;
		int fy = fy0  + j;
		if(!fx || !fy) continue;
		int dx = O[0].x - fx*P[0].x;
		int dy = O[0].y - fy*P[0].y;
		loop(i,3) {
			if(fx*P[i].x + dx != O[i].x) y = 0;
			if(fy*P[i].y + dy != O[i].y) y = 0;
		}
		ret += y;
	}
//	if(y){
//		cerr << point({fx,fy}) << " " << point({dx,dy}) << endl;
//		print(P,point);
//		print(O,point);
//	}
	return ret;
}

int work(int x,int y) {
	vector<point> P = do_rotate(x,y);
	vi ord;
	loop(i,3) ord.push_back(i);
	int ret = 0;
	do{
		vector<point> O;
		loop(i,3) O.push_back(R[ord[i]]);
		ret += valid(P,O);
	}while(next_permutation(all(ord)));
//	if(ret)
//		cerr << x << " " << y << " " << ret << endl;
	return ret;
}

int solve(){
	int ctr = 0;
	for(int y = -9;y <= 10;y++)
		ctr += work(-10,y);
	for(int x = -9;x <= 10;x++)
		ctr += work(x,10);
	return ctr;
}


int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	for(int cn = 1;read();cn++){
		int res = solve();
		string out = int2str[min(res,2)];
		printf("Case %d: %s\n",cn,out.c_str());
	}
	return 0;
}
