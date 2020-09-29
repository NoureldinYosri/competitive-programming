#pragma GCC optimize ("O3")
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
using namespace std;

const int MAXST = 22*50*1000;
int n;
char txt[200*1000];
string I[50*1000];
map<char, int> trie[MAXST];
int ts;
pi ID[50*1000];
map<pi, int> T[MAXST];

void insert(int i){
	int cur = 0;
	for(char *ptr = txt; *ptr; ptr++){
		int nxt = trie[cur][*ptr];
		if(nxt == 0) nxt = trie[cur][*ptr] = ++ts;
		cur = nxt;
		T[cur][ID[i]] = i;
	}
}

const string special = ".,?";
const string i2s[] = {"", "", "abc", "def",
						"ghi", "jkl", "mno", 
						"pqrs", "tuv", "wxyz"
						};
map<char, char> c2i; 
void init(){
	for(int i = 2; i < 10; i++)
		for(char c : i2s[i])
			c2i[c] = i + '0'; 
}

string ans;
void replace(pi newId, int i){
	int cur = 0;
	for(char c : ans){
		c = c2i[c];
		cur = trie[cur][c];
		T[cur].erase(ID[i]);
		T[cur][newId] = i;
	}	
	ID[i] = newId;
}


int main(){
	freopen("t9.in", "r", stdin);
#ifndef HOME
	freopen("t9.out", "w", stdout);
#endif
	init();
	int n; scanf("%d", &n);
	loop(i, n){
		int F; scanf("%s %d", txt, &F);
		ID[i] = pi(F, -i);
		I[i] = string(txt);
		for(char *ptr = txt; *ptr; ptr++){
//			cerr << *ptr << " -> '" << c2i[*ptr] << "'" << endl;
			*ptr = c2i[*ptr];
		}
//		cerr << txt << endl;
		insert(i);
	}
	for(int z = 1; scanf("%s", txt) == 1; z++){
		int cur = 0;
		char *ptr;
		for(ptr = txt; *ptr; ptr++){
			if(*ptr == '*' || *ptr == '1') break;
			cur = trie[cur][*ptr];
		}
		assert(cur);
		auto itr = T[cur].rbegin();
		while(*ptr == '*'){
			itr++;
			ptr++;
		}
		ans = I[itr->second];
		int i = itr->second;
		replace(pi(ID[i].first + 1, z), i);
		if(*ptr == '1'){
			int z = 0;
			ptr++;
			while(*ptr == '*') z++, ptr++;
			assert(z < 3);
			ans.push_back(special[z]);
		}
		printf("%s ", ans.c_str()); 
	}
	return 0;
}
