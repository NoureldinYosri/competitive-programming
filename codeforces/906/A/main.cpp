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

char buffer[1 << 20];

int get(){
	scanf("%s",buffer);
	int ret = 0;
	for(char *p = buffer;*p;p++)
		ret |= 1 << (*p - 'a');
	return ret;
}

string bin(int msk) {
	string ret(26,'0');
	loop(i,26) if(msk & (1 << i)) ret[i] = '1';
	return ret;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int n,ans = 0; scanf("%d",&n);
	int cand = (1 << 26) - 1;
	for(int i = 0;i < n;i++) {
		char c; scanf(" %c",&c);
		int m = get();
//		cerr << c << " " << bin(m) << endl;
		if(c == '.') {
			cand &= ~m;
		}
		else if(c == '!'){
			if(cand == LSOne(cand)) {
//				cerr << "inc !" << endl;
				ans++;
			}
			cand &= m;
		}
		else {
			if(i == n-1) {

			}
			else {
				if(cand == LSOne(cand))
					ans++;
				cand &= ~m;
			}
		}
//		cerr << bin(cand) << endl;
	}
	printf("%d\n",ans);
	return 0;
}
