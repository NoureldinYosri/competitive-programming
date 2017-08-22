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

char A[1 << 20],B[1 << 20];
int cntA[26],cntB[26];


char solve(){
	loop(i,26){
			if(cntA[i] >= 2 && cntB[i] == 0)
				return 'A';
	}
	bool has = 0;
	loop(i,26) {
		if(cntA[i] && !cntB[i]) has = 1;
	}
	if(!has) return 'B';
	has = 0;
	loop(i,26) {
		if(!cntA[i] && cntB[i]) has = 1;
	}
	if(!has) return 'A';
	return 'B';
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	int T; scanf("%d",&T);
	while(T--) {
		scanf("%s %s",A,B);
		int len = strlen(A);
		memset(cntA,0,sizeof cntA);
		memset(cntB,0,sizeof cntB);
		loop(i,len) cntA[A[i] - 'a']++;
		loop(i,len) cntB[B[i] - 'a']++;
		putchar(solve());
		puts("");
	}
	return 0;
}
