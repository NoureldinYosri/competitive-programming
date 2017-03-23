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

const int MAX = 200'010;
ll ST[MAX << 2];
int A[MAX],B[MAX],H[MAX],ord[MAX],n;
int C[MAX << 1];

void update(int node,int s,int e,int p,ll v){
	if(s == e) {
		ST[node] = max(ST[node],v);
		return;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) update(left,s,m,p,v);
	else update(right,m+1,e,p,v);
	ST[node] = max(ST[left],ST[right]);
}


ll query(int node,int s,int e,int p){
	if(e <= p) return ST[node];
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(p <= m) return query(left,s,m,p);
	else return max(ST[left],query(right,m+1,e,p));
}


int main(){
	scanf("%d",&n);
	int k = 0;
	loop(i,n) {
		scanf("%d %d %d",A + i,B + i,H + i);
		ord[i] = i;
		C[k++] = A[i];
		C[k++] = B[i];
	}
	sort(C,C + k);
	k = unique(C,C + k) - C;
	loop(i,n) {
		A[i] = upper_bound(C,C + k,A[i]) - C;
		B[i] = upper_bound(C,C + k,B[i]) - C;
	}
	sort(ord,ord + n,[](const int & a,const int & b){
		if(B[a] == B[b]) return A[a] > A[b];
		else return B[a] > B[b];
	});

	ll ans = 0;
	loop(j,n){
		int i = ord[j];
		ll v = query(1,0,k,B[i] - 1) + H[i];
		update(1,0,k,A[i],v);
		ans = max(ans,v);
	}
	cout << ans << endl;
	cerr << ans << endl;
	return 0;
}
