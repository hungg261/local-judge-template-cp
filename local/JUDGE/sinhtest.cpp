#include <bits/stdc++.h>
#define int long long
using namespace std;
using namespace std::chrono;

const string trau_EXTENSION=".exe", NAME="SOLVE", EXTENSION=".exe", CODE=".TEST";
const int NTEST=1000000, TIME_LIMIT=1;
const bool writetest=false, wronglog=true, wrongexit=true;
string verdict="";
double total_points=100.0;
double avg_points=total_points/NTEST,cur_pts=0,cur_ac=0,cur_time=0;
int ac=0,wa=0,tle=0;

const bool complete_rand=true;
mt19937 rng;

void seeding(){
    if(complete_rand)
        rng.seed(chrono::steady_clock::now().time_since_epoch().count());
    else{
        // random_device rd;
        rng.seed(26012010);
    }
}

int Rand(int l,int h);
string roundk(double number, int k);
string pad(int n);
string get_time();
string randomStr(int size,string mode="num");

string add(const string& a, const string& b);
string subtract(string a, string b);
string multiply(const string& a, const string& b);
string divide(const string& a, const string& b);

unordered_set<int>mark;
signed main(){
    seeding();
    cin.precision(2);
    ofstream logwr("Judges\\[JUDGE] "+CODE+".log");
    logwr<<"Problem: "<<CODE<<"\n"<<"Judge Time: "<<get_time();
    logwr<<"\n\n-------------------- JUDGE --------------------\n";

    bool onetest=false;
    auto start_judge_time=high_resolution_clock::now();
    for(int iTest = 1; iTest <= NTEST; iTest++){
        ofstream inp((NAME + ".INP").c_str());
        stringstream input;
        /*************** CODE ***************/
        int w=Rand(5,1000),n=Rand(1,1e5),m=Rand(1,1e5);
        input<<w<<' '<<n<<' '<<m<<'\n';
        int cur=0;
        while(n--){
            int now=Rand(1,w-2);
            input<<now<<' ';
            cur=max(cur,now);
        }
        input<<'\n';
        while(m--)input<<Rand(1,w-cur)<<' ';

        // int n=Rand(1,2e5);
        // while(n--)input<<Rand(2,1e3)<<'\n';
        // input<<Rand(1,1e8)<<'\n';
        // input<<randomStr(19)<<' '<<randomStr(19)<<' '<<randomStr(19)<<'\n';

        // int n=Rand(1,15),m=Rand(1,n);
        // vector<int>arr(n);
        // iota(begin(arr),end(arr),1);
        // shuffle(begin(arr),end(arr),rng);
        // input<<n<<' '<<m<<'\n';
        // if(Rand(1,2)==1){
        //     sort(begin(arr),begin(arr)+m);
        // }
        // for(int i=0;i<m;++i)input<<arr[i]<<' ';
        // input<<Rand(1,1e9)<<' '<<Rand(1,1e5)<<' ';
        // int L=Rand(1,10),R=Rand(L,1e6);
        // input<<L<<' '<<R<<'\n';
        // int n=Rand(1,9);
        // input<<n<<'\n';
        // while(n--)input<<Rand(1,9)<<' ';
        // int n=Rand(1,20);
        // int fact[n+1]={1};
        // for(int i=1;i<=n;++i){
        //     fact[i]=fact[i-1]*i;
        // }
        // input<<n<<' '<<Rand(1,fact[n]);

        // int n=Rand(1,100000);
        // int arr[n];
        // input<<n<<'\n';
        // if(Rand(1,2)==1){
        //     for(int i=0;i<n/2;++i){
        //         arr[i]=arr[n-i-1]=Rand(1,1e9);
        //     }
        // }
        // else{
        //     for(int i=0;i<n;++i){
        //         arr[i]=Rand(1,1e9);
        //     }
        // }
        // for(int i=0;i<n;++i){
        //     input<<arr[i]<<' ';
        // }
        /************************************/
        inp<<input.str();
        inp.close();
        if(onetest)exit(0);

        auto start=high_resolution_clock::now();
        system((NAME + EXTENSION).c_str());
        auto stop=high_resolution_clock::now();
        auto duration=duration_cast<milliseconds>(stop - start);
        if(duration.count()>1000.0*TIME_LIMIT){
            logwr<<"[Score:0.00][Time:>"<<TIME_LIMIT<<"s] "<<"Test "<<iTest<<": Time Limit Exceeded\n";
            ++tle;
            continue;
        }
        system((NAME + "_trau" + trau_EXTENSION).c_str());

        cur_time+=duration.count()/1000.0;
        bool isWrong=false;
        
        if (system(("fc " + NAME + ".OUT " + NAME + ".ans").c_str())!=0){
            logwr<<"[Score:0.00][Time:"<<roundk(duration.count()/1000.0,3)<<"s] "<<"Test "<<iTest<<": Wrong Answer\n";
            ++wa;
            if(wronglog)isWrong=true;
            if(wrongexit)exit(1);
        }
        else{
            cur_pts+=avg_points,++cur_ac;
            logwr<<"[Score:"<<roundk(avg_points,2)<<"][Time:"<<roundk(duration.count()/1000.0,3)<<"s] "<<"Test "<<iTest<<": Accepted\n";
            ++ac;
        }
        if((writetest||isWrong)){
            logwr<<"- Input:\n"<<input.str().substr(0,min((int)input.str().size(),100LL))<<(input.str().size()>100?"...\n":"\n");
            ifstream out(NAME + ".OUT"), ans(NAME + ".ans");
            string outline, ansline;
            logwr<<"- Output:\n";
            while(getline(out,outline))
                logwr<<outline<<'\n';
            logwr<<"- Expected answer:\n";
            while(getline(ans,ansline))
                logwr<<ansline<<"\n\n";
            out.close();
        }
    }

    if(ac==NTEST)verdict="Accepted";
    if(wa>0)verdict="Wrong Answer";
    if(tle>0)verdict="Time Limit Exceeded";
    if(wa>0&&tle>0)verdict="Wrong Answer + Time Limit Exceeded";

    logwr<<"\n-------------------- SCORE --------------------";
    logwr<<"\n* Total points: "<<roundk(cur_pts,2)<<"/"<<total_points<<".00 ("<<cur_ac<<"/"<<NTEST<<")";
    logwr<<"\n* Total runtime: "<<roundk(cur_time,2)<<"s - Average: "<<roundk(cur_time/NTEST,2)<<"s/case";
    logwr<<"\n* Result types:\n    - Accepted: "<<ac<<"\n    - Wrong Answer: "<<wa<<"\n    - Time Limited Exceeded: "<<tle;
    logwr<<"\n(*) Overall result: "<<verdict;
    logwr<<"\n\n[Finished in "<<roundk(duration_cast<milliseconds>(high_resolution_clock::now()-start_judge_time).count()/1000.0,2)<<"s]\n";

    cout<<"\nTotal points: "<<roundk(cur_pts,2)<<"/"<<total_points<<".00 ("<<cur_ac<<"/"<<NTEST<<")\n";
    logwr.close();
    return 0;
}

int Rand(int l,int h){
    assert(l <= h);
    uniform_int_distribution<int> uni(l, h);
    return uni(rng);
}

// vnoi:
// int Rand(int l, int h) {
//     assert(l <= h);
//     return l + abs(rd() * 1LL * rd()) % (h - l + 1);
// }

string roundk(double number, int k){
    stringstream ss;
    ss << fixed << setprecision(k) << number;
    return ss.str();
}

string pad(int n){
    stringstream padder;
    padder<<setw(2)<<setfill('0')<<n;
    return padder.str();
}

string get_time(){
    time_t now=time(NULL);
    tm *ltm = localtime(&now);

    stringstream formatted;
    formatted<<pad(ltm->tm_hour)<<":"<<pad(ltm->tm_min)<<":"<<pad(ltm->tm_sec)<<" - "<<pad(ltm->tm_mday)<<"/"<<pad(1+ltm->tm_mon)<<"/"<<1900+ltm->tm_year;
    return formatted.str();
}

string randomStr(int size,string mode){
    stringstream rstr;

    if(mode=="num"){
        for(int i=0;i<size/18;++i)
            rstr<<Rand(1e17,1e18-1);
        for(int i=0;i<size%18;++i)
            rstr<<Rand(i>0?0:1,9);
    }
    else{
        string characters="abcdefghijklmnopqrstuvwxyz";
        int len=characters.size();
        for(int i=0;i<size;++i)
            rstr<<characters[Rand(0,len-1)];
    }
    return rstr.str();
}

// BIG NUM MODULE:
int compare(const string& a, const string& b) {
    if (a.size() != b.size()) return a.size() > b.size() ? 1 : -1;
    return a.compare(b);
}

string add(const string& a, const string& b) {
    string result;
    int carry = 0;
    int i = a.size() - 1, j = b.size() - 1;
    
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }
    
    reverse(result.begin(), result.end());
    return result;
}

string subtract(string a, string b) {
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
    int borrow = 0;
    int i = a.size() - 1, j = b.size() - 1;
    
    while (i >= 0 || j >= 0 || borrow) {
        int diff = (i >= 0 ? a[i--] - '0' : 0) - (j >= 0 ? b[j--] - '0' : 0) - borrow;
        borrow = diff < 0;
        if (borrow) diff += 10;
        result.push_back(diff + '0');
    }
    
    while (result.size() > 1 && result.back() == '0') result.pop_back();
    reverse(result.begin(), result.end());
    
    if(negative)result='-'+result;
    return result;
}

string multiply(const string& a, const string& b) {
    vector<int> result(a.size() + b.size(), 0);
    
    for (int i = a.size() - 1; i >= 0; --i) {
        for (int j = b.size() - 1; j >= 0; --j) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int sum = mul + result[i + j + 1];
            result[i + j + 1] = sum % 10;
            result[i + j] += sum / 10;
        }
    }
    
    string product;
    for (int num : result) {
        if (!(product.empty() && num == 0)) product.push_back(num + '0');
    }
    
    return product.empty() ? "0" : product;
}

string divide(const string& a, const string& b) {
    if (b == "0") throw runtime_error("Division by zero");
    
    string quotient, remainder;
    
    for (char digit : a) {
        remainder.push_back(digit);
        while (remainder.size() > 1 && remainder[0] == '0') remainder.erase(0, 1);
        
        int count = 0;
        while (compare(remainder, b) >= 0) {
            remainder = subtract(remainder, b);
            ++count;
        }
        
        quotient.push_back(count + '0');
    }
    
    while (quotient.size() > 1 && quotient[0] == '0') quotient.erase(0, 1);
    return quotient.empty() ? "0" : quotient;
}