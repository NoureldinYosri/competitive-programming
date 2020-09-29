#include <iostream>
#include <deque>
#include <climits>
#include <cstdio>
#include <stack>
#include <set>
#include <map>
#include <vector>
#include <functional>
#include <vector>
#include <list>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pl;

const int MAXN = 100*1000 + 10;
int n, A[MAXN];
ll M;
ll pref[MAXN];
ll ST[1 << 20], LA[1 << 20];

void update(int cur, int x){
	ST[cur] += x;
	LA[cur] += x;
}

void push_down(int cur){
	if(!LA[cur]) return;
	int left = 2*cur + 1, right = left + 1;
	update(left, LA[cur]);
	update(right, LA[cur]);
	LA[cur] = 0;
}

void update(int cur, int s, int e, int p, ll v){
	if(s == e){
		ST[cur] = v;
		LA[cur] = 0;
		return;
	}
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(p <= m) update(left, s, m, p, v);
	else update(right, m+1, e, p, v);
	ST[cur] = min(ST[left], ST[right]);
}

void update(int cur, int s, int e, int l, int r, int v){
	if(l <= s && e <= r) {
		update(cur, v);
//		cerr << "\t[" << s << ", " << e << "] = " << ST[cur] << endl;
		return;
	}
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) update(left, s, m, l, r, v);
	else if(m < l) update(right, m+1, e, l, r, v);
	else {
		update(left, s, m, l, m, v);
		update(right, m+1, e, m+1, r, v);
	}
	ST[cur] = min(ST[left], ST[right]);
//	cerr << "\t[" << s << ", " << e << "] = " << ST[cur] << endl;
}

ll query(int cur, int s, int e, int l, int r){
	if(l <= s && e <= r) return ST[cur];
	push_down(cur);
	int m = (s + e) >> 1, left = 2*cur + 1, right = left + 1;
	if(r <= m) return query(left, s, m, l, r);
	if(m < l) return query(right, m+1, e, l, r);
	return min(query(left, s, m, l, m), query(right, m+1, e, m+1, r));
}



int main(){
#ifdef HOME
	freopen("in.in", "r", stdin);
#endif
	scanf("%d %lld", &n, &M);
	for(int i = 1; i <= n; i++) {
		scanf("%d", A + i);
		pref[i] = A[i] + pref[i-1];
	}

	vector<int> L;
	
	int j = 0;
	
	ll ans = 0;
	for(int i = 1; i <= n; i++){
		while(pref[i] - pref[j] > M) j++;
		
		if(j == i) {
			ans = -1;
			break;
		}

		int k = i, prv = 0;
		while(!L.empty() && A[i] >= A[L.back()]) {
			int j = L.back(); L.pop_back();
			if(j < k) {
			//	cerr << "[" << j << ", " << k-1 << "] += " << A[i] - prv << endl;
				update(0, 0, n, j, k-1, A[i] - prv);
			}
			prv = A[j];
			k = j;
		}
		if(L.empty()) {
			//cerr << "[0, " << k-1 << "] += " << A[i] - prv << endl;
			update(0, 0, n, 0, k-1, A[i] - prv);
		} else {
			//cerr << "[" << L.back() << ", " << k-1 << "] += " << A[i] - prv << endl;
			update(0, 0, n, L.back(), k-1, A[i] - prv);			
		}
		ans = query(0, 0, n, j, i-1);
		update(0, 0, n, i, ans);	
		L.push_back(i);	
		//cerr << i << ": " << ans << " " << j << endl;
	}
	
	printf("%lld\n", ans);
	return 0;
}
