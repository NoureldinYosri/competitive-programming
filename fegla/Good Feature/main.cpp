#pragma GCC optimize ("O3")
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
#define pl pair<ll,ll>
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

char buffer[300];
int siz[300];

void solve(){
	string input = string(buffer);
	vector<char> ST;
	memset(siz,0,sizeof siz);
	int depth = 0,mx = 0;
	for(char c : input) {
		if(c == '{') ST.pb(c),depth ++;
		else if(c == '}') {
			int ctr = 1;
			while(ST.back() == ',') {
				ST.pop_back();
				++ctr;
			}
			siz[depth] = max(siz[depth],ctr);
			//cerr << depth << " " << ctr << endl;
			depth--;
			ST.pop_back();
		}
		else if(c == ',') ST.pb(',');
		mx = max(mx,depth);
	}
	range(i,1,mx) printf("[%d]",siz[i]);
	puts("");
}

int main(){
	freopen("good.in", "r", stdin);
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%s",buffer);
		solve();
		//break;
	}
	return 0;
}
