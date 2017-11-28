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

int A[26],n;

bool valid(int cnt,int & len){
	len = cnt;
	int odd = 0;
	loop(i,n) {
		int x = A[i]/cnt;
		odd += x & 1;
	}
	if(odd == 0) len += cnt;
	return odd <= 1;
}

void build(int cnt){
	if(!cnt) {
		loop(i,n) {
			while(A[i]--) putchar(i + 'a');
		}
		puts("");
		return;
	}
	string s;
	loop(i,n){
		int x = A[i]/cnt;
		x >>= 1;
		while(x--) s.pb('a' + i);
	}
	string z = s;
	reverse(all(z));
	loop(i,n){
		int x = A[i]/cnt;
		if(x & 1) {
			s.pb(i + 'a');
		}
	}
	s += z;
	loop(i,cnt) printf("%s",s.c_str());
	puts("");
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	int g = 0;
	loop(i,n){
		scanf("%d",A + i);
		if(A[i]) g = __gcd(g,A[i]);
	}
	int best_len = 0,best_d = 0;
	for(int i = 1;i*i <= g;i++)
		if(g%i == 0){
			int x;
			if(valid(i,x)) {
				if(best_d < x) {
					best_d = i;
					best_len = x;
				}
			}
			if(valid(g/i,x)) {
				if(best_d < x) {
					best_d = g/i;
					best_len = x;
				}
			}
		}

	printf("%d\n",best_len);
	build(best_d);

	return 0;
}
