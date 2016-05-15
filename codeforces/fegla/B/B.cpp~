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

const int MAX = 2e5;
int A[MAX],B[MAX],C[MAX],ord[MAX],n,m,MortadellaID,T;
char name[MAX][30],MortadellaName[30];
int took[MAX],taken[MAX];

bool cmp(const int & a,const int & b){
	if(C[a] == C[b]) return strcmp(name[a],name[b]) > 0;
	return C[a] < C[b];
}


int get_best(){
	loop(i,n) ord[i] = i;
	copy(A,A + n,C);
	C[MortadellaID] += B[n - 1];
	sort(ord,ord + n,&cmp);
	int j = n - 2,pos = -1;
	loop(i,n) if(ord[i] == MortadellaID) pos = i;
	for(++pos;pos < n;) C[ord[pos++]] += B[j--];
	pos = 0;
	while(j >= 0) C[ord[pos++]] += B[j--];
	sort(ord,ord + n,&cmp);
	loop(i,n) if(ord[i] == MortadellaID) return n - i;
}

int get_worst(){
	loop(i,n) ord[i] = i,took[i] = taken[i] = 0;
	copy(A,A + n,C);
	C[MortadellaID] += B[0];
	took[MortadellaID] = 1;
	taken[0] = 1;
	sort(ord,ord + n,&cmp);
	//loop(i,n) cerr << name[ord[i]] << " " << C[ord[i]] << endl;
	//cerr << "===============" << endl;
	int j = 1,pos = -1;
	loop(i,n) if(ord[i] == MortadellaID) pos = i;
	for(--pos; pos >= 0;pos--){
		while(j < n){
			bool c = 0;
			c = c || (A[MortadellaID] + B[0] < A[ord[pos]] + B[j]);
			if(A[MortadellaID] + B[0] == A[ord[pos]] + B[j])
				c = c || (strcmp(name[ord[pos]],MortadellaName) < 0);
			if(c) {
				C[ord[pos]] += B[j];
				took[ord[pos]] = 1;
				taken[j] = 1;
				j++;
				break;
			}
			j++;
		}
	}
	int i = 0; j = 0;
	while(i < n && j < n){
		if(took[i]) i++;
		else if(taken[j]) j++;
		else {
			C[i] += B[j];
			i++,j++;
		} 
	}
	sort(ord,ord + n,&cmp);
	//loop(i,n) cerr << name[ord[i]] << " " << C[ord[i]] << endl;
	loop(i,n) if(ord[i] == MortadellaID) return n - i;
}

int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		loop(i,n) scanf("%s %d",name[i],A + i);
		scanf("%d",&m);
		loop(i,m) scanf("%d",B + i);
		loop(i,n - m) B[i + m] = 0;
		sort(B,B + n);
		scanf("%s",MortadellaName);
		MortadellaID = -1;
		loop(i,n) if(strcmp(MortadellaName,name[i]) == 0) MortadellaID = i;
		assert(MortadellaID >= 0);
		printf("%d %d\n",get_best(),get_worst());
	}
	return 0;
}
