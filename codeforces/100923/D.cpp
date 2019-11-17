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
#define tc() int T; scanf("%d",&T); for(int t = 1;t <= T;t++)
using namespace std;


struct AC_FSM{
#define ALPHABET_SIZE 26
    struct Node{
        int child[ALPHABET_SIZE], failure = 0, match_parent = -1;
        vector<int> match;
        Node() {
            for (int i = 0; i < ALPHABET_SIZE; ++i)child[i] = -1; } };
    vector<Node> a;
    AC_FSM(){
        a.push_back(Node()); }
    void construct_automaton(vector<string> &words){
        for (int w = 0, n = 0; w < (int)words.size(); ++w, n = 0){
            for (int i = 0; i < (int)words[w].size(); ++i){
                if (a[n].child[words[w][i] - 'a'] == -1){
                    a[n].child[words[w][i] - 'a'] = a.size();
                    a.push_back(Node()); }
                n = a[n].child[words[w][i] - 'a']; }
            a[n].match.push_back(w); }
        queue<int> q;
        for (int k = 0; k < ALPHABET_SIZE; ++k){
            if (a[0].child[k] == -1) a[0].child[k] = 0;
            else if (a[0].child[k] > 0){
                a[a[0].child[k]].failure = 0;
                q.push(a[0].child[k]); } }
        while (!q.empty()){
            int r = q.front();
            q.pop();
            for (int k = 0, arck; k < ALPHABET_SIZE; ++k){
                if ((arck = a[r].child[k]) != -1){
                    q.push(arck);
                    int v = a[r].failure;
                    while (a[v].child[k] == -1) v = a[v].failure;
                    a[arck].failure = a[v].child[k];
                    a[arck].match_parent = a[v].child[k];
                    while (a[arck].match_parent != -1 &&
                            a[a[arck].match_parent].match.empty())
                        a[arck].match_parent = a[a[arck].match_parent].match_parent; } } } }
    void aho_corasick(string &sentence, vector<string> &words,
                      vector<vector<int> > &matches){
        matches.assign(words.size(), vector<int>());
        int state = 0, ss = 0;
        for (int i = 0; i< (int)sentence.length(); ++i, ss = state){
            while (a[ss].child[sentence[i]-'a'] == -1)
                ss = a[ss].failure;
            state = a[state].child[sentence[i]-'a'] = a[ss].child[sentence[i]-'a'];
            for (ss = state; ss != -1; ss = a[ss].match_parent)
                for (int w : a[ss].match)
                    matches[w].push_back(i + 1 - words[w].length()); } } };


int t;
int n;
char s[1000100];
ll a[1000100];
int mn[1000100];

vector < string > v;
vector < vector < int > > matches;
char s2[330];
int m;

using pi = pair<int,int>;
const int MAX = 100*100,MAXK = 102;
ll dp[MAX][MAXK];
vector<pi> aux;

ll solve(int i,int d) {
	if(i == (int)aux.size()) return 0;
	d = max(d,-1);
	ll & ret = dp[i][d + 1];
	if(ret != -1) return ret;
	ret = 1LL << 60;
	int s = aux[i].first;
	if(d != -1 && d < aux[i].second) {
		int nd = s + d;
		if(i+1 < (int)aux.size()) nd -= aux[i+1].first;
		ret = solve(i+1,nd);
	}

	int k = s + aux[i].second;
	for(int p = s;p < k;p++){
		int nd = p;
		if(i+1 < (int)aux.size()) nd -= aux[i+1].first;
		ret = min(ret,solve(i+1,nd) + a[p]);
	}
//	cerr << i << " " << d << ": " << ret << endl;
	return ret;
}

int main()
{
    freopen("cenzura.in", "r", stdin);
    freopen("cenzura.out", "w", stdout);

    scanf("%d", &t);
    while (t--)
    {
        v.clear();
        matches.clear();
        memset(mn, 0x3f, sizeof mn);

        scanf("%d", &n);
        scanf("%s", s);
        for (int i = 0; i < n; ++i)
            scanf("%lld", &a[i]);
        scanf("%d", &m);
        for (int i = 0; i < m ; ++i)
        {
            scanf("%s", s2);
            v.push_back(s2);
        }
        string ss = s;
        AC_FSM aho;
        aho.construct_automaton(v);
        aho.aho_corasick(ss, v, matches);
        for (int i = 0; i < m; ++i)
            for (auto bla : matches[i])
                mn[bla] = min(mn[bla], (int)v[i].size());
//        for(int i = 0;i < n;i++)
//        	cerr << i << " " << mn[i] << endl;
        aux.clear();
        for(int i = 0;i < n;i++)
        	if(mn[i] < MAXK){
        		aux.emplace_back(i,mn[i]);
        	}
        assert(!aux.empty());
        memset(dp,-1,sizeof dp);
        printf("%lld\n",solve(0,-1));
	}

    return 0;
}


