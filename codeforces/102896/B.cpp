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

string A, B;
vector<string> cand_list;
string alphabet;
vector<map<char, int>> trie;
vi end_cnt;
vi lookat;

int create_node(){
	int u = sz(trie);
	trie.emplace_back();
	end_cnt.push_back(0);
	return u;
}

int insert(const string & s){
	int u = 0;
	for(char c : s){
		if(!trie[u].count(c))
			trie[u][c] = create_node();
		u = trie[u][c];
	}
	return u;
}

void update(const string & s){
	int u = 0;
	for(char c : s){
		if(!trie[u].count(c))
			return;
		u = trie[u][c];
	}
//	cerr << "increase " << u << endl;
	end_cnt[u]++;
}


int get_count(const string & s){
	int u = 0;
	for(char c : s){
		if(!trie[u].count(c))
			return 0;
		u = trie[u][c];
	}
	return end_cnt[u];
}


string canonize(string s){
	char tmp = 'a';
	loop(i, sz(s)) {
		if(binary_search(all(alphabet), s[i])) continue;
		if(isupper(s[i])){
			char t = s[i];
			for(int j = i; j < sz(s); j++)
				if(s[j] == t)
					s[j] = tmp;
			tmp++;
		}
	}
	return s;
}


void read(string & s){
	static char buffer[50];
	scanf("%s", buffer);
	s = string(buffer);
}

char rev[128], val[128];

void save(string c, const string & to){
	char a = 'a';
//	cerr << c << " -> ";
	loop(i, sz(c)) {
		if(rev[(int)c[i]] != 0) c[i] = rev[(int)c[i]];
		else if(isdigit(c[i])){
			char t = c[i];
			for(int j = i; j < sz(c); j++)
				if(c[j] == t)
					c[j] = a;
			a++;
		}
	}
	update(c);
//	cerr << c << endl;
}


void use_assignment(const string & to){
	loop(i, 10) rev[i + '0'] = 0;
	loop(i, sz(to)) {
		val[(int)alphabet[i]] = to[i];
		rev[(int)to[i]] = alphabet[i];
	}
	int n = max(sz(A), sz(B));
	if(val[(int)A[0]] == '0' || val[(int)B[0]] == '0') return ;
	static string c;
	c.clear();
	int carry = 0;
	loop(i, n) {
		int v = carry;
		if(i < sz(A)) v += val[(int)A[sz(A) - 1 - i]] - '0';
		if(i < sz(B)) v += val[(int)B[sz(B) - 1 - i]] - '0';
		carry = 0;
		if(v > 9) {
			carry = 1;
			v -= 10;
		}
		c.push_back(v + '0');
	}
	if(carry) {
		assert(carry == 1);
		c.push_back('1');
	}
	reverse(all(c));
	save(c, to);
}

void bt(int i, string & to, int msk){
	if(i == sz(alphabet)){
		use_assignment(to);
		return;
	}
	for(int tm = msk; tm; tm ^= LSOne(tm)){
		int ls = LSOne(tm), b = bit_lg(ls);
		char old = to[i];
		to[i] = b + '0';
		bt(i + 1, to, msk ^ (1 << b));
		to[i] = old;
	}
}

void generate(){
	string to(sz(alphabet), '$');
	bt(0, to, (1 << 10) - 1);
}


int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	create_node();
	read(A);
	read(B);
	alphabet = A + B;
	sort(all(alphabet));
	alphabet.resize(unique(all(alphabet)) - alphabet.begin());
	if(sz(alphabet) > 10){
		puts("0");
		return 0;
	}
	int n; scanf("%d", &n);
	cand_list.resize(n);
	vector<string> ans;
	for(string & s : cand_list) {
		read(s);
		string t = canonize(s);
		lookat.push_back(insert(t));
//		cerr << t << ": " << lookat.back() << endl;
	}
	generate();
	loop(i, n) if(end_cnt[lookat[i]] == 1) ans.push_back(cand_list[i]);
	printf("%d\n", sz(ans));
	for(string & s : ans)
		puts(s.c_str());
	return 0;
}
