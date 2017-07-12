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

const int MAX = 1500 + 10;
int f[128][MAX];
char s[MAX];
int n,m;

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d %s",&n,s);
	for(char c = 'a';c <= 'z';c++){
		for(int i = 0;i < n;i++){
			int ctr = 0;
			for(int j = i;j < n;j++){
				ctr += s[j] != c;
				f[(int)c][ctr] = max(f[(int)c][ctr],j - i + 1);
			}
		}
		for(int i = 0;i < n;i++)
			f[(int)c][i + 1] = max(f[(int)c][i + 1],f[(int)c][i]);
	}
	scanf("%d",&m);
	while(m--){
		char c; int l;
		scanf(" %d %c",&l,&c); l = min(l,n);
		printf("%d\n",f[(int)c][l]);
	}

	return 0;
}
