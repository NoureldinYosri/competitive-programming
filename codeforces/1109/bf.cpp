#include <bits/stdc++.h>
 
using namespace std;
 
template<class T, class U>
void ckmin(T &a, U b)
{
	if (a > b) a = b;
}
template<class T, class U>
void ckmax(T &a, U b)
{
	if (a < b) a = b;
}
 
#define MP make_pair
#define PB push_back
#define LB lower_bound
#define UB upper_bound
#define fi first
#define se second
#define FOR(i, a, b) for (auto i = (a); i < (b); i++)
#define FORD(i, a, b) for (auto i = (a) - 1; i >= (b); i--)
#define SZ(x) ((int) ((x).size()))
#define ALL(x) (x).begin(), (x).end()
#define INF 1000000007
 
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef vector<pll> vpl;
 
const ld EPS = 1e-12;
 
int Q;
 
struct node
{
	ll pos, v, len, stor, best; //where this goes, what's the minimum it goes.
	//stor is actuallly the total delta. best is the min delta.
	int pri, subt;
	//position, speed, stor of subtree
	node *ch[2];
	node(ll x, ll d, ll sp)
	{
		pos = x; len = d; v = sp;
		stor = v * d;
		best = min(0ll, stor);
		pri = rand();
		ch[0] = ch[1] = nullptr;
		subt = 1;
	}
};
 
void recalc(node *t)
{
	if (!t) return;
	t -> stor = t -> v * t -> len;
	t -> subt = 1;
	if (t -> ch[0] && t -> ch[1])
	{
		t -> stor += t -> ch[0] -> stor + t -> ch[1] -> stor;
		t -> subt += t -> ch[0] -> subt + t -> ch[1] -> subt;
		t -> best = min(t -> ch[0] -> best, t -> ch[0] -> stor + t -> v * t -> len + t -> ch[1] -> best);
	}
	else if (t -> ch[1])
	{
		t -> stor += t -> ch[1] -> stor;
		t -> subt += t -> ch[1] -> subt;
		t -> best = min(0ll, t -> v * t -> len + t -> ch[1] -> best);
	}
	else if (t -> ch[0])
	{
		t -> stor += t -> ch[0] -> stor;
		t -> subt += t -> ch[0] -> subt;
		t -> best = min(t -> ch[0] -> best, t -> ch[0] -> stor + t -> v * t -> len);
	}
	else
	{
		t -> best = min(0ll, t -> v * t -> len);
	}
	//recalculate stor, best, subt.
	//calculate!
}
 
node *merge(node *l, node *r)
{
	if (!l) return r;
	if (!r) return l;
	if (l -> pri > r -> pri)
	{
		l -> ch[1] = merge(l -> ch[1], r);
		recalc(l); return l;
	}
	else
	{
		r -> ch[0] = merge(l, r -> ch[0]);
		recalc(r); return r;
	}
}
typedef pair<node*, node*> pnn;
pnn split(node *t, ll x, bool flag) //everything <x goes.
{
	if (!t) return {nullptr, nullptr};
	ll cur = (flag ? (t -> ch[0] ? t -> ch[0] -> subt : 0) : t -> pos);
	if (x <= cur)
	{
		pnn p = split(t -> ch[0], x, flag);
		t -> ch[0] = p.se; recalc(t);
		return {p.fi, t};
	}
	else
	{
		pnn p = split(t -> ch[1], (flag ? x - cur - 1 : x), flag);
		t -> ch[1] = p.fi; recalc(t);
		return {t, p.se};
	}
}
ld trav(node *t, ll x)
{
	ll cur = (t -> ch[0] ? t -> ch[0] -> best : INF);
	// cerr << cur << ' ' << x << endl;
	if (cur <= x)
	{
		return trav(t -> ch[0], x);
	}
	x -= (t -> ch[0] ? t -> ch[0] -> stor : 0);
	// cerr << "then " << t -> v << ' ' << t ->  << ' ' << x << endl;
	if (t -> v * t -> len <= x)
	{
		// cerr << t -> pos << ' ' << x << ' ' << (t -> v) << endl;
		//bleh do some math.
		return t -> pos + (1.0 * x / (t -> v));
	}
	else
	{
		return trav(t -> ch[1], x - t -> v * t -> len);
	}
}
 
void inorder(node *t)
{
	if (!t) return;
	inorder(t -> ch[0]);
	cout << "NODE pos " << t -> pos << " velocity " << t -> v << " dist " <<  t -> len << endl;
	inorder(t -> ch[1]);
}
 
node* root;
set<ll> times;
 
int32_t main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(12);
	cerr << fixed << setprecision(4);
	srand(69);
	root = merge(new node(0, INF, 0), merge(new node(INF, INF, -INF), new node(2 * INF, INF, -INF)));
	times.insert(0); times.insert(INF); times.insert(2 * INF);
	cin >> Q;
	//what's the minimum prefix sum.
	//position, length, speed
	FOR(i, 0, Q)
	{
		int qid; cin >> qid;
		// cerr << "QUERY " << i << endl;
		// inorder(root);
		if (qid == 1)
		{
			ll t, s, len;
			cin >> t >> s;
			len = *times.UB(t) - t;
			times.insert(t);
			pnn p = split(root, t, false);
			// cerr << "WTF\n";
			// inorder(p.fi);
			int zz = (p.fi -> subt) - 1;
			// cerr << p.fi -> subt << endl;
			pnn lt = split(p.fi, zz, true);
			// cerr << "size " << lt.se -> subt << endl;
			// inorder(lt.se);
			lt.se -> len = t - lt.se -> pos;
			lt.se -> stor = lt.se -> v * lt.se -> len;
			lt.se -> best = min(0ll, lt.se -> stor);
			// cerr << lt.se -> best << endl;
			root = merge(merge(lt.fi, lt.se), merge(new node(t, len, s), p.se));
			//insert smth with speed s at time t.
		}
		if (qid == 2)
		{
			ll t;
			cin >> t; times.erase(t);
			//delete smth with speed t.
			pnn p = split(root, t, false);
			pnn p1 = split(p.se, t + 1, false);
			int zz = (p.fi -> subt) - 1;
			pnn lt = split(p.fi, zz, true);
			lt.se -> len = *times.UB(t) - lt.se -> pos;
			lt.se -> stor = lt.se -> v * lt.se -> len;
			lt.se -> best = min(0ll, lt.se -> stor);
			root = merge(merge(lt.fi, lt.se), p1.se);
			// assert((root -> subt) == SZ(times));
		}
		if (qid == 3)
		{
			ll l, r, v;
			cin >> l >> r >> v;
			if (v <= 0)
			{
				cout << l << '\n';
				continue;
			}
			pnn p = split(root, l, false);
			ld ans = trav(p.se, -v);
			if (ans > r + EPS)
			{
				cout << "-1\n";
			}
			else
			{
				cout << ans << '\n';
			}
			root = merge(p.fi, p.se);
			//try shit in [l...r]. see what happens.
		}
	}
	return 0;
}
