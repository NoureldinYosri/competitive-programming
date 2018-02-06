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

const int MAX = 100*1000 + 10;
int A[MAX],B[MAX],n,ord[MAX],C[MAX];


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	range(t,1,T) {
		scanf("%d",&n);
		loop(i,n) scanf("%d",A + i);
		copy(A,A + n,B);
		copy(A,A + n,C);

		vi ones,twos;
		loop(i,n) ord[i] = i;
		sort(ord,ord + n,[](const int & a,const int & b) {
			return A[a] < A[b];
		});
		loop(i,n) {
			int j = i;
			while(j < n && A[ord[i]] == A[ord[j]]) j++;
			int cnt = j - i;
			assert(cnt == 1 || cnt == 2);
			if(cnt == 1) ones.pb(ord[i]);
			else {
				twos.pb(ord[i]);
				twos.pb(ord[i + 1]);
			}
			i = j - 1;
		}

		vi aux;
		if(sz(twos) > 2){
			aux = vi{all(twos)};
			rotate(aux.begin(),aux.begin() + 2,aux.end());
			loop(i,sz(aux)) B[aux[i]] = A[twos[i]];
			loop(i,sz(aux)) C[twos[i]] = B[twos[i]];
			if(sz(ones) > 0) ones.pb(twos[0]);
			if(sz(ones) > 1) ones.pb(twos[1]);
		}
		else {
			for(int x : twos) ones.pb(x);
		}


		aux = vi{all(ones)};
		if(sz(aux) > 2) rotate(aux.begin(),aux.begin() + 2,aux.end());
		else if(!aux.empty()) rotate(aux.begin(),aux.begin() + 1,aux.end());

		loop(i,sz(aux)) B[aux[i]] = C[ones[i]];



		int res = 0;
		loop(i,n) res += A[i] != B[i];

		printf("%d\n",res);
		loop(i,n) printf("%d%c",B[i]," \n"[i==n-1]);
	}
	return 0;
}
