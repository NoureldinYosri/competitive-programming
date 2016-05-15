#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define vi vector<int>
#define ll long long
#define pi pair<int,int>
#define point pair<double,double>
#define pl pair<ll,ll>
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define PQ priority_queue
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define pre() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;

char out[2][4] = {"NO","YES"};
int N,M;
int choices[30][2];

bool bt(int i,int *A){
	if(i == M) return 1;
	loop(j,2){
		int c = choices[i][j];
		A[c]++;
		if(A[c] <= N) {
			if(bt(i + 1,A)) return 1;
		}
		A[c]--;
	}
	return 0;
}

int get_idx(char *s){
	if(strcmp("XS",s) == 0) return 0;
	else if(strcmp("S",s) == 0) return 1;
	else if(strcmp("M",s) == 0) return 2;
	else if(strcmp("L",s) == 0) return 3;
	else if(strcmp("XL",s) == 0) return 4;
	else return 5;
}

int main(){
	int T,A[6]; char s[10];
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&N,&M);
		fill(A,A + 6,0);
		N /= 6;
		loop(i,M) loop(j,2){
			scanf("%s",s);
			choices[i][j] = get_idx(s); 
		}
		puts(out[bt(0,A)]);
	}		
	return 0;
}
