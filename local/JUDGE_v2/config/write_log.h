if(config::statistic::ac==config::setup::NTEST)config::statistic::verdict="Accepted";
if(config::statistic::wa>0)config::statistic::verdict="Wrong Answer";
if(config::statistic::tle>0)config::statistic::verdict="Time Limit Exceeded";
if(config::statistic::wa>0&&config::statistic::tle>0)config::statistic::verdict="Wrong Answer + Time Limit Exceeded";

File::logwr<<"\n-------------------- SCORE --------------------";
File::logwr<<"\n* Total points: "<<Utilities::Methods::roundk(config::statistic::cur_pts,2)<<"/"<<config::statistic::total_points<<".00 ("<<config::statistic::cur_ac<<"/"<<config::setup::NTEST<<")";
File::logwr<<"\n* Total runtime: "<<Utilities::Methods::roundk(config::statistic::cur_time,2)<<"s - Average: "<<Utilities::Methods::roundk(config::statistic::cur_time/config::setup::NTEST,2)<<"s/case";
File::logwr<<"\n* Result types:\n    - Accepted: "<<config::statistic::ac<<"\n    - Wrong Answer: "<<config::statistic::wa<<"\n    - Time Limited Exceeded: "<<config::statistic::tle;
File::logwr<<"\n(*) Overall result: "<<config::statistic::verdict;
File::logwr<<"\n\n[Finished in "<<Utilities::Methods::roundk(duration_cast<milliseconds>(Utilities::Time::get_current()-start_judge_time).count()/1000.0,2)<<"s]\n";

cout<<"\nTotal points: "<<Utilities::Methods::roundk(config::statistic::cur_pts,2)<<"/"<<config::statistic::total_points<<".00 ("<<config::statistic::cur_ac<<"/"<<config::setup::NTEST<<")\n";