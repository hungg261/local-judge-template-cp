void Init(){
    if(config::setup::fastIO){
        ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    }

    Rand_machine::seeding();
    cin.precision(2);

    if(!config::setup::onetest){
        File::setup();
    }
}
