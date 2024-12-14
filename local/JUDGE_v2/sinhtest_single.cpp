#include <bits/stdc++.h>
#define int long long
using namespace std;
using namespace std::chrono;

const string EXTENSION=".exe", NAME="SOLVE", NEXTENSION=".exe", CODE="STEST";
const int NTEST=10000, TIME_LIMIT=1;
const bool writetest=false, wronglog=true, wrongexit=true;
string verdict="";
double total_points=100.0;
double avg_points=total_points/NTEST,cur_pts=0,cur_ac=0,cur_time=0;
int ac=0,wa=0,tle=0;

random_device rd;
mt19937 rng(rd());

int Rand(int l,int h);
string roundk(double number, int k);
string pad(int n);
string get_time();
string randomStr(int size,string mode="num");

signed main(){
    cin.precision(2);
    ofstream logwr("Judges\\[JUDGE] "+CODE+".log");
    logwr<<"Problem: "<<CODE<<"\n"<<"Judge Time: "<<get_time();
    logwr<<"\n\n-------------------- JUDGE --------------------\n";

    auto start_judge_time=high_resolution_clock::now();
    for(int iTest = 1; iTest <= NTEST; iTest++){
        ofstream inp((NAME + ".INP").c_str());
        stringstream input;
        /*************** CODE ***************/
        int n=Rand(1,100),m=0;
        vector<int>A(n);
        string ans=string(n,'0');
        input<<n;
        for(int i=0;i<n;++i){
            A[i]=Rand(1,100);
            if(Rand(1,5)==1){
                // cout<<c<<' '<<i<<'\n';
                ans[i]='1';
                m+=A[i];
            }
        }
        input<<' '<<m<<'\n';
        for(int k:A)input<<k<<' ';
        // cout<<ans;
        /************************************/
        inp<<input.str();
        inp.close();
        // exit(0);

        auto start=high_resolution_clock::now();
        system((NAME + NEXTENSION).c_str());
        auto stop=high_resolution_clock::now();
        auto duration=duration_cast<milliseconds>(stop - start);
        if(duration.count()>1000.0*TIME_LIMIT){
            logwr<<"[Score:0.00][Time:>"<<TIME_LIMIT<<"s] "<<"Test "<<iTest<<": Time Limit Exceeded\n";
            ++tle;
            continue;
        }

        cur_time+=duration.count()/1000.0;
        bool isWrong=false;
        
        /*************** JUDGE ***************/
        ifstream outputfile("SOLVE.OUT");
        string output;
        getline(outputfile,output);
        stringstream getout(output);

        int idx,sum=0;
        while(getout>>idx){
            sum+=A[idx-1];
        }
        if(sum!=m)isWrong=true;
        /*************************************/
        if (isWrong){
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