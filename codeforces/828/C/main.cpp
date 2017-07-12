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

const int MAX = 100* 1000 + 10;
int BIT[11][10][4][MAX],len;
char I[MAX];
map<char,int> M;

inline void update(int p,int v,int *T){
	for(++p;p <= len;p += LSOne(p)) T[p] += v;
}
inline int get(int p,int *T){
	int ret = 0;
	for(++p;p;p^= LSOne(p)) ret += T[p];
	return ret;
}

void init(){
	string DNA = "ATGC";
	loop(i,4) M[DNA[i]] = i;
	len = strlen(I);
	for(int i = 0;i < len;i++) {
		int j = M[I[i]];
		for(int L = 1;L <= 10;L++)
			update(i,1,BIT[L][i%L][j]);
	}
}

char buffer[1 << 20];

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	scanf("%s",I);
	init();
	int n; scanf("%d",&n);
	loop(_,n){
		int type; scanf("%d",&type);
		if(type == 1) {
			int pos; char c,old;
			scanf("%d %c",&pos,&c);
			pos--;
			old = I[pos];
			int j = M[old];
			for(int L = 1;L <= 10;L++)
				update(pos,-1,BIT[L][pos%L][j]);
			j = M[I[pos] = c];
			for(int L = 1;L <= 10;L++)
				update(pos,1,BIT[L][pos%L][j]);
		//	cerr << I << endl;
		}
		else{
			int l,r;
			scanf("%d %d %s",&l,&r,buffer);
			--l,r--;
			int ans = 0;
			for(int i = 0,L = strlen(buffer);i < L;i++){
				int j = M[buffer[i]];
				int up = get(r,BIT[L][(i + l)%L][j]);
				int down = get(l-1,BIT[L][(i + l)%L][j]);
				ans += up - down;
			//	cerr << buffer[i] << " " << i << " " << down << " " << up << endl;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
