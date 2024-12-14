        // So ket qua:
        if (system(("fc " + config::setup::NAME + ".OUT " + config::setup::NAME + ".ans").c_str())!=0){
            File::logwr<<"[Score:0.00][Time:"<<Utilities::Methods::roundk(duration.count()/1000.0,3)<<"s] "<<"Test "<<iTest<<": Wrong Answer\n";
            ++config::statistic::wa;

            if(config::setup::wronglog)isWrong=true;
            if(config::setup::wrongexit)exit(1);
        }
        else{
            config::statistic::cur_pts+=config::statistic::avg_points,++config::statistic::cur_ac;
            File::logwr<<"[Score:"<<Utilities::Methods::roundk(config::statistic::avg_points,2)<<"][Time:"<<Utilities::Methods::roundk(duration.count()/1000.0,3)<<"s] "<<"Test "<<iTest<<": Accepted\n";
            ++config::statistic::ac;
        }
