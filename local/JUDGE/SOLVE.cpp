/******************************************************************************
Link: REPORT
Code: REPORT
Time (YYYY-MM-DD-hh.mm.ss): 2024-12-13-21.13.52
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAX=1e5;
int w,n,m,a[MAX+3],b[MAX+3];

int countline(int space,int arr[],int len){
    int line=1,j=1,sum=0;
    while(j<=len){
        if(arr[j]>space)return 1e18;
        sum+=arr[j];
        if(sum>space){
            sum=arr[j];
            ++line;

        }

        ++j;
    }
    return line;
}

void solve(){
   int ans=1e14;
   for(int i=1;i<w;++i){
       int cur=max(countline(i,a,n),countline(w-i,b,m));
       ans=min(ans,cur);

       // cerr<<i<<"/"<<w-i<<"\t| "<<cur<<' '<<countline(i,a,n)<<' '<<countline(w-i,b,m)<<'\n';
   }
   // cerr<<ans<<'\n';
}

int tknp(){
    int l=1,h=w-1,ans=LLONG_MAX;
    while(l<=h){
        int mid=(l+h)/2;
        int left=countline(mid,a,n),
            right=countline(w-mid,b,m);

        // cout<<mid<<' '<<left<<' '<<right<<'\n';
        ans=min(ans,max(left,right));
        if(left<right){
            h=mid-1;
        }
        else l=mid+1;
    }
    return ans;
}


signed main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    freopen("SOLVE.INP","r",stdin);freopen("SOLVE.OUT","w",stdout);
    // freopen("REPORT.INP","r",stdin);
    // freopen("REPORT.OUT","w",stdout);
    cin>>w>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=m;++i){
        cin>>b[i];
    }

    solve();
    cout<<tknp()<<'\n';
    return 0;
}
