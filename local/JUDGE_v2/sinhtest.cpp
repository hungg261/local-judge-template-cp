#include <bits/stdc++.h>
#define int long long
using namespace std;
using namespace std::chrono;

namespace config{
    namespace setup{
        const string    trau_EXTENSION=".exe",
                        NAME="SOLVE",
                        EXTENSION=".exe",
                        CODE=".TEST";

        const double    TIME_LIMIT=1;
        const int   NTEST=100;

        const bool  writetest=false,
                    wronglog=true,
                    wrongexit=false;

        const bool  RAND_ALL=true,
                    onetest=false,
                    fastIO=false;
    }
    namespace statistic{
        string  verdict="";
        double  total_points=100.0,
                avg_points=total_points/config::setup::NTEST,
                cur_pts=0,
                cur_ac=0,
                cur_time=0;

        int ac=0,
            wa=0,
            tle=0;
    }
}

#include "config/random.h"
#include "config/utility.h"
#include "config/file.h"
#include "config/init.h"

using namespace File;
using namespace Rand_machine::Random;
signed main(){
    Init();

    auto start_judge_time=Utilities::Time::get_current();
    for(int iTest = 1; iTest <= config::setup::NTEST; iTest++){
        ofstream file_input((config::setup::NAME + ".INP").c_str());
        stringstream input;
        /*************** CODE ***************/
        int n=Rand(1,10000);
        while(n--)input<<Rand_VNOI(-100,100)<<'\n';
        /************************************/
        file_input<<input.str();
        file_input.close();
        if(config::setup::onetest){
            exit(0);
        }

        bool isWrong=false;
        #include "config/run.h"
        #include "config/ans_cmp.h"
        #include "config/write_test.h"
    }

    #include "config/write_log.h"
    File::logwr.close();
    return 0;
}
