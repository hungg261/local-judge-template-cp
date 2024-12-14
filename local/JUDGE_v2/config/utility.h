namespace Utilities{
    namespace Methods{
        // Lam tron so toi k chu so thap phan (=> string)
        string roundk(double number, int k){
            stringstream ss;
            ss << fixed << setprecision(k) << number;
            return ss.str();
        }

        // Them cac chu cai vao truoc de can bang xau (vd: 1,2,3 -> 01,02,03)
        string pad(int n,int width=2,char target='0'){
            stringstream padder;
            padder<<setw(width)<<setfill(target)<<n;
            return padder.str();
        }
    }

    namespace Time{
        // Lay thoi gian hien tai qua format (HH::MM::DD)
        string get_time(){
            time_t now=time(NULL);
            tm *ltm = localtime(&now);

            stringstream formatted;

            using namespace Utilities::Methods;
            formatted<<pad(ltm->tm_hour)<<":"<<pad(ltm->tm_min)<<":"<<pad(ltm->tm_sec)<<" - "<<pad(ltm->tm_mday)<<"/"<<pad(1+ltm->tm_mon)<<"/"<<1900+ltm->tm_year;
            return formatted.str();
        }

        string get_time2(){
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);

            std::stringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
            return ss.str();
        }

        time_point<std::chrono::high_resolution_clock> get_current(){
            return high_resolution_clock::now();
        }
    }

    // BIG NUM MODULE:
    namespace BIGINT{
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
    }
}