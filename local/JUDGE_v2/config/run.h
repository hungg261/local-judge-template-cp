// Thuat toan "toi uu":
auto start=Utilities::Time::get_current();
system((config::setup::NAME + config::setup::EXTENSION).c_str());
auto stop=Utilities::Time::get_current();
auto duration=duration_cast<milliseconds>(stop - start);

// Kiem tra qua thoi gian:
if(duration.count()>1000.0*config::setup::TIME_LIMIT){
    File::logwr<<"[Score:0.00][Time:>"<<config::setup::TIME_LIMIT<<"s] "<<"Test "<<iTest<<": Time Limit Exceeded\n";
    ++config::statistic::tle;
    continue;
}

// Thuat toan "vet can":
system((config::setup::NAME + "_trau" + config::setup::trau_EXTENSION).c_str());

config::statistic::cur_time+=duration.count()/1000.0;
