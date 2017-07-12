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

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	string S; cin >> S;
	vi pos;
	int L = string("happiness").size();


	for(int i = 0;i <= sz(S) - L;i++) if(S[i] == 'h'){
		if(S.substr(i,L) == "happiness") {
			pos.pb(i);
			i += L - 1;
		}
	}
	if(pos.empty()){
		int h = -1,p = -1;
		for(int i = 0;i < sz(S);i++){
			if(S[i] == 'h' && h == -1) h = i;
			if(S[i] == 'p') p = i;
		}
		puts("YES");
		if(h == -1 || p == -1) puts("1 2\n");
		else printf("%d %d\n",h + 1,p + 1);
	}
	else if(pos.size() == 1){
		int x = pos[0] + 1;
		puts("YES");
		printf("%d %d\n",x ,x + 1);
	}
	else if(pos.size() == 2){
		int x = pos[0] + 1,y = pos[1] + 1;
		puts("YES");
		printf("%d %d\n",x,y + 1);
	}
	else cout << "NO" << endl;
	return 0;
}
