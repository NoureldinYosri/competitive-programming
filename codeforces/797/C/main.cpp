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
char line[MAX];
char mn[MAX];


int main(){
	scanf("%s",line);
	int L = strlen(line);
	char c = 'z';
	mn[L] = c;
	for(int i = L-1;i >= 0;i--){
		c = min(c,line[i]);
		mn[i] = c;
	}
	vector<char> ST;
	for(int i = 0;i < L || !ST.empty();){
		if(i < L && (ST.empty() || mn[i] < ST.back())) {
			ST.pb(line[i]);
			i++;
		}
		else {
			putchar(ST.back());
			ST.pop_back();
		}
	}
	puts("");
	return 0;
}
