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
#define popcnt(x) __builtin_popcount(x)
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

const int MAXT = 100,MAXN = 20;
vi upperN {2,4,10,20,100,200,300,500,800,998,1000};
vi probN { 0,2,8 ,25,30 ,10 ,5  ,5  ,5  ,0  ,10};



const int million = 1000*1000,billion = million*1000;
const int hundredthousand = 100*1000;
const string lowercase = "abcdefghijklmnopqrstuvwxyz",uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ",digits = "0123456789";


ll BigRand(ll mod){
	ll a = rand()%mod;
	ll b = rand()%mod;
	return ((a * b)%mod + mod)%mod;
}

ll randint(ll s,ll e){
	if(s == e) return s;
	ll len = e - s + 1;
	len = min(len,100*1000LL);
	return s + BigRand(len);
}

int getWeightedRandom(vi & W){
	int sum = 0,r = randint(1,100);
	for(int i = 0;i < sz(W);i++){
		sum += W[i];
		if(r <= sum) return i;
	}
	return sz(W)-1;
}

string create_string(int n,string alpha = lowercase){
	string ret ;
	loop(i,n) ret.pb(alpha[randint(0,sz(alpha)-1)]);
	return ret;
}

vi getRandomDistinctList(int len,int s ,int e){
	vi ret; ret.reserve(len);
	--s;
	for(int i = 0,r = len;i < len;i++,r--){
		int x = randint(s+1,e - r +1);
		ret.pb(x);
		s = x;
	}
	random_shuffle(all(ret));
	return ret;
}

int getRandomFromList(vi & V){
	return V[randint(0,sz(V)-1)];
}

vi getRandomDistinctFromList(int cnt,vi & V,bool shuffle = 1){
	vi IDX = getRandomDistinctList(cnt,0,sz(V)-1);
	vi ret; ret.reserve(cnt);
	for(int i : IDX) ret.pb(V[i]);
	if(shuffle) random_shuffle(all(ret));
	return ret;
}





int main(int argc,char **argv){
	int seed = 0;
	if(argc > 1) sscanf(argv[1],"%d",&seed);
	srand(seed);

	int T = MAXT;

	printf("%d\n",T);
	for(int t = 1;t <= T;t++){
		int mode = getWeightedRandom(probN);
		int n = randint(upperN[mode-1],upperN[mode]);
		
	}
	return 0;
}



