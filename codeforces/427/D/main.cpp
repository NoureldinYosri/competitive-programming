#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define PI acos(-1)
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
#define vl vector<long long>
#define vd vector<double>
#define vp vector<pair<int,int> >
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
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
using namespace std;


const int MAX = 5010;
char A[MAX],B[MAX],C[MAX << 1];
int SA[MAX << 1],LCP[MAX << 1];
int r[MAX << 1];
int ST[MAX << 1][20],lg[MAX << 1];

int lcp(int i,int j,char *line){
	int len = 0;
	for(;line[i] == line[j];i++,j++,len++);
	return len;
}

int lcp(int a,int b){
	a = r[a],b = r[b]; 
	if(a > b) swap(a,b);
	b--;
	int l = lg[b - a + 1];
	return min(ST[a][l],ST[b - (1 << l) + 1][l]);
}

vp preprocess(char *line,int offset = 0){
	int n = strlen(line);
	loop(i,n + 1) SA[i] = i;
	sort(SA,SA + n,[line](const int & a,const int & b){
		return strcmp(line + a,line + b) < 0;
	});
	int prv = 0;
	vp cand;
	loop(i,n){
		int cur = lcp(SA[i],SA[i + 1],line);
		LCP[i] = cur;
	//	if(n - SA[i] + 1 >= max(cur,prv) + 1) 
			cand.pb(mp(SA[i] + offset,max(cur,prv) + 1));
		prv = cur;	
	//	fprintf(stderr,"%s -> %d\n",line + SA[i] - offset,cur);
	}
//	cerr << endl;
	return cand;
}

void buildST(){
	lg[0] = -1;
	int L = strlen(C);
	loop(i,L) lg[i + 1] = lg[i] + ((i + 1) == LSOne(i + 1));
	loop(i,L) ST[i][0] = LCP[i];
	loop(k,19){
		loop(i,L){
			int j = i + (1 << k);
			if(j >= L) j = i;
			ST[i][k + 1] = min(ST[i][k],ST[j][k]);
		}
	}
}

int main(){
	cin >> A >> B;
	vp CA = preprocess(A);
	vp CB = preprocess(B,strlen(A) + 1);

	strcpy(C,A);
	C[strlen(C)] = '$';
	strcpy(C + strlen(C),B);
	preprocess(C);
	buildST();
	int L = strlen(C);
	loop(i,L) r[SA[i]] = i;
	
	int ans = INT_MAX;
	for(auto a : CA) for(auto b : CB){
		int len = lcp(a.xx,b.xx);
		if(len >= max(a.yy,b.yy)) {
			ans = min(ans,max(a.yy,b.yy));
			//fprintf(stderr,"(%s,%d) (%s,%d) -> %d\n",C + a.xx,a.yy,C + b.xx,b.yy,len);
		}
	}
	if(ans == INT_MAX) ans = -1;
	cerr << ans << endl;
	cout << ans << endl;
	return 0;
}
