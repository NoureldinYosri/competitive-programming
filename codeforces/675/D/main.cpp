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

set<int> S;
const int MAX = 1 << 20;
int L[MAX],R[MAX];
map<int,int> id;

int traverse(int root,int p,int x){
	if(root == -1) return p;
	if(x < root) return traverse(L[id[root]],root,x);
	else return traverse(R[id[root]],root,x);
 }

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	memset(L,-1,sizeof L);
	memset(R,-1,sizeof R);
	int n; scanf("%d",&n);
	int x; scanf("%d",&x); S.insert(x);
	id[x] = 0;
	for(int i = 1;i < n;i++){
		scanf("%d",&x);
		id[x] = i;
		auto p = S.lower_bound(x);
		int root = *S.begin();
		if(p != S.begin()){
			--p;
			root = *p;
		}
		root = traverse(root,-1,x);
		printf("%d%c",root," \n"[i==n-1]);
		S.insert(root);
		if(x < root) L[id[root]] = x;
		else R[id[root]] = x;
	}
	return 0;
}
