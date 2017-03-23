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

const int MOD = 1e9 + 7;
const int MAX = 1 << 20;
int F[MAX];
int id[MAX][4];
int base[4],mod[4];
vi P{179424691,179425033,179425601,179426083,179424697,179425063,179425619,179426089,179424719,179425069,179425637,179426111,179424731,179425097,179425657,179426123,179424743,179425133,179425661,179426129,179424779,179425153,179425693,179426141,179424787,179425171,179425699,179426167,179424793,179425177,179425709,179426173,179424797,179425237,179425711,179426183,179424799,179425261,179425777,179426231,179424821,179425319,179425811,179426239,179424871,179425331,179425817,179426263,179424887,179425357,179425819,179426321,179424893,179425373,179425823,179426323,179424899,179425399,179425849,179426333,179424907,179425403,179425859,179426339,179424911,179425423,179425867,179426341,179424929,179425447,179425879,179426353,179424937,179425453,179425889,179426363,179424941,179425457,179425907,179426369,179424977,179425517,179425943,179426407,179424989,179425529,179425993,179426447,179425003,179425537,179426003,179426453,179425019,179425559,179426029,179426491,179425027,179425579,179426081,179426549};
int n,m; 
int A[MAX];
pi B[MAX];
pair<pi,pi> ID[MAX];

int mul(int x,int y,int mod){
	return (x*1LL*y)%mod;
}

int add(int x,int y,int mod){
	if(x >= mod) x %= mod; 
	if(y >= mod) y %= mod;	
	x += y;
	if(x >= mod) x -= mod;
	return x;
}

int main(){
	srand(time(0));
	loop(i,4) {
		base[i] = rand()%100;
		mod[i] = P[rand()%sz(P)];
	}
	F[0] = 1;
	loop(i,MAX-1) F[i + 1] = mul(F[i],i+1,MOD);
	
	scanf("%d %d",&m,&n);
	int cnt = 1;
	while(m--){
		int g,q = 0; scanf("%d",&g);
		loop(i,g) scanf("%d",A + i);
		sort(A,A + g);
		loop(i,g){
			int j = i;
			while(j < g && A[i] == A[j]) j++;
			B[q++] = mp(j - i,A[i]);
			i = j - 1;
		}
		sort(B,B + q);
		loop(i,q){
			int j = i;
			while(j < q && B[i].xx == B[j].xx) {
				int x = B[j].yy;				
				loop(k,4) {
					id[x][k] = mul(id[x][k],base[k],mod[k]);
					id[x][k] = add(id[x][k],cnt,mod[k]);
				}
				j++;
			}
			cnt++;
			i = j - 1;
		}
	}
	range(i,1,n) {
		ID[i-1] = mp(mp(id[i][0],id[i][1]),mp(id[i][2],id[i][3]));
	}
	sort(ID,ID + n);
	int ans = 1;
	loop(i,n){
		int j = i;
		while(j < n && ID[i] == ID[j]) j++;
		ans = mul(ans,F[j - i],MOD);
		i = j - 1;
	}
	cerr << ans << endl;
	cout << ans << endl;
	
	return 0;
}
