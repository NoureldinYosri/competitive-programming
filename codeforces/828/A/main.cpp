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

const int MAX = 2 << 20;
char buffer[1 << 20];
string s[MAX];
vi occur[MAX];
int n;
int longest_start[MAX];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	memset(longest_start,-1,sizeof longest_start);
	scanf("%d",&n);
	int len = 0;
	loop(i,n){
		scanf("%s",buffer);
		s[i] = string(buffer);
		int k; scanf("%d",&k);
		occur[i].reserve(k);
		while(k--) {
			int x; scanf("%d",&x);
			x--;
			len = max(len,x + sz(s[i]));
			if(longest_start[x] == -1 || sz(s[longest_start[x]]) < sz(s[i])) longest_start[x] = i;
			occur[i].pb(x);
		}
	}
	for(int i = 0;i < len;) {
		if(longest_start[i] == -1) {
			putchar('a');
			i++;
		}
		else{
			int idx = longest_start[i],j = 0;
			for(;j < sz(s[idx]);j++) {
				putchar(s[idx][j]);
				int q = i + j;
				if(longest_start[q] != -1) {
					int l = sz(s[longest_start[q]]);
					if(l > sz(s[idx]) - j) {
						idx = longest_start[q];
						i = q;
						j = 0;
					}
				}
			}
			i += sz(s[idx]);
		}
	}
	puts("");

	return 0;
}
