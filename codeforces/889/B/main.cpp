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

const int MAX = 3*100*1000 + 10;
char buffer[MAX];
string S[MAX];
int n;
int cnt[128];
int prv[128],nxt[128];


bool isSet(string & s) {
	set<char> S{all(s)};
	return sz(S) == sz(s);
}

void compress(){
	sort(S,S + n,[](const string & a,const string & b) {
		return sz(a) < sz(b);
	});
	set<string> aux;
	loop(t,n){
		string s = S[t];
		for(int i = 0;i < sz(s);i++){
			string u ;
			for(int j = i;j < sz(s);j++) {
				u += s[j];
				aux.erase(u);
			}
		}
		aux.insert(s);
	}


	copy(all(aux),S);
	n = sz(aux);
}

string solve(){
	loop(i,n) {
		if(!isSet(S[i]))
			return "NO";
	}

	compress();

	int ctr = 0;
	loop(i,n) {
		for(char c : S[i]) {
			int x = c;
			ctr += !cnt[x];
			cnt[x]++;
		}
	}

	loop(i,n){
		string s = S[i];
		for(int j = 0;j + 1 < sz(s);j++){
			int x = s[j],y = s[j + 1];
			if(nxt[x] && nxt[x] != y) return "NO";
			if(prv[y] && prv[y] != x) return "NO";
			nxt[x] = y;
			prv[y] = x;
		}
	}


	int m = 0;
	for(int i = 'a';i <= 'z';i++) if(cnt[i]){
		if(!prv[i]){
			int cur = i;
			while(cur) {
				buffer[m++] = cur;
				cur = nxt[cur];
			}
		}
	}
	buffer[m] = 0;
	if(m != ctr) return "NO";
	return string(buffer);
}


int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n){
		scanf("%s",buffer);
		S[i] = string(buffer);
	}

	puts(solve().c_str());

	return 0;
}
