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


const int MAXQ = 5001,MAXN = 100'010,MAXLG = 20;
int L[MAXQ],R[MAXQ],ord[MAXQ],m;
double P[MAXQ];
int A[MAXN],n;
int ST[MAXN][MAXLG],lg[MAXN];
vi G[MAXQ];

void build(){
	lg[0] = -1;
	loop(i,MAXN - 1) lg[i + 1] = lg[i] + ((i + 1) == LSOne(i + 1));
	loop(i,n) ST[i][0] = A[i];
	loop(k,MAXLG-1)
		loop(i,n){
			int j = i + (1 << k);
			if(j >= n) j = i;
			ST[i][k + 1] = max(ST[i][k],ST[j][k]);
		}
}

double get_max(int s,int e){
	int l = lg[e - s + 1];
	return max(ST[s][l],ST[e - (1 << l) + 1][l]);
}

double dfs(int q){
	sort(all(G[q]),[](const int & a,const int & b){
		return L[a] < L[b];
	});
	cerr << q << " ";
	print(G[q],int);
	int cur = L[q] - 1;
	double ret = 0;
	for(int p : G[q]){
		assert(cur <= L[p]);
		if(cur + 1 <= L[p] - 1) ret = max(ret,get_max(cur + 1,L[p] - 1));
		ret = max(ret,dfs(p));
		cur = R[p];
	}
	if(cur < R[q]) ret = max(ret,get_max(cur + 1,R[q]));
	return ret + P[q];
}

int main(){
	scanf("%d %d",&n,&m);
	loop(i,n) scanf("%d",A + i);
	build();
	L[0] = 0,R[0] = n-1,P[0] = 0;	
	range(i,1,m) scanf("%d %d %lf",L + i,R + i,P + i),ord[i] = i,L[i]--,R[i]--;
	m++;
	sort(ord,ord + m,[](const int & a,const int & b){
		return mp(R[a] - L[a],b) < mp(R[b] - L[b],a);
	});
	for(int i = 0;i < m - 1;i++)
		for(int j = i + 1;j < m;j++)
			if(L[ord[j]] <= L[ord[i]] && R[ord[i]] <= R[ord[j]]){
				G[ord[j]].pb(ord[i]);
				cerr << ord[j] << " " << ord[i] << endl;
				break;
			}
	cerr << dfs(0) << endl;
				 
	return 0;
}
