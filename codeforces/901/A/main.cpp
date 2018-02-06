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

const int MAX = 3*100*1000 + 10;
int C[MAX],n;
int P1[MAX],P2[MAX],m;

void build(int h) {
	int s = 0,e = 0;
	loop(i,n) {
		loop(j,C[i]){
			++m;
			P1[m] = s;
			P2[m] = s;
		}
		if(i == h+1)
			P2[m] = e;
		s = e+1;
		e = m;
	}
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	n++;
	loop(i,n) {
		scanf("%d",C + i);
		assert(C[i] > 0);
		if(i == 0) assert(C[i] == 1);
	}
	int h = -1;
	loop(i,n-1) if(C[i] > 1 && C[i + 1] > 1) {
		h = i;
		break;
	}
	if(h == -1) puts("perfect");
	else {
		puts("ambiguous");
		build(h);
		range(i,1,m) printf("%d%c",P1[i]," \n"[i==m]);
		range(i,1,m) printf("%d%c",P2[i]," \n"[i==m]);
	}
	return 0;
}
