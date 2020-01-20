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



string txt;

struct quanta{
	int sum;
	int mx,mx_abs,mn;
	bool valid;
	friend ostream& operator << (ostream & st, const quanta & q){
		st << "(" << q.sum << ", " << q.mx << ", " << q.valid << ")";
		return st;
	}
};

vector<quanta> pref;
deque<quanta> suff;
quanta empty ({0,0,0,0,1});
char eps = '-';

quanta merge(quanta prv, char c){
	//cout << "pref merge of " << prv << " " << c << endl;
	if(c == eps) return prv;
	quanta ret(prv);
	if(c == '(') {
		ret.sum++;
		ret.mn++;
	}
	else {
		ret.sum--;
		ret.mn = min(-1, ret.mn - 1);
	}
	ret.mx_abs = max(ret.mx_abs, -ret.sum);
	ret.mx = max(ret.mx, ret.sum);
	if(ret.sum < 0) ret.valid = 0;
	return ret;	
}

quanta merge(char c, quanta nxt){
	//cout << "suff merge of " << c << " " << nxt << endl;
	if(c == eps) return nxt;
	quanta ret(nxt);
	if(c == '(') {
		ret.sum++;
		ret.mn++;
	}
	else {
		ret.sum--;
		ret.mn = min(-1, ret.mn - 1);
	}
	ret.mx_abs = max(ret.mx_abs, -ret.sum);
	ret.mx = max(ret.mx, ret.sum);
	if(ret.sum < 0) ret.valid = 0;
	return ret;	
}

int getAnswer(quanta L, quanta R){
	if(!L.valid) return -1;
	if(L.sum + R.mn < 0) return -1;
	if(L.sum + R.sum != 0) return -1;
	return max(max(L.mx, R.mx_abs), L.sum + R.mx);
}

int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	int m; string S;
	cin >> m >> S;
	txt.pb('-');
	suff.emplace_back(empty);
	suff.emplace_back(empty);
	pref.emplace_back(empty);

	for(char & c : S) {
		if(c == '(') continue;
		if(c == ')') continue;
		if(c == 'L') continue;
		if(c == 'R') continue;
		c = '-';
	}
	int p = 0;
	for(char c : S){
//		cout << "c = " << c << " " << sz(pref) << " " << sz(suff) << endl;
		if(c == 'L') {
			if(p) {
				p--;
				pref.pop_back();
				suff.push_front(merge(txt[p], suff.front()));
			}
		}
		else if(c == 'R') {
			pref.push_back(merge(pref.back(), txt[p]));
			suff.pop_front();
			p++;
			if(p == sz(txt)) txt.pb(eps), suff.emplace_back(empty);
		}
		else {
			suff.pop_front();
			txt[p] = c;
			suff.push_front(merge(txt[p], suff.front()));
		}
		printf("%d\n", getAnswer(pref.back(),  suff.front()));
	/*	cout << txt << endl;
		for(auto q : pref) cout << q << " ";
		cout << "|";
		for(auto q : suff) cout << " " << q;
		cout << endl;
	*/
	}
	
	
	return 0;
}
