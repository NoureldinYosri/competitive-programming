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

char C[20],out[20];
int N[20];
int L1,L2;
vp usable[10];
vi db[10],other[10][10];

void init(){
	loop(i,10) loop(j,10) {
		int s = (i + j)%10;
		usable[s].pb(mp(i,j));
		other[i][s].pb(j);
	}
	loop(i,10) db[(i+i)%10].pb(i);
/*	loop(i,10) {
		cerr << i << " : " << endl;
		print(db[i],int);
		for(auto p : usable[i]) prp(p);
		cerr << endl;
	}
*/
}

int K;

bool possible(){
	int i = 0,j = L2 - K;
	int r = 0,know = 1,s,cur;
	while(i < L2) {
		cur = C[i] - '0';
		if(N[i] != -1 && N[j] != -1) {
			s = N[i] + N[j];
			if(know) {
				s += r;
				if(s%10 != cur) return 0;
				r = s / 10;
			}
			else {
				know = 0;
				if(s%10 != cur && (s + 1)%10 != cur) return 0;
			}
		}
		know = 0;
		i++;
		j++;
		if(j == L2) j = 0;
	}
	return 1;
}

bool bt(short i,short j,bool r) {
	if(!possible()) return 0;
	if(j == L2) j = 0;
	if(N[L2-1] == 0) return 0;
	/*
	bool debug = N[0] == 7 && N[L2-K] == 9;
	if(debug) {
		cerr << "===============================" << endl;
		cerr << "highlight" << endl;
		cerr << "===============================" << endl;
	}
	cerr << i << " " << j << endl;
	prArr(N,L2,int);
	cerr << r << endl;
	*/
	if(i == L2) {
		if(i == L1) return r == 0;
		else return r == C[L2] - '0';
	}
	short s,cur = C[i] - '0',tr = cur - r;
	if(tr < 0) tr += 10;
	if(N[i] != -1 && N[j] != -1) {
		s = N[i] + N[j] + r;
		if(s%10 != C[i] - '0') return 0;
		else return bt(i+1,j+1,s/10);
	}
	if(i == j) {
		for(int x : db[tr]) {
			s = 2*x + r;
			assert(s%10 == C[i] - '0');
			N[i] = x;
			if(bt(i+1,j+1,s/10)) return 1;
		}
		N[i] = -1;
		return 0;
	}
	if(N[i] != -1 || N[j] != -1) {
		short c = (N[i] == -1) ? i : j;
		short o = i + j - c;
		for(auto x : other[N[o]][tr]) {
			N[c] = x;
			s = x + N[o] + r;
			if(bt(i+1,j+1,s/10)) return 1;
		}
		N[c] = -1;
		return 0;
	}
	for(auto p : usable[tr]) {
		N[i] = p.xx;
		N[j] = p.yy;
		s = p.xx + p.yy + r;
		if(bt(i+1,j+1,s/10)) return 1;
	}
	N[i] = N[j] = -1;
	return 0;
}

bool solve(int L,int K) {
	memset(N,-1,sizeof N);
	L2 = L;
	if(L2 >= K && bt(0,L2-K,0)) {
		loop(i,L2) out[L2-1-i] = N[i] + '0';
		return 1;
	}
	return 0;
}

int main(){
	freopen("coding.in", "r", stdin);
	freopen("coding.out", "w", stdout);

	init();
	scanf("%s %d",C,&K);
	L1 = strlen(C);
	reverse(C,C + L1);

	if(!solve(L1,K) && !solve(L1 - 1,K))
		strcpy(out,"failed :(");
	puts(out);
	//cerr << out << endl;
	return 0;
}
