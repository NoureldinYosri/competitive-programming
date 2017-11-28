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

const int MAX = 2500000 + 10;

char minID[MAX],maxID[MAX],minPower[MAX],maxPower[MAX];
int n;

void workMin(){
	if(n == 1) {
		strcpy(minID,"9");
		strcpy(minPower,"-72");
		return;
	}
	if(n == 2) {
		strcpy(minID,"19");
		strcpy(minPower,"-63");
		return;
	}
	loop(i,n-3) minPower[i] = '9';
	minPower[n-3] = '2';
	minPower[n-2] = '7';
	minPower[n-1] = 0;
	minID[0] = '1';
	loop(i,n-2) minID[i+1] = '0';
	minID[n-1] = '9';
	maxID[n] = 0;
}

ll getScore() {
	ll score = 0;
	loop(i,n) {
		int d = maxID[i] - '0';
		score += d*d;
	}
	return score;
}

void subtract(char *score) {
	if(n <= 3) {
		ll id,sq;
		sscanf(maxID,"%lld",&id);
		sscanf(score,"%lld",&sq);
		id -= sq;
		sprintf(maxPower,"%lld",id);
		return;
	}
	int m = strlen(score);
	assert(n > m);
	assert(m <= 15);
	ll id,sq;
	sscanf(score,"%lld",&sq);
	sscanf(maxID + n - m - 1,"%lld",&id);
	id -= sq;
	assert(id >= 0);
	strcpy(maxPower,maxID);
	sprintf(maxPower+n-m-1,"%lld",id);
}

void workMax(){
	if(n == 1) {
		strcpy(maxID,"1");
		strcpy(maxPower,"0");
		return;
	}
	loop(i,n-2) maxID[i] = '9';
	maxID[n-2] = '5';
	maxID[n-1] = '0';
	maxID[n] = 0;
	char score[20] ;
	sprintf(score,"%lld",getScore());
	subtract(score);
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	workMin();
	workMax();
	printf("%s\n",maxID);
	printf("%s\n",minID);
	printf("%s\n",maxPower);
	printf("%s\n",minPower);
	return 0;
}
