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

const int MAX = 1e5 + 1e2;
int A[MAX],B[MAX],n,m;
int BIT[2][MAX];
int pref[MAX],suff[MAX];

void update(int p,int v,int *T){
	for(;p <= m + 1;p += LSOne(p)) T[p] += v;
}

int get(int p,int *T){
	int ret = 0;
	for(;p;p ^= LSOne(p)) ret += T[p];
	return ret;
}

int main(){
	ll k ; scanf("%d %lld",&n,&k);
	loop(i,n) scanf("%d",A + i),B[i] = A[i];
	sort(B,B + n);
	m = unique(B,B + n) - B;
	loop(i,n) A[i] = upper_bound(B,B + m,A[i]) - B;
	ll inv = 0,tot_inv = 0,ans = 0,cnt = 0,inv_out;
	loop(i,n){
		tot_inv += get(m + 1,BIT[0]) - get(A[i],BIT[0]);
		update(A[i],1,BIT[0]);
	}
	inv_out = tot_inv;
	memset(BIT,0,sizeof BIT);
	for(int i = n-1;i >= 0;i--){
		suff[i] = get(A[i] - 1,BIT[0]);
		update(A[i],1,BIT[0]);
	}
	memset(BIT,0,sizeof BIT);
	// inv_out = tot_inv - inv_in - cnt;
	int l = 0; update(A[l],1,BIT[1]);
	for(int r = 1;r < n;r++){
		if(r != l + 1){
			inv += get(m+1,BIT[0]) - get(A[r-1],BIT[0]);
			inv_out -= suff[r-1];
			inv_out -= get(m + 1,BIT[1]) - get(A[r-1],BIT[1]);
			update(A[r-1],1,BIT[0]);
			assert(inv >= 0);
			assert(inv_out >= 0);
		}
		while(l+1 < r && inv_out <= k){
			++l;
			inv -= get(A[l]-1,BIT[0]);
			update(A[l],-1,BIT[0]);
			inv_out += suff[l] - get(A[l]-1,BIT[0]);
			inv_out += get(m+1,BIT[1]) - get(A[l],BIT[1]);
			update(A[l],1,BIT[1]);
		}
		assert(inv >= 0);
		assert(inv_out >= 0);
//		cerr << l << " " << r << " " << inv << " " << inv_out << endl;
		ans += l + (inv_out <= k);
	}
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
