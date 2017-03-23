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

const int MAX = 1001;
const int MAXN = 20*1000 + 1;
int k;
double P[2][MAX];
double p[MAXN];
int ans[MAX];
void init(){
	P[0][0] = 1;
	int one = 1,other = 0;
	for(int i = 1;i < MAXN;i++){
		P[one][0] = 0;
		range(j,1,k) P[one][j] = (P[other][j]*j)/k + P[other][j - 1]*(k - j + 1.0)/k;
		p[i] = P[one][k];
		one ^= other ^= one ^= other;
	}
}

void pre(){
	int i = 1;
	for(int p = 1;p <= 1000;p++){
		while(2000*::p[i] < p && abs(2000*::p[i] < p) > 1e-9) i++;
		ans[p] = i;
	}
}

int main(){
	int q; scanf("%d %d",&k,&q);
	init();
	pre();
	while(q--){
		int p ; scanf("%d",&p);
		printf("%d\n",ans[p]);
	}
	
	
	return 0;
}
