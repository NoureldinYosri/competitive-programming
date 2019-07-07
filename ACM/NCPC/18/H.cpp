#ifdef ACTIVE
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
#define loop(i,n) for(int i = 0;i < (n);i++)
#define range(i,a,b) for(int i = (a);i <= (b);i++)
#define all(A) A.begin(),A.end()
#define pb push_back
#define mp make_pair
#define sz(A) ((int)A.size())
#define vi vector<int>
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
using namespace std;

const int MAX = 100;
int L,M;
string name[MAX];
int P[MAX],C[MAX],T[MAX],R[MAX];
char buffer[1 << 20];

void read(int idx) {
	static vector<string> words;
	fgets(buffer,1 << 20,stdin);
	words.clear();
	char *token = strtok(buffer,",");
	for(;token;token = strtok(0,","))
		words.push_back(string(token));
	name[idx] = words[0];
	sscanf(words[1].c_str(),"%d",P + idx);
	sscanf(words[2].c_str(),"%d",C + idx);
	sscanf(words[3].c_str(),"%d",T + idx);
	sscanf(words[4].c_str(),"%d",R + idx);
}

ll get_area(int c,int t,int r,ll T) {
	T *= 10080;
	ll cnt = T/(t + r),rem = T%(t + r);
	ll area = (cnt * t) * c;
	area += min(rem,(ll)t)*c;
	return area;
}

bool usable(int c,int t,int r) {
	for(int T = 1;T <= 1000*100;T++) {
		ll area = get_area(c,t,r,T);
		if(area < T*(ll)L) return 0;
	}
	return 1;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	scanf("%d %d\n",&L,&M);
	vector<string> ans;
	int best = INT_MAX;
	loop(i,M){
		read(i);
		if(usable(C[i],T[i],R[i])) {
			if(P[i] < best) {
				ans.clear();
				best = P[i];
			}
			if(best == P[i]) ans.push_back(name[i]);
		}
	}
	if(ans.empty())
		ans.push_back("no such mower");
	for(string s : ans)
		printf("%s\n",s.c_str());
	return 0;
}
#endif
