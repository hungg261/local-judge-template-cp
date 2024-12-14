namespace File{
    ofstream logwr;

    void clear_contents(string PATH){
        ofstream file(PATH,ios::trunc);
        file.close();
    }

    void setup(){
        logwr.open(("Judges\\[JUDGE] "+config::setup::CODE+".log"));

        logwr<<"Problem: "<<config::setup::CODE<<"\n"<<"Judge Time: "<<Utilities::Time::get_time();
        logwr<<"\n\n-------------------- JUDGE --------------------\n";
    }
}
