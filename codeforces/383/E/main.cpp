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

const int NUMBITS = 24,MAX = 1 << NUMBITS;
int n;
int f[MAX];
int S[MAX];
int g[MAX];

void SOS(){
	for(int b = 0;b < NUMBITS;b++){
		for(int i = 0;i < MAX;i++) {
			if(i & (1 << b)) f[i] += f[i ^ (1 << b)];
		}
	}
	for(int i = 0;i < MAX;i++)
		g[i] += f[i];
}

string toString(int msk) {
	string s;
	int i = 0;
	while(msk) {
		int b = LSOne(msk);
		while((1 << i) != b) i++;
		s += 'a' + i;
		msk ^= b;
	}
	return s;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n) {
		char buffer[4]; scanf("%s",buffer);
		int m = strlen(buffer);
		sort(buffer,buffer + m);
		m = unique(buffer,buffer + m) - buffer;
		buffer[m] = 0;
		for(char c : string(buffer))
			S[i] |= 1 << (c - 'a');
	}

	for(int i = 0;i < n;i++){
		string s = toString(S[i]);
		for(char c : s)
			f[1 << (c - 'a')]++;
	}
	SOS();

	memset(f,0,sizeof f);
	for(int i = 0;i < n;i++){
		string s = toString(S[i]);
		for(int j = 0;j < sz(s);j++)
			for(int k = 0;k < j;k++) {
				int a = s[j] - 'a',b = s[k] - 'a';
				f[(1 << a) | (1 << b)]--;
			}
	}
	SOS();

	memset(f,0,sizeof f);
	for(int i = 0;i < n;i++){
		string s = toString(S[i]);
		if(sz(s) == 3) {
			int msk = 0;
			for(char c : s)
				msk |= 1 << (c - 'a');
			f[msk]++;
		}
	}
	SOS();


	ll ans = 0;
	loop(i,MAX) ans ^= g[i] * 1LL * g[i];
	cout << ans << endl;
	return 0;
}
