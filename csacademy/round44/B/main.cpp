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

const int MAX = 300;
int A[300][300],m,n;
int cnt[1 << 20];
map<int,int> mnX,mnY,mxX,mxY;


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %d",&m,&n);
	assert(m <= 300 && n <= 300);
	set<int> S;
	loop(i,m) loop(j,n) {
		scanf("%d",&A[i][j]);
		cnt[A[i][j]]++;
		int val = A[i][j];
		if(mnX.find(A[i][j]) == mnX.end()){
			mnX[val] = MAX;
			mnY[val] = MAX;
			mxX[val] = 0;
			mxY[val] = 0;
		}
		S.insert(val);
		mnX[val] = min(mnX[val],i);
		mxX[val] = max(mxX[val],i);
		mnY[val] = min(mnY[val],j);
		mxY[val] = max(mxY[val],j);
	}
	for(int x : S){
		int r1 = mnX[x],r2 = mxX[x],c1 = mnY[x],c2 = mxY[x];
		//cerr << x << "\t" << r1 << " " << r2 << " " << c1 << " " << c2 << endl;
		if(r2 - r1 != c2 - c1) {
			puts("0");
			return 0;
		}
		int l = r2 - r1 + 1;
		if(l*l != cnt[x]) {
			puts("0");
			return 0;
		}
	}
	puts("1");
	return 0;
}
