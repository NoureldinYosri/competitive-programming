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

struct node{
	int nameId,lId,rId;
	char op;
	bool isLeaf;
	node(){memset(this,0,sizeof *this);}
	node(int name) {
		memset(this,0,sizeof *this);
		nameId = name;
		isLeaf = 1;
	}
	node(int name,int a,int b,char c) {
		nameId = name;
		lId = a;
		rId = b;
		op = c;
		isLeaf = 0;
	}
};

char I[1000][30];
node* A[2000];
bool done[2000];
int newId[2000];
int n;
vector<string> ans;
map<string,int> id;
string S[2000]; int cnt;
map<string,int> memo;
set<string> forbidden;

void read(){
	scanf("%d",&n);
	loop(i,n) scanf("%s",I[i]);
}

int getId(const string & s) {
	if(id.count(s)) return id[s];
	int i = id[s] = cnt++;
	S[i] = s;
	A[i] = new node(i);
	return i;
}

int getDummyId(int x) {
	int y = cnt++;
	A[y] = A[x];
	return y;
}

string getNext(){
	static int q = 0;
	static char c = 'a';
	while(true){
		if(q >= 1000) {
			c++;
			q = 0;
		}
		string num = to_string(q);
		while(forbidden.count("a" + num) && num.size() <= 3)
			num = "0" + num;
		if(num.size() == 4) {
			q++;
			continue;
		}
		string s = "a" + num;
		forbidden.insert(s);
		return s;
	}
}

void dfs(int i,bool isRoot) {
	if(done[i]) return;
	node* cur = A[i];
	if(cur->isLeaf) {
		done[i] = 1;
		newId[i] = cur->nameId;
		return ;
	}
	dfs(cur->lId,0);
	dfs(cur->rId,0);
	string exp = S[newId[cur->lId]] + cur->op + S[newId[cur->rId]];
	if(memo.count(exp)) newId[i] = memo[exp];
	else {
		string t = "res";
		if(!isRoot) t = getNext();
		int ti = getId(t);
		newId[i] = memo[exp] = ti;
		ans.push_back(t + "=" + exp);
	}
}


void getCutPoints(char *S,int & j,int & k,string & s,string & L,string & R,char & c) {
	static char buffer[50];
	strcpy(buffer,S);
	j = k = -1;
	int len = strlen(S);
	loop(i,len) {
		if(S[i] == '=') j = i;
		else if(!isalnum(S[i])) k = i;
	}
	assert(j != -1);
	if(k != -1) {
		c = buffer[k];
		buffer[k] = 0;
		R = string(buffer + k + 1);
	}
	buffer[j] = 0;
	s = string(buffer);
	L = string(buffer + j + 1);
}

int main(int argc,char **argv){
#ifdef HOME
	freopen("in.in","r",stdin);
#endif
	read();
	loop(i,n) {
		int j,k;
		string s,L,R;
		char c;
		getCutPoints(I[i],j,k,s,L,R,c);
		int si = getId(s);
		forbidden.insert(s);
		if(k == -1) {
			string & t = L;
			int ti = getId(t);
			A[si] = A[ti];
			forbidden.insert(t);
		}
		else {
			int li = getId(L),ri = getId(R);
			if(si == li) li = getDummyId(li);
			if(si == ri) ri = getDummyId(ri);
			A[si] = new node(si,li,ri,c);
			forbidden.insert(L);
			forbidden.insert(R);
		}
	}

	if(!id.count("res")) cout << 0 << endl;
	else {
		dfs(id["res"],1);
		int i = id["res"];
		if(ans.empty() && newId[i] != i)
			ans.push_back("res=" + S[newId[i]]);
		printf("%d\n",sz(ans));
		for(string s : ans)
			printf("%s\n",s.c_str());
	}
	return 0;
}
