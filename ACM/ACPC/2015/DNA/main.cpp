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

char str[1 << 20];
int Z[1 << 20],n;
string DNA = "ACGT";
int lg[1 << 4];
vi dont[1 << 20];



void get_Z(string & s,vector<int> & Z){
	int n = s.length();
	Z = vector<int>(n,0);
	int L = 0, R = 0;
	for (int i = 1; i < n; i++)
  		if (i > R) {
   			L = R = i;
   			while (R < n && s[R-L] == s[R]) R++;
    		Z[i] = R-L; R--;
  		}
  		else {
    		if (Z[i - L] < R - i + 1) Z[i] = Z[i - L];
    		else {
      			L = i;
      			while (R < n && s[R - L] == s[R]) R++;
      			Z[i] = R-L; R--;
    		}
  		}
}


bool solve(){
	if(Z[0] != n) return 0;
	loop(i,n) if(Z[i] + i > n) return 0;

	loop(i,n) dont[i].clear();
	str[0] = 'A';

	set<pi> R;
	for(int i = 1;i < n;i++) {
		while(!R.empty() && R.begin()->xx < i) R.erase(R.begin());
		if(Z[i]) R.insert(mp(i + Z[i] - 1,i));
		dont[i + Z[i]].pb(Z[i]);

		set<char> aux({all(DNA)});
		for(int x : dont[i])
			aux.erase(str[x]);

//		print(dont[i],int);
//		print(aux,char);

		if(aux.empty()) return 0;

		char c = *aux.begin();
		if(!R.empty()) {
			int x = R.begin()->yy;
			int p = i - x;
			c = str[p];
			if(aux.find(c) == aux.end()) return 0;
		}
		str[i] = c;
//		cerr << str << endl;
	}
	str[n] = 0;
	string s (str);
	vi ZA;
	get_Z(s,ZA);
	for(int i = 1;i < n;i++)
		if(Z[i] != ZA[i])
			return 0;
	return 1;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	loop(i,4) lg[1 << i] = i;
	int T; scanf("%d",&T);
	range(t,1,T){
		scanf("%d",&n);
		loop(i,n) scanf("%d",Z + i);
		if(!solve()) strcpy(str,"Impossible");
		puts(str);
	}

	return 0;
}
