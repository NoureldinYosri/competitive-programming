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

const int MAX = 2*100*1000 + 10;
char txt[MAX];
int SA[MAX],Rank[MAX],aux[MAX];

int main(){
	//freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif

	scanf("%s",txt);
	int L = strlen(txt);
	strncpy(txt + L,txt,L);
	L <<= 1;
	txt[L++] = '$';
	txt[L] = 0;

	loop(i,L+1) SA[i] = i,Rank[i] = txt[i];

	for(int k = 0;(1 << k) <= (L + 1);k++){
		auto cmp = [k,L](const int & a,const int & b){
			if(Rank[a] != Rank[b]) return Rank[a] < Rank[b];
			int ca = min(a + (1 << k),L),cb = min(b + (1 << k),L);
			return Rank[ca] < Rank[cb];
		};
		stable_sort(SA,SA + L + 1,cmp);
		int r = 0;
		aux[SA[0]] = 0;
		for(int i = 1;i <= L;i++){
			r += cmp(SA[i - 1],SA[i]);
			aux[SA[i]] = r ;
		}
		for(int i = 0;i <= L;i++) Rank[i] = aux[i];
	}

	int ans = 0;
	for(int i = 0;i <= L;i++)
		if(SA[i] <= L/2) {
			ans = SA[i];
			break;
		}
	cout << ans << endl;
	//cerr << ans << endl;

	return 0;
}
