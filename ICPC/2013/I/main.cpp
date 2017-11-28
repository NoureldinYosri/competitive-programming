#pragma GCC optimize ("O3")
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
const double PI = acos(-1);
using namespace std;

int A[500][500],m,n,a,b;
int max_depth = 0;
int aux[500];
int L[500],R[500];

bool valid(int x,int y) {
	if(x <= a && y <= b) return 1;
	if(x <= b && y <= a) return 1;
	return 0;
}

ll brute_force() {
	ll ans = 0;
	for(int r1 = 0;r1 < m;r1++)
		for(int r2 = r1;r2 < m;r2++) {
			for(int c = 0;c < n;c++) {
				aux[c] = 0;
				range(r,r1,r2)
					aux[c] = max(aux[c],A[r][c]);
			}
			for(int c1 = 0;c1 < n;c1++){
				int mx = 0;
				for(int c2 = c1;c2 < n;c2++){
					if(!valid(c2-c1+1,r2-r1+1)) break;
					mx = max(mx,aux[c2]);
					int x = c2-c1+1,y=r2-r1+1;
					ll H = m*n*(max_depth - mx + 0LL),d = m*n - x*y;
					ll h = H/d;
					if(H%d == 0) h--;
					h = max(h,0LL);
					ans = max(ans,h*x*y);
				}
			}
		}
	return ans;
}

ll solve(){
	vector<int> ST;
	ll ans = 0;
	for(int r1 = 0;r1 < m;r1++){
		memset(aux,0,sizeof aux);
		for(int r2 = r1;r2 < m;r2++) {
			int dr = r2 - r1 + 1,limit = 0;
			if(dr > b) break;
			if(dr > a) limit = a;
			else limit = b;
			for(int c = 0;c < n;c++)
				aux[c] = max(aux[c],A[r2][c]);
			for(int c = 0;c < n;c++) {
				while(!ST.empty() && aux[ST.back()] <= aux[c]) ST.pop_back();
				if(ST.empty()) L[c] = -1;
				else L[c] = ST.back();
				ST.push_back(c);
			}
			ST.clear();
			for(int c = n-1;c >= 0;c--) {
				while(!ST.empty() && aux[ST.back()] <= aux[c]) ST.pop_back();
				if(ST.empty()) R[c] = n;
				else R[c] = ST.back();
				ST.push_back(c);
			}
			ST.clear();
			for(int c = 0;c < n;c++) {
				int l = R[c] - L[c] - 1;
				l = min(l,limit);
				ll H = m*n*(max_depth - aux[c] + 0LL),d = m*n - dr*l;
				ll h = H/d;
				if(H%d == 0) h--;
				h = max(h,0LL);
				ans = max(ans,h*dr*l);
			}

		}
	}
	return ans;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif

	while(scanf("%d %d %d %d",&a,&b,&m,&n) == 4){
		if(a > b) swap(a,b);
		loop(i,m) loop(j,n) {
			scanf("%d",&A[i][j]);
			max_depth = max(max_depth,A[i][j]);
		}
		loop(i,m) loop(j,n) A[i][j] = max_depth - A[i][j];

	//	cout << brute_force() << endl;
		printf("%lld\n",solve());
	}
	return 0;
}
