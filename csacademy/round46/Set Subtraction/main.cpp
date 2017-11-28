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

const int MAX = 2 << 10;
ll A[MAX];
int n;
int taken[MAX];

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> n;
	loop(i,2*n) cin >> A[i];
	sort(A,A + 2*n);

	for(int i = 1;i < 2*n;i++){
		ll X = A[i] - A[0];
		if(!X) continue;
		map<ll,vi> M;
		memset(taken,0,sizeof taken);
		taken[i] = 1;
		vi ans;
		ans.pb(A[i]);
		for(int j = 1;j < 2*n;j++)
			if(i != j)
				M[A[j]].pb(j);
		bool cond = 1;
		for(int j = 1;j < 2*n;j++)
			if(!taken[j]){
				ll target = A[j] + X;
				ans.pb(target);
				if(M[target].empty()) {
					cond = 0;
					break;
				}
				taken[M[target].back()] = 1;
				M[target].pop_back();
			}
		if(!cond) continue;
        cout << X << endl;
        for(int i = 0;i < n;i++) printf("%d%c",ans[i]," \n"[i==n-1]);
        return 0;
	}
    cout << -1 << endl;
	return 0;
}
