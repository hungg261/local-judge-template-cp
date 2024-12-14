namespace Rand_machine{
    const int   RANDOM_SEED=26012010;
    const bool  complete_rand=config::setup::RAND_ALL;
    mt19937_64 rng;
    mt19937 rng32;

    void seeding(){
        if(complete_rand){
            rng.seed(chrono::steady_clock::now().time_since_epoch().count());
        }
        else{
            rng.seed(RANDOM_SEED);
        }
    }

    namespace Random{
        // Sinh ngau nhien tu l toi h
        int Rand(int l,int h){
            assert(l <= h);
            uniform_int_distribution<int> uni(l, h);
            return uni(rng);
        }

        // Sinh ngau nhien tu l toi h (nguon: VNOI)
        long long Rand_VNOI(long long L, long long R) {
            assert(L <= R);
            return L + rng() % (R - L + 1);
        }

        // Sinh ki tu ngau nhien
        char randomChar(char l,char h){
            return (char)Rand(l,h);
        }

        // Sinh bigint ngau nhien
        string bigRand(int len){
            string number="";
            number+=randomChar('1','9');
            --len;

            while(len--){
                number+=randomChar('0','9');
            }
            return number;
        }

        // Sinh xau ngau nhien
        string randomStr(int len,string characters="abcdefghijklmnopqrstuvwxyz"){
            string String="";
            int range=characters.size();

            while(len--){
                String+=characters[Rand(0,range-1)];
            }
            return String;
        }
    }
}
