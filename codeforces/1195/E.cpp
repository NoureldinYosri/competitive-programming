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

const int MAX = 3 << 10;


struct monoQueue{
	deque<pi> dq;
	queue<pi> q;
	void insert(int i,int x){
		pi cur(x,i);
		q.push(cur);
		while(!dq.empty() && dq.back().first >= x)
			dq.pop_back();
		dq.push_back(cur);
	}
	int getMin(){
		assert(!dq.empty());
		return dq.front().first;
	}
	void pop() {
		assert(!q.empty());
		pi cur = q.front(); q.pop();
		if(dq.front() == cur) dq.pop_front();
	}
	void clear(){
		dq.clear();
		while(!q.empty()) q.pop();
	}
};


int add(int a,int b,int mod){
	a += b;
	if(a >= mod) a -= mod;
	return a;
}
int mul(int a,int b,int mod) {
	return (a*(ll)b)%mod;
}


monoQueue col[MAX];
int G[MAX][MAX],m,n,H,W;


void gen(){
	int g0,x,y,z;
	scanf("%d %d %d %d",&g0,&x,&y,&z);
	int g = g0;
	loop(i,m) loop(j,n) {
		G[i][j] = g;
		g = add(mul(g,x,z),y,z);
	}
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %d %d %d",&m,&n,&H,&W);
	gen();
	loop(c,n) {
		loop(i,H) col[c].insert(i,G[i][c]);
	}
	monoQueue mq;
	ll ans = 0;
	for(int r = 0;r <= m-H;r++){
		mq.clear();
		loop(c,W) mq.insert(c,col[c].getMin());
		for(int c = 0;c <= n-W;c++) {
//			cerr << mq.getMin() << " ";
			ans += mq.getMin();
			mq.pop();
			if(c+W < n)
				mq.insert(c+W,col[c+W].getMin());
		}
//		cerr << endl;
		for(int c = 0;c < n;c++) {
			col[c].pop();
			if(r+H < m) col[c].insert(r+H,G[r+H][c]);
		}
	}
	cout << ans << endl;
	return 0;
}
#endif
