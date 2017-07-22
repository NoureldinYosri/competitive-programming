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

const int MAX = 8000 + 10;
char I[MAX];
int n;
vi smallP { 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73};
vi bigP{973501687, 979190873, 972765169, 962474831, 976714393, 979097809, 968106283, 977383639, 965782747, 972313789, 967404107, 974263201, 978940031, 963054383, 964554827, 962958977, 972112651, 982236889, 978524933, 982188197, 962420743, 979900177, 975462149, 973602013, 980952491, 970774003, 966357419, 976625681, 963040019, 980450173, 976309153, 972910223, 976526429, 970508741, 963068017, 979569649, 980963443, 972966857, 978455249, 970720189, 976665073, 977168053, 962367881, 964504559, 965704799, 979968601, 968721791, 982322837, 980000971, 980208373};
int H[MAX][2];
int base[2],mod[2],POW[2][MAX];
int cnt[MAX][MAX],dp[MAX];
vector<pair<int,pi> > cost_div[MAX];
int len[MAX];
int add(int x,int y,int m){
	x += y;
	if(x >= m) x -= m;
	if(x < 0) x += m;
	return x;
}
int mul(int x,int y,int m){
	return (x*1LL*y)%m;
}

void init(){
	srand(time(0));
	srand(0);
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
	loop(k,2) {
		POW[k][0] = 1;
		loop(q,MAX-1) POW[k][q + 1] = mul(POW[k][q],base[k],mod[k]);
	}
}
int get_len(int v){
	if(v < 10) return 1;
	if(v < 100) return 2;
	if(v < 1000) return 3;
	return 4;
}

void get_hash(int s,int l,int *h){
	copy(H[s + l - 1],H[s + l - 1] + 2,h);
	if(s){
		loop(k,2) h[k] = add(h[k],-mul(H[s-1][k],POW[k][l],mod[k]),mod[k]);
	}
}

bool valid(int s,int l){
	int h1[2],h2[2];
	get_hash(s,l,h1);
	get_hash(s+l,l,h2);
	prArr(h1,2,int);
	prArr(h2,2,int);
	return h1[0] == h2[0] && h1[1] == h2[1];
}

int main(){
	#ifndef ONLINE_JUDGE
		freopen("in.in", "r", stdin);
	#endif
	init();
	scanf("%s",I);
	n = strlen(I);
	int h[2] = {0};
	for(int s = 0;s < n;s++) {
		loop(k,2) h[k] = add(mul(h[k],base[k],mod[k]),I[s] - 'a' + 1,mod[k]);
		copy(h,h + 2,H[s]);
	}
	for(int l = 1;l <= n;l++)
		for(int s = n-l;s >= 0;s--){
			cnt[s][l] = 1;
			if(s + 2*l <= n) {
				int h1[2],h2[2];
				get_hash(s,l,h1);
				get_hash(s+l,l,h2);
				if(h1[0] == h2[0] && h1[1] == h2[1])
					cnt[s][l] = 1 + cnt[s + l][l];
			}
		}

	loop(i,MAX) len[i] = get_len(i);
	for(int i = 1;i < MAX;i++){
		for(int j = 1;j <= i;j++)
			if(i%j == 0)
				cost_div[i].pb(mp(j + len[i/j],mp(j,i/j)));
		sort(all(cost_div[i]));
	}
	for(int s = n-1;s >= 0;s--){
		dp[s] = len[n] + n;
		for(int l = 1;s+l <= n;l++){
			for(auto p : cost_div[l]) {
				if(cnt[s][p.yy.xx] >= p.yy.yy) {
					dp[s] = min(dp[s],dp[s + l] + p.xx);
					break;
				}
			}
		}
	}
	printf("%d\n",dp[0]);
	return 0;
}
