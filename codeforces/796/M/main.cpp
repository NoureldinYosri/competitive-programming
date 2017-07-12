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

pi A[1 << 20];
int n;

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d",&n);
	ll sum = 0;
	loop(i,n) {
		scanf("%d",&A[i].xx),A[i].yy = i + 1;
		sum += A[i].xx;
	}
	if(sum > n -1){
		puts("NO");
		return 0;
	}
	sort(A,A + n);
	vi toKill;
	vp E;
	cerr << toKill.size() << endl;
	for(int i = 0;i < n;i++){
		auto p = A[i];
		int who = p.yy;
		int num = p.xx;
		for(;num;num--){
			if(toKill.empty()){
				puts("NO");
				return 0;
			}
	//		cerr << who << " kills " << toKill.back() << endl;
			E.pb(mp(who,toKill.back()));
			toKill.pop_back();
		}
	//	cerr << "insert " << who << " into killabels" << endl;
		toKill.pb(who);
	}
	puts("YES");
	for(auto p : E) printf("%d %d\n",p.xx,p.yy);
	return 0;
}
