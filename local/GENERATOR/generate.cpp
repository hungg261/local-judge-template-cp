#include<bits/stdc++.h>
#include<direct.h>
#define int long long
using namespace std;
using namespace std::chrono;

const string EXTENSION=".txt", SOLVERx=".exe", MAINDIR="Tests";
const string CODE="KTH-FACT", CODEin="input", CODEout="output";
const int NTEST=100;

random_device rd;
// mt19937 rng(rd());
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int Rand(int l,int h);
string Rand_bigint(string l,string h);
string roundk(double number, int k);
string pad(int n,int layer=2);
string get_time();
string randomStr(int size,string mode="num",string characters="abcdefghijklmnopqrstuvwxyz");

string add(const string& a, const string& b);
string subtract(string a, string b);
string multiply(const string& a, const string& b);
string divide(const string& a, const string& b);

void createdir(string fpath){
    stringstream ss(fpath);
    string path="",cur;

    while(getline(ss, cur, '/')){
        if(path.size()>0)path=path+"/"+cur;
        else path=cur;

        mkdir(path.c_str());
    }
}

signed main(){
    // createdir(MAINDIR+"/"+CODE);
    createdir(MAINDIR+"/"+CODE+"/"+CODEin);
    createdir(MAINDIR+"/"+CODE+"/"+CODEout);

    for(int iTest = 1; iTest <= NTEST; iTest++){
        // createdir(MAINDIR+"/"+CODE+"/"+"test"+pad(iTest,3));
        // ofstream writetest(MAINDIR+"/"+CODE+"/"+"test"+pad(iTest,3)+"/"+"input"+EXTENSION);
        ofstream writetest(MAINDIR+"/"+CODE+"/"+CODEin+"/"+CODEin+pad(iTest,3)+EXTENSION);
        ofstream writelocaltest("SOLVE.INP");
        cout<<"Generating Test #"<<iTest<<'\n';
        stringstream input;
        /*************** CODE ***************/
        int n=iTest==1?1:(iTest<30?Rand(2,10):(iTest<50?Rand(11,20):Rand(21,26)));
        string fact[n+1]={"1"};
        for(int i=1;i<=n;++i){
            fact[i]=multiply(fact[i-1],to_string(i));
        }
        cerr<<iTest<<' '<<n<<' '<<fact[n]<<'\n';
        input<<n<<' '<<Rand_bigint("1",fact[n])<<'\n';

        // input<<(iTest<250?Rand(1,20):(iTest<500?Rand(100,500):(iTest<750?Rand(501,1000):Rand(3000,5000))))<<'\n';
        // input<<iTest<<'\n';

        // input<<(iTest<250?Rand(1,1000):(iTest<500?Rand(1001,1e6):(iTest<750?Rand(1e7,1e12):Rand(1e13,1e14))))<<'.';
        // input<<randomStr(6,"char","0123456789")<<'\n';
        // input<<Rand(-5,5)<<'\n';

        // input<<(iTest<250?Rand(1,1000):(iTest<500?Rand(1001,1e6):(iTest<750?Rand(1e7,1e12):Rand(1e13,1e14))))<<'\n';
        // int a,b;
        // #define gen (iTest<25?Rand(-50,50):(iTest<100?Rand(-1e3,1e3):(iTest<250?Rand(-1e5,1e5):(iTest<500?Rand(-INT_MAX,INT_MAX):Rand(LLONG_MAX+1,LLONG_MAX)))))
        // if(iTest>=500||Rand(1,10)!=1){
        //     a=gen;
        //     b=gen; 
        // }
        // else{
        //     a=gen;
        //     b=a*Rand(1,iTest);
        // }
        // if(Rand(1,2)==1)swap(a,b);
        // input<<a<<' '<<b;
        // input<<(iTest<25?Rand(1,50):(iTest<100?Rand(1,1e3):(iTest<250?Rand(1,1e5):(iTest<500?Rand(1,INT_MAX):Rand(1,LLONG_MAX)))))<<'\n';
        // input<<(iTest<250?Rand(7,3+iTest*4):(iTest<500?Rand(iTest*100,iTest*200):(iTest<800?Rand(iTest*1000,iTest*1250):Rand(1e15,1e18))))<<'\n';
        // if(Rand(1,80)!=69){
        //     if(Rand(1,3)!=1){
        //         input<<Rand(1,31)<<' '<<Rand(1,12)<<' '<<Rand(0,iTest*100000)<<'\n';
        //     }
        //     else input<<Rand(1,iTest*10)<<' '<<Rand(1,iTest*10)<<' '<<Rand(0,iTest*100000)<<'\n';
        // }
        // else{
        //     int y=Rand(0,iTest*100000);
        //     if(Rand(1,2)==1)y=y/4*4;
        //     input<<29<<' '<<2<<' '<<y<<'\n';
        // }
        /************************************/
        writetest<<input.str();
        writetest.close();

        writelocaltest<<input.str();
        writelocaltest.close();

        /******************** OUTPUTS ********************/
        ofstream writeans(MAINDIR+"/"+CODE+"/"+CODEout+"/"+CODEout+pad(iTest,3)+EXTENSION);
        // ofstream writeans(MAINDIR+"/"+CODE+"/"+"test"+pad(iTest,3)+"/"+"output"+EXTENSION);
        system(("SOLVER"+SOLVERx).c_str());
        ifstream getans("SOLVE.OUT");

        string output;
        while(getline(getans,output))
            writeans<<output<<'\n';
        getans.close();
        writeans.close();
        cout<<"Generated test #"<<iTest<<"\n\n";
    }
    cout<<"Finished generating "<<NTEST<<" tests.\n";
    return 0;
}

int Rand(int l,int h){
    assert(l <= h);
    uniform_int_distribution<int> uni(l, h);
    return uni(rng);
}

string Rand_bigint(string l_str,string h_str){
    std::string l = l_str;
    std::string h = h_str;

    int len_l = l.size();
    int len_h = h.size();

    if (len_l < len_h) {
        l.insert(0, len_h - len_l, '0');
    } else if (len_h < len_l) {
        h.insert(0, len_l - len_h, '0');
    }

    int length = l.size();
    std::string result = "";

    bool generated = false;  // To track if we have generated the number

    // Generate the random number digit by digit
    for (int i = 0; i < length; ++i) {
        char l_digit = l[i];
        char h_digit = h[i];

        if (l_digit == h_digit) {
            // If both digits are the same, the random digit must also be the same
            result += l_digit;
        } else {
            // If digits differ, generate a random number between l_digit and h_digit
            int lower = l_digit - '0';
            int upper = h_digit - '0';

            int rand_digit = lower + rand() % (upper - lower + 1);
            result += (rand_digit + '0');

            // After finding a random digit, we can freely choose the rest of the digits
            for (int j = i + 1; j < length; ++j) {
                int rand_rest = rand() % 10;
                result += (rand_rest + '0');
            }
            generated = true;
            break;
        }
    }

    // Ensure no leading zeros in the result
    while (result[0] == '0' && result.size() > 1) {
        result.erase(0, 1);
    }

    return result;
}

string roundk(double number, int k){
    stringstream ss;
    ss << fixed << setprecision(k) << number;
    return ss.str();
}

string pad(int n,int layer){
    stringstream padder;
    padder<<setw(layer)<<setfill('0')<<n;
    return padder.str();
}

string get_time(){
    time_t now=time(NULL);
    tm *ltm = localtime(&now);

    stringstream formatted;
    formatted<<pad(ltm->tm_hour)<<":"<<pad(ltm->tm_min)<<":"<<pad(ltm->tm_sec)<<" - "<<pad(ltm->tm_mday)<<"/"<<pad(1+ltm->tm_mon)<<"/"<<1900+ltm->tm_year;
    return formatted.str();
}

string randomStr(int size,string mode,string characters){
    stringstream rstr;

    if(mode=="num"){
        for(int i=0;i<size/18;++i)
            rstr<<Rand(1e17,1e18-1);
        for(int i=0;i<size%18;++i)
            rstr<<Rand(i>0?0:1,9);
    }
    else{
        // string characters="abcdefghijklmnopqrstuvwxyz";
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