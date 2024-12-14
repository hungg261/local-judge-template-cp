#include<bits/stdc++.h>
#define int long long
using namespace std;

// module xu li so lon
typedef string bigint;
namespace BIGINT{
    int compare(const string&a,const string&b){
        if(a.size()!=b.size())return a.size()>b.size()?1:-1;
        return a.compare(b);
    }

    string add(const string&a,const string&b){
        string result;
        int carry=0;
        int i=a.size()-1,j=b.size()-1;

        while (i>=0||j>=0||carry){
            int sum=carry;
            if(i>=0)sum+=a[i--]-'0';
            if(j>=0)sum+=b[j--]-'0';
            carry=sum/10;
            result+=sum%10+'0';
        }

        reverse(begin(result),end(result));
        return result;
    }

    string subtract(string a,string b){
        bool negative=false;
        switch(compare(a,b)){
            case -1:
                swap(a,b);
                negative=true;
                break;
            case 0:
                return "0";
        }

        string result;
        int borrow=0;
        int i=a.size()-1,j=b.size()-1;

        while (i>=0||j>=0||borrow){
            int diff=(i>=0?a[i--]-'0':0)-(j>=0?b[j--]-'0':0)-borrow;
            borrow=diff<0;
            if(borrow)diff+=10;
            result+=diff+'0';
        }

        while (result.size()>1&&result.back()=='0')result.pop_back();
        reverse(result.begin(),result.end());

        if(negative)result='-'+result;
        return result;
    }

    string multiply(const string&a,const string&b){
        vector<int>result(a.size()+b.size(),0);

        for (int i=a.size()-1;i>=0;--i){
            for (int j=b.size()-1;j>=0;--j){
                int mul=(a[i]-'0')*(b[j]-'0');
                int sum=mul+result[i+j+1];
                result[i+j+1]=sum%10;
                result[i+j]+=sum/10;
            }
        }

        string product;
        for (int num:result){
            if(!(product.empty()&&num==0))product+=num+'0';
        }

        return product.empty()?"0":product;
    }

    string divide(const string&a,const string&b){
        string result,rem;

        for (char digit:a){
            rem+=digit;
            while (rem.size()>1&&rem[0]=='0')rem.erase(0,1);

            int count=0;
            while (compare(rem,b)>=0){
                rem=subtract(rem,b);
                ++count;
            }

            result+=count+'0';
        }

        while (result.size()>1&&result[0]=='0')result.erase(0,1);
        return result.empty()?"0":result;
    }
    
    string mod(const string&a,const string&b){
        return subtract(a,multiply(b,divide(a,b)));
    }
}
using namespace BIGINT;

bigint fact[27]={"1"};
bool mark[27];
string characters=" abcdefghijklmnopqrstuvwxyz";

string toString(int n){
    string res="";
    while(n>0){
        res+=n%10+'0';
        n/=10;
    }
    reverse(begin(res),end(res));
    return res;
}

void compute(){
    for(int i=1;i<=26;++i){
        fact[i]=multiply(fact[i-1],toString(i));
    }
}

int get_at(int pos,int n=26){
    int idx=0;
    for(int i=1;i<=n;++i){
        if(!mark[i])++idx;
        
        if(idx==pos){
            return i;
        }
    }
    return '0';
}

string solve(bigint pos,int length,string trace){
    if(length==0){
        return trace;
    }
    if(compare(pos,fact[length])==1)return "-1";
    
    int idx=get_at(stoll(divide(subtract(pos,"1"),fact[length-1]))+1);
    mark[idx]=true;
    return solve(add(mod(subtract(pos,"1"),fact[length-1]),"1"),length-1,trace+characters[idx]);
}

signed main(){
    freopen("SOLVE.INP","r",stdin);freopen("SOLVE.OUT","w",stdout);
    int n;
    bigint k;
    cin>>n>>k;
    compute();
    
    cout<<solve(k,n,"");
    return 0;
}
