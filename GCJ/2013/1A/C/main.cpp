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

const int MAX = 50388,D = 8;
int N,M,K,M2;
int cnts[MAX][D],m = 0;
int ctr[D],ord[MAX];
ll configProb[MAX],prod[10];
unordered_map<ll,int> SubSetProd[MAX];
int C[13][13];
double score[MAX];

void create(int r){
	static vi nums;
	nums.clear();
	assert(m < MAX);
	ctr[M2-1] = r;
	copy(ctr,ctr + M2,cnts[m]);
	configProb[m] = 1;
	int n = N;
	loop(i,M2){
		configProb[m] *= C[n][ctr[i]];
		n -= ctr[i];
		loop(j,ctr[i])
			nums.push_back(i+2);
	}
	SubSetProd[m].reserve(1 << N);
	loop(msk,1 << N) {
		ll p = 1;
		loop(i,N) if(msk&(1<<i)) p *= nums[i];
		SubSetProd[m][p]++;
	}
	m++;
	if(m%1000 == 0) cerr << m << endl;
}
void gen(int d,int r) {
	if(d == M2-1) return create(r);
	for(ctr[d] = 0;ctr[d] <= r;ctr[d]++)
		gen(d+1,r-ctr[d]);
}





int Q;


void compute_scores(){
	for(int i = 0;i < m;i++) {
		score[i] = log(configProb[i]);
		loop(k,Q) {
			int ctr = 0;
			ll p = prod[k];
			if(SubSetProd[i].count(p)) ctr = SubSetProd[i][p];
			if(ctr == 0) {
				score[i] = -1;
				break;
			}
			score[i] += log(ctr);
		}
	}
//	prArr(score,m,ll);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
	freopen("out.out","w",stdout);
#endif
	for(int n = 0;n <= 12;n++){
		C[n][0] = C[n][n] = 1;
		for(int k = 1;k < n;k++)
			C[n][k] = C[n-1][k] + C[n-1][k-1];
	}
	int T; scanf("%d",&T); // discard
	assert(T == 1);
	int R;
	scanf("%d %d %d %d",&R,&N,&M,&K);
	M2 = M-1;
	gen(0,N);
	cerr << "m = " << m << endl;
//	for(int i = 0;i < m;i++){
//		prArr(cnts[i],M2,int);
//	}
//	cerr << m << endl;
	loop(i,m) ord[i] = i;
	puts("Case #1:");
	for(int r = 1;r <= R;r++) {
		if((r-1)%100 == 0)
			cerr << "r = " << r  << "/" << R << endl;
		loop(i,K) scanf("%lld",prod+i);
		Q = K;

		compute_scores();
		int choice = 0;
		for(int i = 1;i < m;i++)
			if(score[i] > score[choice])
				choice = i;
		loop(i,D) {
			int d = i + 2;
			loop(j,cnts[choice][i])
				putchar(d + '0');
		}
		puts("");
	}
	return 0;
}
