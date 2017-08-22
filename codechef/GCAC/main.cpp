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

const int MAX = 1000 + 10;
int minSalary[MAX],offeredSalary[MAX],maxJobOffers[MAX],employed[MAX];
char qual[MAX][MAX];
int n,m;

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%d %d",&n,&m);
		loop(i,n) scanf("%d",minSalary + i);
		loop(i,m) scanf("%d %d",offeredSalary + i,maxJobOffers + i),employed[i] = 0;
		int offeredJob = 0,couldntemply = m;
		ll totOffered = 0;
		loop(i,n) {
			int c = -1;
			scanf("%s",qual[i]);
			loop(j,m) if(qual[i][j] == '1'){
				if(!maxJobOffers[j]) continue;
				if(offeredSalary[j] < minSalary[i]) continue;
				if(c == -1 || offeredSalary[c] < offeredSalary[j])
					c = j;
			}
			if(c != -1) {
				offeredJob++;
				totOffered += offeredSalary[c];
				maxJobOffers[c]--;
				if(!employed[c]) couldntemply--;
				employed[c] = 1;
			}
		}
		printf("%d %lld %d\n",offeredJob,totOffered,couldntemply);
	}
	return 0;
}
