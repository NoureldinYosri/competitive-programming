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


char buffer[1 << 20];
int n;
pi A[1 << 20];

pi canonize(){
	vector<char> ST;
	for(char *p = buffer;*p;p++){
		if(*p == '(') ST.pb('(');
		else if(ST.empty() || ST.back() != '(') ST.pb(')');
		else ST.pop_back();
	}
	vector<char> aux = ST;
	assert(unique(all(aux)) - aux.begin() <= 2);
	pi ret = mp(0,0);
	for(char c : ST)
		if(c != ')') break;
		else ret.xx++;
	reverse(all(ST));
	for(char c : ST)
		if(c != '(') break;
		else ret.yy++;
	return ret;
}

int main(){
	freopen("logger.out","w",stderr);
	#ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
	scanf("%d",&n);

	vi out;
	set<pi> frenge,comp,rem;

	loop(i,n){
		scanf("%s",buffer);
		A[i] = canonize();
		if(!A[i].xx) {
			frenge.insert(mp(A[i].yy,i));
			comp.insert(mp(0,i));
		}
		else rem.insert(mp(A[i].xx,i));
	}

	int ctr = 0;
	while(!frenge.empty()){
		auto p = *frenge.rbegin();
		int idx = p.yy;
		frenge.erase(p);
		comp.erase(mp(A[idx].xx,idx));
		ctr -= A[idx].xx;
		ctr += A[idx].yy;
		out.pb(idx + 1);
		//cerr << "take " << idx + 1 << endl;
		while(!comp.empty()){
			p = *comp.rbegin();
			idx = p.yy;
			if(p.xx > ctr){
				comp.erase(p);
				frenge.erase(mp(A[idx].yy,idx));
				rem.insert(p);
//				cerr << "move " << idx + 1 << " from usables to rem" << endl;
			}
			else break;
		}
		while(!rem.empty()){
			p = *rem.begin();
			if(p.xx <= ctr){
				rem.erase(p);
				idx = p.yy;
				frenge.insert(mp(A[idx].yy,idx));
				comp.insert(p);
//				cerr << "move " << idx + 1 << " from rem to usables " << endl;
			}
			else break;
		}
	}

	if(!rem.empty() || ctr != 0) puts("NO");
	else{
		puts("YES");
		for(int x : out) printf("%d ",x);
		puts("");
	}
	return 0;
}
