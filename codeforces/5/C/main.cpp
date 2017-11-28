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

const int MAX = 1000*1000 + 10;
char expression[MAX];
int pref[MAX],n;
vi EQUAL[2*MAX];
int offset = MAX;

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	cin >> expression;
	n = strlen(expression);
	loop(i,n) pref[i + 1] = pref[i] + ((expression[i] == '(') ? 1 : -1);
	loop(i,n+1) EQUAL[pref[i] + offset].pb(i);
	vi ST; ST.pb(n);
	int max_len = 0,cnt = 1;
	for(int i = n-1;i >= 0;i--) {
		while(!ST.empty() && pref[ST.back()] >= pref[i]) ST.pop_back();
		int r = ST.empty() ? (n+1) : ST.back();
		auto p = lower_bound(all(EQUAL[pref[i] + offset]),r);
		if(p != EQUAL[pref[i] + offset].begin()) {
			--p;
			int len = *p - i;
			//cout << i << " to " << *p << " len " << len << endl;
			if(len){
				if(len > max_len) {
					max_len = len;
					cnt = 0;
				}
				if(len == max_len) cnt++;
			}
		}
		ST.push_back(i);
	}
	cout << max_len << " " << cnt << endl;
	return 0;
}
