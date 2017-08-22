#include<bits/stdc++.h>
using namespace std;
using P = pair< int,int>;
using node = tuple<int,int,int>;
const int MAX_N = (1 << 21) - 1;
const int inf = numeric_limits<int>::max();
 
int n;
P etree[MAX_N];
P otree[MAX_N];
vector< P > v;
 
void init(int k,int l,int r){
  if(r - l == 1){
    etree[k] = P(inf,-1);
    otree[k] = P(inf,-1);
  }else{
    int chl = k*2+1;
    int chr = k*2+2;
    etree[k] = P(inf,-1);
    otree[k] = P(inf,-1);
    init(chl, l, (l+r)/2);
    init(chr, (l+r)/2, r);
  }
}
 
void update(int t,int i,int x,int k,int l, int r){
  if(l <= i && i < r){
    if(r - l == 1){
      if(t == 0)
        etree[k] = P(x,2*l);
      else
        otree[k] = P(x,2*l+1);
    }else{
      int chl = k*2+1;
      int chr = k*2+2;
      update(t,i,x,chl,l,(l+r)/2);
      update(t,i,x,chr,(l+r)/2,r);
      if(t == 0)
        etree[k] = min(etree[chl],etree[chr]);
      else
        otree[k] = min(otree[chl],otree[chr]);
    }
  }
}
 
P find(int t,int a,int b,int k,int l,int r){
  if(r <= a || b <= l)return P(inf,-1);
  else if(a <= l && r <= b)
    return t == 0 ? etree[k] : otree[k];
  else{
    int chl = k*2+1;
    int chr = k*2+2;
    P vl = find(t,a,b,chl,l,(l+r)/2);
    P vr = find(t,a,b,chr,(l+r)/2,r);
    return min(vl,vr);
  }
}
 
void rec(int l,int r){
  cout << l << " " << r << endl;
  if(r - l <= 0)return;
  P res = find(l%2,l/2,r/2,0,0,n);
  int idx = res.second;
  P res2 = find((idx+1)%2,(idx+1)/2,(r+1)/2,0,0,n);
  int idx2 = res2.second;
  rec(l,idx);
  rec(idx+1,idx2);
  rec(idx2+1,r);
  v.push_back(P(res.first,res2.first));
}
 
int main(void){
  cin >> n;
  init(0,0,n);
  for(int i = 0;i < n;++i){
    int a;
    cin >> a;
    update(i%2,i/2,a,0,0,n);
  }
  priority_queue< node,vector<node>,greater<node> > que;
  bool flag = false;
  que.push(node(find(0,0,n/2,0,0,n).first,
                0,n));
  while(!que.empty()){
    int m,l,r;
    tie(m,l,r) = que.top();
    que.pop();
    if(flag)cout << " ";
    flag = true;
    P res = find(l%2,l/2,r/2,0,0,n);
    int idx = res.second;
    P res2 = find((idx+1)%2,(idx+1)/2,(r+1)/2,0,0,n);
    int idx2 = res2.second;
    cout << res.first << " " << res2.first;
    if(idx - l > 0)
      que.push(node(find(l%2,l/2,idx/2,0,0,n).first,
                    l,idx));
    if(idx2 - (idx+1) > 0)
      que.push(node(find((idx+1)%2,(idx+1)/2,idx2/2,0,0,n).first,
                    idx+1,idx2));
    if(r - (idx2+1) > 0)
      que.push(node(find((idx2+1)%2,(idx2+1)/2,r/2,0,0,n).first,
                    idx2+1,r));
  }
  return 0;
}

