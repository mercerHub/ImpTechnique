#include <bits/stdc++.h>
using namespace std;

vector<long long> tree;
vector<long long>lazy;

long long Query(int node , int nl , int nh ,int ql,int qh){
    if(lazy[node] != 0){
        long long dx = lazy[node];
        lazy[node] = 0;
        tree[node] += dx * (nh - nl + 1);
        if(nl != nh){
            lazy[2*node] += dx;
            lazy[2*node + 1] += dx;
        }
    }
    if(nl >= ql && nh <=qh) return tree[node];
    if(nl > qh || nh < ql) return  0;
    int mw = (nl + nh)/2;
    return Query(2*node , nl , mw , ql, qh) + Query(2*node + 1 , mw + 1 , nh , ql , qh);
}
void update (int node , int nl , int nh ,int ql,int qh , long long val){
    if(lazy[node] != 0){
        long long dx = lazy[node];
        lazy[node] = 0;
        tree[node] += dx * (nh - nl + 1);
        if(nl != nh){
            lazy[2*node] += dx;
            lazy[2*node + 1] += dx;
        }
    }
    if(nl >= ql && nh <=qh){
        long long dx = (nh - nl + 1)*val;
        tree[node]+=dx;
        if(nl != nh){
            lazy[2*node] += val;
            lazy[2*node + 1] += val;
        }
        return;
    }
    if(nl > qh || nh < ql) return ;
    int mw = (nl + nh)/2;
    update(2*node , nl , mw , ql, qh,val);
    update(2*node + 1 , mw + 1 , nh , ql , qh,val);
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q;
    cin >> n >> q;

    vector<long long>arr(n,0);
    for(int i = 0 ; i < n ; i ++) cin >> arr[i];

    while(__builtin_popcount(n) != 1){
        n++;
        arr.push_back(0);
    }

    tree.resize(2*n);
    lazy.resize(2*n);

    for(int i = 0 ; i < n ; i ++){
        tree[n+i] = arr[i];
    }

    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int l,r;
            long long val;
            cin >> l >> r >> val;
            l--;
            r--;
            update(1,0,n-1,l,r,val);
        }
        else{
            int ind;
            cin >> ind;
            ind--;
            cout << Query(1,0,n-1,ind,ind) <<endl;
        }
    }

    return 0;
}  