#ifdef DEBUG
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

int loc[10];
int t,c;

void Move(int i) {
	loc[i]++;
	if(loc[i] >= t) loc[i] = (loc[i] - t)%c + t;
}

void answer(){
	vector<string> V;
	bool taken[10] = {0};
	for(int d = 0;d < 10;d++) if(!taken[d]){
		string s;
		for(int i = d;i < 10;i++)
			if(loc[i] == loc[d]){
				s += (char)('0' + i);
				taken[i] = 1;
			}
		V.push_back(s);
	}
	cout << sz(V);
	for(string s : V) cout << " " << s;
	cout << endl;
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	srand(argv[1][0]);
	t = rand()%5 + 1;
	c = rand()%5 + 1;
	while(1) {
		string q;
		getline(cin,q);
		vector<string> tokens;
		char buffer[1000];
		strcpy(buffer,q.c_str());
		for(char *token = strtok(buffer," \n");token;token = strtok(0," \n")) {
			tokens.push_back(string(token));
		}
		if(tokens.size() <= 1) break;
		for(int i = 1;i < sz(tokens);i++)
			for(char c : tokens[i])
				Move(c - '0');
		answer();
	}
	bool y = 1;
	loop(i,10) y &= loc[i] == t;
	cerr << y << endl;
	return 0;
}
#endif
