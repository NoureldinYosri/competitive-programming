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

const int MAX = 100*1000 + 10;
char buffer[10];
string name[MAX];
int type[MAX],n,e;
vector<pair<string,string> > ans;

bool read_num(const string & s,int & x){
	x = 0;
	for(char c : s) {
		if('0' <= c && c <= '9') x = x*10 + c - '0';
		else return 0;
	}
	if(x == 0 && sz(s) != 1) return 0;
	if(s[0] == '0') return 0;
	return 1;
}

int get_num(const string & s){
	int x;
	assert(read_num(s,x));
	return x;
}

void do_count(int target,int s,int e,vi & inRange,vi & inOtherRange,vi & other){
	loop(i,n) {
		if(type[i] == target) {
			int x;
			if(read_num(name[i],x)) {
				if(s <= x && x <= e) inRange.pb(i);
				else if(x > n) other.pb(i);
				else inOtherRange.pb(i);
			}
			else other.pb(i);
		}
	}
	sort(all(inRange),[](const int & a,const int & b){
		return get_num(name[a]) < get_num(name[b]);
	});
	sort(all(inOtherRange),[](const int & a,const int & b){
		return get_num(name[a]) < get_num(name[b]);
	});
}

void get_free(set<int> & S,int s,int e,vi & A,vi & B) {
	range(i,s,e) S.insert(i);
	//print(S,int);
	for(int x : A) {
		auto p = S.find(get_num(name[x]));
	//	cerr << "erase " << name[x] << endl;
		assert(p != S.end());
		S.erase(p);
	}
	for(int x : B) {
		auto p = S.find(get_num(name[x]));
	//	cerr << "erase " << name[x] << endl;
		assert(p != S.end());
		S.erase(p);
	}

}

bool work(set<int> & S,vi & A,vi & B,set<int> & O,bool yes = 0) {
	//print(S,int);
	bool ret = 0;
	while(!A.empty() && !S.empty()) {
		int x = A.back() ;
		A.pop_back();
		ans.pb(mp(name[x],to_string(*S.begin())));
//		cerr << "move " << name[x] << " " << to_string(*S.begin()) << endl;
		O.insert(get_num(name[x]));
//		print(O,int);
		S.erase(S.begin());
		ret = 1;
	}
	if(yes){
		while(!B.empty() && !S.empty()) {
			int x = B.back() ;
			B.pop_back();
			ans.pb(mp(name[x],to_string(*S.begin())));
//			cerr << "move " << name[x] << " " << to_string(*S.begin()) << endl;
			S.erase(S.begin());
			ret = 1;
		}
	}
//	cerr << "========================" << endl;
	return ret;
}

string get_aux(){
	set<int> S;
	loop(i,n){
		int x;
		if(read_num(name[i],x)) {
			S.insert(x);
		}
	}
	int i;
	for(i = n+1;;i++)
		if(S.find(i) == S.end())
			break;
	return to_string(i);
}

void work2(vi & A,vi & B) {
	assert(sz(A) == sz(B));
	if(A.empty()) return;
	string aux = get_aux();
	int x = A.back(),y,pos = 0; A.pop_back();
	ans.pb(mp(name[x],aux));
	while(!A.empty() || !B.empty()){
		if(pos == 0) {
			y = B.back();
			B.pop_back();
		}
		else {
			y = A.back();
			A.pop_back();
		}
		ans.pb(mp(name[y],name[x]));
		x = y;
		pos ^= 1;
		//cerr << "move " << name[x] << " " << aux << endl;
		//cerr << "move " << name[y] << " " << name[x] << endl;
		//cerr << "move " << aux << " " << name[y] << endl;
	}
	ans.pb(mp(aux,name[x]));
}

int main(){
	#ifdef HOME
		freopen("in.in", "r", stdin);
	#endif
	scanf("%d",&n);
	loop(i,n){
		scanf("%s %d",buffer,type + i);
		e += type[i];
		name[i] = string(buffer);
	}
	vi AinRange,AinOtherRange,Aother;
	vi BinRange,BinOtherRange,Bother;
	do_count(1,1,e,AinRange,AinOtherRange,Aother);
	do_count(0,e+1,n,BinRange,BinOtherRange,Bother);
	set<int> up,down;
	get_free(up,1,e,AinRange,BinOtherRange);
	get_free(down,e+1,n,BinRange,AinOtherRange);
	while(work(up,AinOtherRange,Aother,down) || work(down,BinOtherRange,Bother,up));
	work(up,AinOtherRange,Aother,down,1);
	work(down,BinOtherRange,Bother,up,1);
	work2(AinOtherRange,BinOtherRange);

	assert(AinOtherRange.empty());
	assert(Aother.empty());
	assert(BinOtherRange.empty());
	assert(Bother.empty());

	printf("%d\n",sz(ans));
	for(auto p : ans) printf("move %s %s\n",p.xx.c_str(),p.yy.c_str());
	return 0;
}
