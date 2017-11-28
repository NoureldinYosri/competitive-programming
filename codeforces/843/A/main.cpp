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

const int MAX = 1 << 20;
int A[MAX],B[MAX],n;
vector<vi> ans;
int vis[MAX];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
	copy(A,A + n,B);
	sort(B,B + n);
	int m = unique(B,B + n) - B;
	loop(i,n) A[i] = lower_bound(B,B + m,A[i]) - B;
	loop(i,n) if(!vis[i]) {
		int cur = i;
		vi aux;
		while(!vis[cur]) {
			vis[cur] = 1;
			aux.pb(cur + 1);
			cur = A[cur];
		}
		ans.pb(aux);
	}
	printf("%d\n",sz(ans));
	for(auto V : ans){
		printf("%d",sz(V));
		for(int x : V) printf(" %d",x);
		puts("");
	}
	return 0;
}
