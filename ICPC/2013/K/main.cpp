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

struct node{
	char c;
	node *l,*r;
};

void preorder(node *root,string & s){
	if(!root) return;
	s.pb(root->c);
	preorder(root->l,s);
	preorder(root->r,s);
}
void inorder(node *root,string & s){
	if(!root) return;
	inorder(root->l,s);
	s.pb(root->c);
	inorder(root->r,s);
}
void postorder(node *root,string & s){
	if(!root) return;
	postorder(root->l,s);
	postorder(root->r,s);
	s.pb(root->c);
}

map<string,pair<string,string> > func;



bool optimize(map<string,string> M,char c,node *&root){
	cerr << "there" << endl;
	assert(sz(M) == 1 || sz(M) == 2);
	assert(M.find("in") == M.end());

	return 1;
}

bool split(string s,char c,string & L,string & R) {
	int i = 0;
	for(;i < sz(s) && s[i] != c;i++);
	if(i == sz(s)) return 0;
	L = s.substr(0,i);
	R = s.substr(i+1,sz(s)-i);
	return 1;
}

bool setSame(string a,string b) {
	sort(all(a));
	sort(all(b));
	return a == b;
}

bool validate(map<string,string>,node*&);

bool work(map<string,string> M,node *&root,char c1,string L,string R) {
	if(M.count("pre")) {
		string s = M["pre"];
		s = s.substr(1,sz(s)-1);
		string preL = s.substr(0,sz(L));
		string preR = s.substr(sz(L),sz(s)-sz(L));
		if(!setSame(L , preL)) return 0;
		if(!setSame(R , preR)) return 0;
	}
	if(M.count("post")){
		string s = M["post"];
		s = s.substr(0,sz(s)-1);
		string preL = s.substr(0,sz(L));
		string preR = s.substr(sz(L),sz(s)-sz(L));
		if(!setSame(L , preL)) return 0;
		if(!setSame(R , preR)) return 0;
	}
	root = new node();
	root->c = c1;
	vector<pair<string,string> > toApply;
	map<string,string> tM;
	if(!L.empty()){
		for(auto p : M) {
			string s = p.yy;
			if(p.xx == "pre") s = s.substr(1,sz(L));
			else if(p.xx == "post") s = s.substr(0,sz(L));
			else s = L;
			toApply.push_back(mp(func[p.xx].xx,s));
		}
		sort(all(toApply));
		toApply.resize(unique(all(toApply)) - toApply.begin());
		for(auto p : toApply) {
			string f = p.xx ,s = p.yy;
			if(tM.find(f) != tM.end()) return 0;
			tM[f] = s;
		}
		if(!validate(tM,root->l)) return 0;
	}
	toApply.clear();
	tM.clear();
	if(!R.empty()){
		for(auto p : M) {

			string s = p.yy;
			if(p.xx == "pre") s = s.substr(1 + sz(L),sz(R));
			else if(p.xx == "post") s = s.substr(sz(L),sz(R));
			else s = R;
			toApply.push_back(mp(func[p.xx].yy,s));
		}
		sort(all(toApply));
		toApply.resize(unique(all(toApply)) - toApply.begin());
		for(auto p : toApply) {
			string f = p.xx ,s = p.yy;
			if(tM.find(f) != tM.end()) return 0;
			tM[f] = s;
		}
		if(!validate(tM,root->r)) return 0;
	}
	return 1;
}

map<map<string,string> ,pair<bool,node*> > memo;

bool validate(map<string,string> M,node *&root) {
	if(memo.find(M) != memo.end()) {
		root = memo[M].yy;
		return memo[M].xx;
	}

	pair<bool,node*> & ret = memo[M];
	ret.xx = 0;
	root = 0;
	int c1 = 0,c2 = 0;

	if(M.count("pre")) c1 = M["pre"][0];
	if(M.count("post")) c2 = M["post"].back();

	if(!c1 && !c2) {
		assert(M.count("in"));
		c1 = *min_element(all(M["in"]));
	}
	if(!c1) swap(c1,c2);
	vector<pair<char,pair<string,string> > >factory;
	if(M.find("in") == M.end()) {
		string s ;
		if(M.count("pre")) {
			s = M["pre"];
			s = s.substr(1,sz(s)-1);
		}
		else {
			assert(M.count("post"));
			s = M["post"];
			s = s.substr(0,sz(s)-1);
		}
		for(int i = 0;i < sz(s);i++) {
			string L = s.substr(0,i),R = s.substr(i,sz(s)-i);
			factory.pb(mp(c1,mp(L,R)));
		}
		factory.pb(mp(c1,mp(s,"")));
	}
	else{
		string L,R;
		if(!split(M["in"],c1,L,R)) return 0;
		factory.pb(mp(c1,mp(L,R)));
	}
	vector<string> val;
	for(auto fac : factory) {
		char c = fac.xx;
		string L = fac.yy.xx,R = fac.yy.yy;
		node *tmpRoot;
		if(work(M,tmpRoot,c,L,R)) {
			vector<string> tmp(3);
			preorder(tmpRoot,tmp[0]);
			inorder(tmpRoot,tmp[1]);
			postorder(tmpRoot,tmp[2]);
			if(val.empty() || tmp < val) {
				val = tmp;
				root = tmpRoot;
			}
		}
	}
	if(val.empty()) return 0;
	ret.xx = 1;
	ret.yy = root;
	return 1;
}

int key(string s){
	if(s == "pre") return 0;
	if(s == "in") return 1;
	return 2;
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	map<string,string> M;
	vector<string> name{"pre","in","post"};
	for(string f : name) {
		string s ;
		cin >> s;
		M[f] = s;
	}

//	int ctr = 0;
	vector<pair<vector<string>,vector<string> > > ans;
//	vector<string> val;
//	vector<string> target {"pre","post","in","post","in","pre"};

	vi aux;
	loop(i,6) aux.pb(i/2);
	do{
		memo.clear();
		vector<string> ord = vector<string>(6);
		loop(i,6) ord[i] = name[aux[i]];
		for(int i = 0;i < 3;i++)
			func[name[i]] = mp(ord[2*i],ord[2*i+1]);
		node *root = 0;
		if(validate(M,root)){
			assert(root != NULL);
			vector<string> tmp(3);
			preorder(root,tmp[0]);
			inorder(root,tmp[1]);
			postorder(root,tmp[2]);
			ans.pb(mp(ord,tmp));
		}
	}while(next_permutation(all(aux)));


	assert(!ans.empty());

	loop(j,sz(ans)) {
		vector<string> ord = ans[j].xx,val = ans[j].yy;
		loop(i,6) {
			ord[i][0] = toupper(ord[i][0]);
			cout << ord[i];
			if(i+1 < 6) cout << " ";
			else cout << endl;
		}
		for(string s : val) cout << s << endl;
//		if(j+1 < sz(ans)) cout << endl;
	}
	return 0;
}
