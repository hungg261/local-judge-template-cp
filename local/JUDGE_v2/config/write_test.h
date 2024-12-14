// In ra test vao file log:
if((config::setup::writetest||isWrong)){
    File::logwr<<"- Input:\n"<<input.str().substr(0,min((int)input.str().size(),100LL))<<(input.str().size()>100?"...\n":"\n");
    ifstream out(config::setup::NAME + ".OUT"), ans(config::setup::NAME + ".ans");
    string outline, ansline;

    File::logwr<<"- Output:\n";
    while(getline(out,outline)){
        File::logwr<<outline<<'\n';
    }

    File::logwr<<"- Expected answer:\n";
    while(getline(ans,ansline)){
        File::logwr<<ansline<<"\n\n";
    }

    out.close();
}
