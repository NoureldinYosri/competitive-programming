#ifdef ACTIVE
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
typedef std::vector<int> vi;
typedef std::pair<int,int> pi;
typedef std::vector<pi> vp;
typedef long long ll;
#define popcnt(x) __builtin_popcount(x)
#define LSOne(x) ((x) & (-(x)))
#define print(A,t) cerr << #A << ": "; copy(all(A),ostream_iterator<t>(cerr," " )); cerr << endl
#define prArr(A,n,t)  cerr << #A << ": "; copy(A,A + n,ostream_iterator<t>(cerr," " )); cerr << endl
#define PRESTDIO() cin.tie(0),cerr.tie(0),ios_base::sync_with_stdio(0)
#define what_is(x) cerr << #x << " is " << x << endl
#define bit_lg(x) (assert(x > 0),__builtin_ffsll(x) - 1)
const double PI = acos(-1);
template<class A,class B>
std::ostream& operator << (std::ostream& st,const std::pair<A,B> p) {
	st << "(" << p.first << ", " << p.second << ")";
	return st;
}
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;

vector<string> notes = {"A","A#","B","C","C#","D","D#","E","F","F#","G","G#"};
vi scale {2,2,1,2,2,2,1};

map<vector<string>,vector<string> > M;

void init(){
	for(int i = 0;i < sz(notes);i++) {
		int j = i;
		vector<string> V;
		V.push_back(notes[i]);
		for(int d : scale) {
			j = (j + d)%sz(notes);
			V.push_back(notes[j]);
		}
//		print(V,string);
		sort(all(V));
		V.resize(unique(all(V)) - V.begin());
		vector<string> aux;
		for(int msk = 1;msk < (1 << sz(V));msk++) {
			aux.clear();
			for(int j = 0;j < sz(V);j++)
				if(msk & (1 << j))
					aux.push_back(V[j]);
			M[aux].push_back(notes[i]);
		}
	}
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	init();
	int n; cin >> n;
	set<string> S;
	loop(i,n) {
		string s; cin >> s;
		S.insert(s);
	}
	vector<string> V{all(S)};
//	print(V,string);
	if(!M.count(V)) puts("none");
	else {
		vector<string> & res = M[V];
		loop(i,sz(res)) printf("%s%c",res[i].c_str()," \n"[i==sz(res)-1]);
	}
	return 0;
}
#endif
