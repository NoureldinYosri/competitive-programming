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
int A[MAX],B[MAX],n;
int ord1[MAX],ord2[MAX];
int ctr[MAX];
ll sa = 0,sb = 0;
int ord[MAX << 1];
int inv[MAX];

int main(){
	scanf("%d",&n);
	ll totA = 0,totB = 0;
	loop(i,n) {
		scanf("%d",A + i);
		ord1[i] = i;
		totA += A[i];
	}
	loop(i,n) {
		scanf("%d",B + i);
		ord2[i] = i;
		totB += B[i];
	}

	sort(ord1,ord1 + n,[](const int & a,const int & b){
		return A[a] > A[b];
	});
	//prArr(ord1,n,int);
	vi S;
	S.pb(ord1[0]);
	for(int i = 1;i < n;i += 2){
		if(i == n-1 || B[ord1[i]] >= B[ord1[i + 1]]) S.pb(ord1[i]);
		else S.pb(ord1[i + 1]);
	}
	printf("%d\n",sz(S));
	for(int x : S) printf("%d ",x + 1);
	puts("");
	return 0;
}
