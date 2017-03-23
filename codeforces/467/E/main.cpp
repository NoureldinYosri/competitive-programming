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

const int MAX = 500'010;
int A[MAX],n,B[MAX],m;
vi IDX[MAX];
int lst[MAX],nxt[MAX],dp[MAX],use[MAX];
vi ST[MAX << 2];

void build(int node,int s,int e){
	if(s == e){
		ST[node].pb(nxt[s]);
		return ;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	build(left,s,m);
	build(right,m+1,e);
	int i = 0,j = 0;
	vi & A = ST[left],&B = ST[right];
	while(i < sz(A) && j < sz(B)){
		if(A[i] < B[j]) ST[node].pb(A[i++]);
		else ST[node].pb(B[j++]);
	}
	while(i < sz(A)) ST[node].pb(A[i++]);
	while(j < sz(B)) ST[node].pb(B[j++]);
}

int query(int node,int s,int e,int l,int r,int k){
	if(l <= s && e <= r){
		auto p = upper_bound(all(ST[node]),k);
		if(p == ST[node].end()) return n;
		else return *p;
	}
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	if(r <= m) return query(left,s,m,l,r,k);
	if(m < l) return query(right,m+1,e,l,r,k);
	return min(query(left,s,m,l,m,k),query(right,m+1,e,m+1,r,k));
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i),B[i] = A[i];
	sort(B,B + n);
	m = unique(B,B + n) - B;
	loop(i,n) {
		A[i] = lower_bound(B,B + m,A[i]) - B;
		IDX[A[i]].pb(i);
	}
	memset(lst,-1,sizeof lst);
	for(int i = n - 1;i >= 0;i--){
		nxt[i] = lst[A[i]];
		lst[A[i]] = i;		
	}
	build(1,0,n-1);
	
	for(int i = n - 1;i >= 0;i--){
		dp[i] = dp[i + 1];
		use[i] = 0;
		auto p = lower_bound(all(IDX[A[i]]),i);
		if(IDX[A[i]].end() - p >= 4) {
			loop(i,3) p++;
			if(dp[*p + 1] + 2 > dp[i]){
				use[i] = 1;
				dp[i] = dp[*p + 1]  + 2;
				lst[i] = *p;
			}
		}
		if(i+1 == nxt[i] || nxt[i] == -1) continue;
		int j = query(1,0,n-1,i+1,nxt[i]-1,nxt[i]);
		if(j == n) continue;
		if(dp[j+1] + 2 > dp[i]){
			use[i] = 1;
			dp[i] = dp[j + 1] + 2;
			lst[i] = j;
		}
	}
	cout << 2*dp[0] << endl;
	cerr << dp[0] << endl;
	for(int i = 0;i < n;i++){
		if(use[i]){
			int x = B[A[i]],y = B[A[lst[i]]];
			printf("%d ",x);
			printf("%d ",y);
			printf("%d ",x);
			printf("%d ",y);
			i = lst[i];
		}
	}
	puts("");	
	return 0;
}
