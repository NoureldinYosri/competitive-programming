#include <bits/stdc++.h>
using namespace std;

template<typename T>
void out(T x) { cout << x << endl; exit(0); }
#define watch(x) cout << (#x) << " is " << (x) << endl





using ll = long long;

const ll mod = 1e9+7;
const int maxn = 1e6 + 5;


void solve() {
    int n,x,y;
    cin>>n>>x>>y;
    vector<int> b(n);
    vector<vector<int>> inds(n+2);
    for (int i=0; i<n; i++) {
    cin>>b[i];
    inds[b[i]].push_back(i);
    }
    
    int other=1;
    while (!inds[other].empty() && other<=n+1) other++;
    assert(other<=n+1);

    vector<int> ans(n, other);
    
    priority_queue<pair<int,int>> pq; //(freq,x)
    for (int i=1; i<=n+1; i++) {
    pq.push({(int)inds[i].size(),i});
    }


    // Assign x elems, pick most frequent elems
    for (int i=0; i<x; i++) {
    auto cur = pq.top();
    pq.pop();
    int num = cur.second;
    ans[inds[num].back()] = num;
    inds[num].pop_back();
    pq.push({(int)inds[num].size(),num});
    }


    // Most freq is bottleneck
    int mostFreq = pq.top().first;
    if (mostFreq*2 - (n-x) > (n-y)) {
    cout<<"NO\n";
    return;
    }

    cout<<"YES\n";
    
    int shift = mostFreq;
    vector<int> rest;
    
    while (pq.size()) {
    auto cur = pq.top();
    pq.pop();
    int num = cur.second;
    rest.insert(rest.end(), inds[num].begin(), inds[num].end());
    }

    int N = rest.size();
    for (int i=0; i<N; i++) {
    ans[rest[(i+shift)%N]] = b[rest[i]];
    }

    for (int i=0; i<n-y; i++) {
    ans[rest[i]] = other;
    }

    int cntX = 0;
    for (int i=0; i<n; i++) {
    cntX += ans[i]==b[i];
    }
    assert(cntX==x);

    for (int i: rest) {
    assert(ans[i] != b[i]);
    }

    for (int x: ans) cout<<x<<" ";
    cout<<"\n";

    
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);  cout.tie(0);

    int t;
    cin>>t;
    while (t--) {
    solve();
    }
    
    
    return 0;
}