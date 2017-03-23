#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define rrep(i,n) for(int i = (n);i >= 0;i--)
#define rran(i,a,b) for(int i = (b);i >= (a);i--)
#define step(i,a,b,d) for(int i = (a);i <= (b); i += d)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) A.size()
#define len(A) A.length()
#define print(A,t) cout << #A << ": "; copy(all(A),ostream_iterator<t>(cout," " )); cout << endl
#define pi pair<int,int>
#define point pi
#define vi vector<int>
#define ll long long
#define pl pair<ll,ll>
#define pre() cin.tie(0),cout.tie(0),ios_base::sync_with_stdio(0)
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define xx first
#define yy second
#define prp(p) cerr << "(" << (p).first << " ," << (p).second << ")";
#define prArr(A,n,t)  cout << #A << ": "; copy(A,A + n,ostream_iterator<t>(cout," " )); cout << endl
using namespace std;

int n;
pi P[1 << 20];
int A[1 << 20];

ll ccw(pi a,pi b){
	return a.xx*1LL*b.yy - a.yy *1LL*b.xx;
}

bool cmp(const pi & a,const pi & b){
	if(a.yy > 0 && b.yy > 0) return ccw(a,b) > 0;
	if(a.yy < 0 && b.yy < 0) return ccw(a,b) > 0;
	if(a.yy > 0 && b.yy < 0) return 1;
	if(a.yy < 0 && b.yy > 0) return 0;
	assert(!a.yy || !b.yy);
	if(!a.yy && !b.yy) return a.xx > b.xx;
	else if(!a.yy) {
		if(a.xx > 0) return 1;
		return b.yy < 0;
	}
	else{
		if(b.xx > 0) return 0;
		return a.yy > 0;
	}
}


pi get_vec(pi a,pi b){
	return {a.xx*b.xx + a.yy*b.yy,b.yy*a.xx-b.xx*a.yy};
}

int main(){
	scanf("%d",&n);
	loop(i,n) scanf("%d %d",&P[i].xx,&P[i].yy),A[i] = i;
	sort(A,A + n,[](const int & a,const int & b){
		return cmp(P[a],P[b]);
	}); 
//	loop(i,n) {prp(P[A[i]]);}
//	cerr << endl;
	pi anc = {0,1};
	pi vec = {-1,0};
	loop(i,n){
		int j = i + 1; if(j == n) j = 0;
		pi aux = get_vec(P[A[i]],P[A[j]]);
		if(cmp(aux,vec) || !anc.xx){
			vec = aux;
			anc = mp(A[i]+1,A[j]+1);
		}

	}

	printf("%d %d\n",anc.xx,anc.yy);
	prp(anc); cerr << endl;
	return 0;
}

