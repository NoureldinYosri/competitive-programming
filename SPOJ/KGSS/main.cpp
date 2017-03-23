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

const int MAX = 1 << 17;
int ST[MAX << 1][2];

void merge(int *A,int *B,int *C){
	int aux[4];
	loop(i,2) aux[i] = A[i],aux[i + 2] = B[i];
	sort(aux,aux + 4);
	loop(i,2) C[i] = aux[3 - i];
}

void update(int node,int s,int e,int p,int v){
	if(s == e) {
		ST[node][0] = v;
		ST[node][1] = INT_MIN;
		return;
	}
	int m = (s + e) >> 1,left = 2*node + 1,right = left + 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
	merge(ST[left],ST[right],ST[node]);
}

void query(int node,int s,int e,int l,int r,int *res){
	if(l <= s && e <= r){
		copy(ST[node],ST[node]+2,res);
		return;
	}
	int m = (s + e) >> 1,left = 2*node + 1,right = left + 1;
	if(r <= m) return query(left,s,m,l,r,res);
	if(m < l) return query(right,m+1,e,l,r,res);
	int A[2],B[2];
	query(left,s,m,l,m,A);
	query(right,m+1,e,m+1,r,B);
	merge(A,B,res);	
}

int main(){
	fill(&ST[0][0],&ST[MAX << 1][0],INT_MIN);
	int n; scanf("%d",&n);
	loop(i,n) {
		int x; scanf("%d",&x);
		update(0,0,n-1,i,x);
	}
	int m; scanf("%d",&m);
	loop(i,m){
		char c; int a,b; scanf(" %c %d %d",&c,&a,&b);
		if(c == 'Q') {
			int res[2]; query(0,0,n-1,a-1,b-1,res);
			printf("%d\n",res[0] + res[1]);
		}
		else update(0,0,n-1,a-1,b);
	}
	
	
	return 0;
}
