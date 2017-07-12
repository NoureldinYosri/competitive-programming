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
#define popcnt(x) __builtin_popcount(x)
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

const int MAX = 100*1000 + 10;
int n,Q;
int A[MAX];
int isBegin[MAX],cntTillNow[MAX],maxLen[MAX];
int BIT[MAX];
int L[MAX],R[MAX],K[MAX],ans[MAX];
vector<pair<pi,pi> > V;

void update(int p){
	for(;p <= n;p += LSOne(p)) BIT[p]++;
}

int get(int p){
	int ret = 0;
	for(;p;p ^= LSOne(p)) ret += BIT[p];
	return ret;
}

int main(){
//	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	int T; scanf("%d",&T);
	for(int t = 1;t <= T;t++){
		memset(BIT,0,sizeof BIT);
		V.clear();
		memset(isBegin,0,sizeof isBegin);
		scanf("%d %d",&n,&Q);
		range(i,1,n) scanf("%d",A + i);
		for(int i = 1;i <= n;){
			int j = i;
			isBegin[i] = 1;
			while(j <= n && A[i] == A[j]){
				cntTillNow[j] = j - i + 1;
				j++;
			}
			V.pb(mp(mp(j - i,1),mp(i,j)));
			int len = j - i;
			for(;i < j;i++) maxLen[i] = len;
		}
		for(int i = 0;i < Q;i++){
			scanf("%d %d %d",L + i,R + i,K + i);
			V.pb(mp(mp(K[i],-1),mp(i,i)));
		}
		sort(all(V));
		reverse(all(V));
		for(auto e : V){
			int k = e.xx.xx,type = e.xx.yy,l = e.yy.xx,r = e.yy.yy;
			if(type == -1){
				//cerr << "compute answer of " << k << endl;
				int idx = l;
				l = L[l];
				r = R[r];
				int tmp = get(r) - get(l - 1);
				if(maxLen[r] >= k){
					if(cntTillNow[r] < k) tmp--;
				}
				if(!isBegin[l] && maxLen[l] - cntTillNow[l] + 1 >= k) tmp++;
				ans[idx] = tmp;
			}
			else{
				//cerr << "insert len " << k << " at " << l << endl;
				update(l);
			}
		}
		loop(i,Q) printf("%d\n",ans[i]);
	}
	return 0;
}
