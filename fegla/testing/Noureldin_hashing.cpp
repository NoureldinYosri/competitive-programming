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

struct st_node{
	int cnt;
	int h[2],sum_coef[2];
	ll sum_indices;
	int la;
};

ostream& operator << (ostream & st,const st_node & node){
	st << "(" << node.cnt << " ,(" << node.h[0] << " ," << node.h[1] << ") ,";
	st << "(" << node.sum_coef[0] << " ," << node.sum_coef[1] << ") ," << node.sum_indices << " ," << node.la << ")";
	return st;
}

const int MAX = 100*1000 + 10;
int n,m;
int A[MAX],B[MAX],C[MAX];
int mod[2],base[2];
int POW[2][MAX];
vi smallP { 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73};
vi bigP{973501687, 979190873, 972765169, 962474831, 976714393, 979097809, 968106283, 977383639, 965782747, 972313789, 967404107, 974263201, 978940031, 963054383, 964554827, 962958977, 972112651, 982236889, 978524933, 982188197, 962420743, 979900177, 975462149, 973602013, 980952491, 970774003, 966357419, 976625681, 963040019, 980450173, 976309153, 972910223, 976526429, 970508741, 963068017, 979569649, 980963443, 972966857, 978455249, 970720189, 976665073, 977168053, 962367881, 964504559, 965704799, 979968601, 968721791, 982322837, 980000971, 980208373};
st_node ST[MAX*4];
int H[MAX][2];

int add(ll a,ll b,int mod){
	a %= mod,b %= mod;
	a += b;
	a += (a >= mod) ? -mod : ((a < 0) ? mod : 0);
	return a;
}

int mul(ll a,ll b,int mod){
	return (a*b)%mod;
}

void init(){
	srand(time(0));
//	srand(0);
	int m = sz(smallP)/2;
	loop(i,2){
		int s = i*m,siz = i ? (sz(smallP) - m) : m;
		base[i] = smallP[s + rand()%siz];
	}
	m = sz(bigP) / 2;
	loop(i,2){
		int s = i*m,siz = i ? (sz(bigP) - m) : m;
		mod[i] = bigP[s + rand()%siz];
	}
//	base[0] = base[1] = 10;
//	mod[0] = mod[1] = 1e9 + 7;
	loop(k,2) {
		POW[k][0] = 1;
		loop(q,MAX-1) POW[k][q + 1] = mul(POW[k][q],base[k],mod[k]);
	}
}

void brute_force_hash(int *A,int *h){
	int aux[MAX];
	loop(i,m) aux[i] = i;
	sort(aux,aux + m,[A](const int & a,const int & b){
		return A[a] < A[b];
	});
	h[0] = h[1] = 0;
	loop(i,m) {
		int j = i;
		while(j < m && A[aux[i]] == A[aux[j]]) {
			loop(k,2) h[k] = add(h[k],mul(aux[j]+1,POW[k][i],mod[k]),mod[k]);
			j++;
		}
		i = j - 1;
	}
}


void compress(int *f,int *t,int len){
	vi aux{f,f + len};
	sort(all(aux));
	aux.resize(unique(all(aux)) - aux.begin());
	loop(i,len) t[i] = lower_bound(all(aux),f[i]) - aux.begin() + 1;
}


bool are_same(int *A,int *B,int len){
	loop(i,len) if(A[i] != B[i]) return 0;
	return 1;
}

#define REDUCE 0
#define INSERT 1
#define REMOVE 2

void update(int node,int offset,int type){
//	cerr << node << " was " << ST[node] << endl;
//	cerr << "offset = " << offset << " type = " << type << endl;
	if(type == REDUCE) {
		assert(offset >= 0);
		offset = min(offset + 0LL,ST[node].sum_indices);
		ST[node].sum_indices -= offset*1LL*ST[node].cnt;
		loop(k,2) ST[node].h[k] = add(ST[node].h[k],mul(-offset,ST[node].sum_coef[k],mod[k]),mod[k]);
		ST[node].la += offset;
	}
	else if(type == INSERT){
		ST[node].cnt ++ ;
		loop(k,2) ST[node].sum_coef[k] = add(ST[node].sum_coef[k],1,mod[k]);
		ST[node].sum_indices += offset;
		loop(k,2) ST[node].h[k] = add(ST[node].h[k],offset,mod[k]);
	}
	else {
		ST[node].cnt -- ;
		loop(k,2) ST[node].sum_coef[k] = add(ST[node].sum_coef[k],-1,mod[k]);
		ST[node].sum_indices -= offset;
		loop(k,2) ST[node].h[k] = add(ST[node].h[k],-offset,mod[k]);
	}
//	cerr << "set " << node << " to " << ST[node] << endl;
}

void push(int node){
	if(!ST[node].la) return;
	int left = node << 1,right = left | 1;
	update(left,ST[node].la,REDUCE);
	update(right,ST[node].la,REDUCE);
	ST[node].la = 0;
}

void merge(st_node & left,st_node & right,st_node & node){
	node.cnt = left.cnt + right.cnt;
	node.sum_indices = left.sum_indices + right.sum_indices;
	node.la = 0;
	loop(k,2) {
		int tmp = mul(POW[k][left.cnt],right.sum_coef[k],mod[k]);
		node.sum_coef[k] = add(left.sum_coef[k],tmp,mod[k]);
	}
	loop(k,2) {
		int tmp = mul(POW[k][left.cnt],right.h[k],mod[k]);
		node.h[k] = add(left.h[k],tmp,mod[k]);
		// 20 + 1 = 21
	}
//	cerr << left << " + " << right << " = " << node << endl;
}

void update(int node,int s,int e,int p,int cnt,int v){
	assert(cnt == 1 || cnt == -1);
	if(s == e) return update(node,v,(cnt == 1) ? INSERT : REMOVE);
	int m = (s + e) >> 1,left = node << 1,right = left | 1;
	push(node);
	if(p <= m) update(left,s,m,p,cnt,v);
	else update(right,m+1,e,p,cnt,v);
	merge(ST[left],ST[right],ST[node]);
}

void reduce(int i){
	update(1,1,n,A[i],-1,1);
	//cerr << "after poping " << ST[1] << endl;
	update(1,1,REDUCE);
	//cerr << "after reducing " << ST[1] << endl;
	//ST[1].la++;
}

void read(){
	scanf("%d",&m);
	loop(i,m) scanf("%d",B + i);
	scanf("%d",&n);
	loop(i,n) scanf("%d",A + i);
}

void solve(bool testing_mode = 0){
//	init();
	if(!testing_mode) read();
	if(n < m) {
		puts("0");
		return;
	}
	compress(A,A,n);
	compress(B,B,m);
	memset(ST,0,sizeof ST);
	int P[2];
	brute_force_hash(B,P);
	//prArr(P,2,int);
	memset(ST,0,sizeof ST);
	loop(i,m) update(1,1,n,A[i],1,i+1);
	//cerr << ST[1] << endl;
	for(int i = 0;i <= n-m;i++) {
		if(!testing_mode && ST[1].h[0] == P[0] && ST[1].h[1] == P[1]) printf("%d ",i);
		// save for testing
		H[i][0] = ST[1].h[0];
		H[i][1] = ST[1].h[1];
		// remove i
		reduce(i);
		if(i+m < n) {
			update(1,1,n,A[i+m],1,m);
		//	cerr << "after inserting " << A[i+m] << " -> " << ST[1] << endl;
		}
	}
	if(!testing_mode) puts("");
}

bool stress_test(int num){
	int MAXA = 100000;
	for(int case_num = 1; case_num <= num; case_num++){
		n = 1 + rand()%1000;
		m = 1 + rand()%n;
		assert(m <= n);
		loop(i,n) A[i] = rand()%MAXA;
		loop(i,m) B[i] = rand()%MAXA;
		solve(1);
		int h[2];
		loop(i,n-m+1) {
			brute_force_hash(A+i,h);
			if(h[0] != H[i][0] || h[1] != H[i][1]) {
				printf("failed on case #%d which is\n",case_num);
				printf("%d\n",m);
				loop(i,m) printf("%d%c",B[i]," \n"[i==m-1]);
				printf("%d\n",n);
				loop(i,n) printf("%d%c",A[i]," \n"[i==m-1]);
				exit(0);
			}
		}
	}
	puts("passed all tests");
	return 1;
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	init();
	int T; scanf("%d",&T);
	while(T--) solve();
//	stress_test(100);
	return 0;
}
