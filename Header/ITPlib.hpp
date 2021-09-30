#ifndef ITPTIT_HPP
#define ITPTIT_HPP
    /**
     * @Description: File header chứa thư viện riêng tự viết để dành cho việc sinh test case phục vụ các contest clb IT.
     * @Author: HlighT.
     * @Facebook: fb.com/hlight.fb
     * @Date Created: 22/08/2021.
     * @Version: 1.1.0
     * @Modifier: HlighT.
     * @Last Date Modified: 29/09/2021.
    */
            #include <bits/stdc++.h>
            #include <assert.h>
            #include <direct.h>
            #include <type_traits>
            using namespace std;
            typedef long long ll;
            typedef double db;
            
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            class Problem_Info{
                public:
                    int number_of_test_case;
                    int limit_size_of_file;
                    Problem_Info(){
                        number_of_test_case = 15;
                        limit_size_of_file = 500000;
                    }
                    Problem_Info(const int& n, const int& l){
                        number_of_test_case = n;
                        limit_size_of_file = l;
                    }
            };
            class BigInt{
                public:
                    int sign;
                    string s;
                    BigInt():s(""){}
                    BigInt(string x){
                        *this = x;
                    }
                    BigInt(int x){
                        *this = to_string(x);
                    }
                    BigInt(long long x){
                        *this = to_string(x);
                    }
                    BigInt negative(){
                        BigInt x = *this;
                        x.sign *= -1;
                        return x;
                    }
                    BigInt normalize(int newSign){
                        for (int a = s.size() - 1; a > 0 && s[a] == '0'; a--)
                            s.erase(s.begin() + a);
                        sign = (s.size() == 1 && s[0] == '0' ? 1 : newSign);
                        return *this;
                    }
                    void operator=(string x){
                        int newSign = (x[0] == '-' ? -1 : 1);
                        s = (newSign == -1 ? x.substr(1) : x);
                        reverse(s.begin(), s.end());
                        this->normalize(newSign);
                    }
                    bool operator==(const BigInt& x) const{
                        return (s == x.s && sign == x.sign);
                    }
                    bool operator<(const BigInt& x) const{
                        if (sign != x.sign)
                            return sign < x.sign;
                        if (s.size() != x.s.size())
                            return (sign == 1 ? s.size() < x.s.size() : s.size() > x.s.size());
                        for (int a = s.size() - 1; a >= 0; a--)
                            if (s[a] != x.s[a])
                                return (sign == 1 ? s[a] < x.s[a] : s[a] > x.s[a]);
                        return false;
                    }
                    bool operator<=(const BigInt& x) const{
                        return (*this < x || *this == x);
                    }
                    bool operator>(const BigInt& x) const{
                        return (!(*this < x) && !(*this == x));
                    }

                    bool operator>=(const BigInt& x) const{
                        return (*this > x || *this == x);
                    }
                    BigInt operator+(BigInt x){
                        BigInt curr = *this;
                        if (curr.sign != x.sign)
                            return curr - x.negative();
                        BigInt res;
                        for (int a = 0, carry = 0; a < s.size() || a < x.s.size() || carry; a++) {
                            carry += (a < curr.s.size() ? curr.s[a] - '0' : 0) + (a < x.s.size() ? x.s[a] - '0' : 0);
                            res.s += (carry % 10 + '0');
                            carry /= 10;
                        }
                        return res.normalize(sign);
                    }
                    BigInt operator-(BigInt x){
                        BigInt curr = *this;
                        if (curr.sign != x.sign)
                            return curr + x.negative();
                        int realSign = curr.sign;
                        curr.sign = x.sign = 1;
                        if (curr < x)
                            return ((x - curr).negative()).normalize(-realSign);
                        BigInt res;
                        for (int a = 0, borrow = 0; a < s.size(); a++) {
                            borrow = (curr.s[a] - borrow - (a < x.s.size() ? x.s[a] : '0'));
                            res.s += (borrow >= 0 ? borrow + '0' : borrow + '0' + 10);
                            borrow = (borrow >= 0 ? 0 : 1);
                        }
                        return res.normalize(realSign);
                    }
                    BigInt operator*(BigInt x){
                        BigInt res("0");
                        for (int a = 0, b = s[a] - '0'; a < s.size(); a++, b = s[a] - '0') {
                            while (b--)
                                res = (res + x);
                            x.s.insert(x.s.begin(), '0');
                        }
                        return res.normalize(sign * x.sign);
                    }
                    BigInt operator/(BigInt x){
                        if (x.s.size() == 1 && x.s[0] == '0')
                            x.s[0] /= (x.s[0] - '0');
                        BigInt temp("0"), res;
                        for (int a = 0; a < s.size(); a++)
                            res.s += "0";
                        int newSign = sign * x.sign;
                        x.sign = 1;
                        for (int a = s.size() - 1; a >= 0; a--) {
                            temp.s.insert(temp.s.begin(), '0');
                            temp = temp + s.substr(a, 1);
                            while (!(temp < x)) {
                                temp = temp - x;
                                res.s[a]++;
                            }
                        }
                        return res.normalize(newSign);
                    }
                    BigInt operator%(BigInt x){
                        if (x.s.size() == 1 && x.s[0] == '0')
                            x.s[0] /= (x.s[0] - '0');
                        BigInt res("0");
                        x.sign = 1;
                        for (int a = s.size() - 1; a >= 0; a--) {
                            res.s.insert(res.s.begin(), '0');
                            res = res + s.substr(a, 1);
                            while (!(res < x))
                                res = res - x;
                        }
                        return res.normalize(sign);
                    }
                    string toString() const{
                        string ret = s;
                        reverse(ret.begin(), ret.end());
                        return (sign == -1 ? "-" : "") + ret;
                    }
                    BigInt toBase10(int base){
                        BigInt exp(1), res("0"), BASE(base);
                        for (int a = 0; a < s.size(); a++) {
                            int curr = (s[a] < '0' || s[a] > '9' ? (toupper(s[a]) - 'A' + 10) : (s[a] - '0'));
                            res = res + (exp * BigInt(curr));
                            exp = exp * BASE;
                        }
                        return res.normalize(sign);
                    }
                    BigInt toBase10(int base, BigInt mod){
                        BigInt exp(1), res("0"), BASE(base);
                        for (int a = 0; a < s.size(); a++) {
                            int curr = (s[a] < '0' || s[a] > '9' ? (toupper(s[a]) - 'A' + 10) : (s[a] - '0'));
                            res = (res + ((exp * BigInt(curr) % mod)) % mod);
                            exp = ((exp * BASE) % mod);
                        }
                        return res.normalize(sign);
                    }
                    string convertToBase(int base){
                        BigInt ZERO(0), BASE(base), x = *this;
                        string modes = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                        if (x == ZERO)
                            return "0";
                        string res = "";
                        while (x > ZERO) {
                            BigInt mod = x % BASE;
                            x = x - mod;
                            if (x > ZERO)
                                x = x / BASE;
                            res = modes[stoi(mod.toString())] + res;
                        }
                        return res;
                    }
                    BigInt toBase(int base){
                        return BigInt(this->convertToBase(base));
                    }
                    friend ostream& operator<<(ostream& os, const BigInt& x){
                        os << x.toString();
                        return os;
                    }
            };
            /* File and error checker */
                int fsize(const string& dir){
                    ifstream fin(dir, ifstream::ate | ifstream::binary);
                    int size = fin.tellg();
                    fin.close();
                    return size;
                }
                bool fempty(const string& dir){
                    if(fsize(dir))  return false;
                    return true;
                }
                bool isExist(const string& fname){
                    ifstream fin(fname, ios::in);
                    bool res = fin.good();
                    fin.close();
                    return res;
                }
                string solution_check(string fname){
                    if(isExist("Generator.exe"))
                        fname = ".\\Solutions\\" + fname;
                    else 
                        fname = "..\\Solutions\\" + fname;
                    if(!isExist(fname))
                        system(string("g++ .\\" + fname + ".cpp -o .\\" + fname).c_str());
                    return fname;
                }
                string error_check(const string& dir, const Problem_Info& inf){
                    ifstream fin(dir, ios::in);
                    if(!fin.good())
                        cout << "ERROR: File not found!";
                    else if(fempty(dir))
                        cout << "ERROR: An empty file!";
                    else if(fsize(dir) >= inf.limit_size_of_file)
                        cout << "ERROR: File size limit exceeded, it should be less than" << (inf.limit_size_of_file/1024.0) << "kb, not " << (fsize(dir)/1024.0) << "kb!";
                    else return "nothing";
                    fin.close();
                    cout << "\nThe program was interrupted by the above error, please check again!";
                    return "ERROR";
                }
            /*  Random number   */
                ll randll(const ll& left, const ll& right){
                    return rng() % (right - left + 1) + left;
                }
                db randdb(const db& left, const db& right){
                    int l = ceil(left);
                    int r = floor(right);
                    db res = randll(l, r - 1);
                    string tail = "0.";
                    for(int i=0; i<14; i++)
                        tail += (char)(randll(0, 9) + '0');
                    return res + stod(tail);
                }
                //THIS ONE IS THE BETTER FOR RANDOM BIGINT.
                BigInt randBigInt(const int& number_of_digits){
                    string res = to_string(randll(1, 9));
                    for(int i = 1; i<number_of_digits; i++)
                        res += (char)(randll(0, 9) + '0');
                    return BigInt(res);
                }
                //THIS ONE IS NOT GOOD ENOUGH.
                template <class Type>
                    BigInt randBigInt(Type left, Type right){
                        BigInt sub = BigInt(right - left);
                        BigInt tmp = randBigInt(randll(0, sub.s.size()));
                        while(tmp >= sub)
                            tmp = randBigInt(randll(0, sub.s.size()));
                        return BigInt(left) + tmp;
                    }
                template <class Type>
                    Type random(Type left, Type right){
                        if(typeid(Type) == typeid(float) || typeid(Type) == typeid(double))
                            return randdb(left, right);
                        return randll(left, right);
                    }
                //NOT FOR BIGINT.
                template <typename Type>
                    vector <Type> randUniqueArr(const int& size, const Type& left, const Type& right){
                        map <Type, bool> seen;
                        vector <Type> res;
                        do{
                            Type tmp = random(left, right);
                            if(!seen[tmp]){
                                seen[tmp] = true;
                                res.push_back(tmp);
                            }
                        }while(res.size() < size);
                        return res;
                    }
            /*  Array shuffle - Note: có thể dùng hàm random_shuffle */
                //HÃY DÙNG "arrShuff (arr)"!
                template <class Type> 
                    void Array_Shuffle(Type &a, const int& size){
                        int SwapTurn = randll(size, randll(2, 3)*size);
                        while(SwapTurn--){
                            int x = randll(1, size) - 1;
                            int y = randll(1, size) - 1;
                            swap(a[x], a[y]);
                        }
                    }
                template <class Type>
                    void arrShuff(Type& arr){
                        int size = sizeof(arr)/sizeof(arr[0]);
                        Array_Shuffle(arr, size);
                    }
                template <class Type> 
                    void arrShuff(vector <Type>& arr){
                        Array_Shuffle(arr, arr.size());
                    }
            /*  Prime Numbers   */
                template <class Type>
                    bool isPrime(const Type& n){
                        if(n == 2 || n == 3)    return true;
                        if(n < 2 || n&1 == 0 || n%3 == 0)    return false;
                        for(Type i = 5; i*i <= n; i+=6){
                            if(n % i == 0)  return false;
                            if(n % (i+2) == 0)  return false;
                        }
                        return true;
                    }
                int primeTh(const int& th){
                    if(th < 1 || th > 5761455){
                        cout << "Beyond the scope of the data contained in the resource file!";
                        return -1;
                    }
                    string data = "./Resources/PrimeNumbers.txt";
                    if(!isExist("Generator.exe"))
                        data = '.' + data;
                    ifstream fin(data);
                    int cnt = 0;
                    int num;
                    while(fin >> num){
                        ++cnt;
                        if(cnt == th)                            
                            break;
                    }
                    fin.close();
                    return num;
                }
                vector <int> primeListBySerial(const int& left, const int& right){
                    string data = "./Resources/PrimeNumbers.txt";
                    if(!isExist("Generator.exe"))
                        data = '.' + data;
                    ifstream fin(data);
                        int cnt = 0;
                        int num;
                        vector <int> res;
                        while(fin >> num){
                            ++cnt;
                            if(cnt == left){
                                res.push_back(num);
                                break;
                            }
                        }
                        res.resize(right - left + 1);
                        for(int i=1; i <= right-left; i++)
                            fin >> res[i];
                    fin.close();
                    return res;
                }
                vector <int> primeListByValue(const int& left, const int& right){
                    string data = "./Resources/PrimeNumbers.txt";
                    if(!isExist("Generator.exe"))
                        data = '.' + data;
                    ifstream fin(data);
                        int num;
                        vector <int> res;
                        while(fin >> num){
                            if(num > right)
                                break;
                            if(left <= num)
                                res.push_back(num);
                        }
                    fin.close();
                    return res;
                }
                vector <ll> EratosthenesOnRange(const ll& left, const ll& right){
                    vector <ll> res;
                    vector <bool> isit(right - left + 1, true);
                    for (ll i = 2; i*i <= right; ++i)
                        for (ll j = max(i*i, (left+i-1) / i*i); j <= right; j += i)
                            isit[j - left] = false;
                    if (1 >= left)
                        isit[1 - left] = false;
                    for (ll x = left; x <= right; ++x)
                        if (isit[x - left])
                            res.push_back(x);
                    return res;
                }
            /*    Palindrome    */
                template <class Type>
                    string toString(const Type& var){
                        ostringstream oss;
                        oss << var;
                        return oss.str();
                    }
                template <class Type>
                    bool isPalindrome(const Type& var){
                        string tmp = toString(var);
                        return tmp == string(tmp.rbegin(), tmp.rend());
                    }
                template <class Array>
                    bool isPalindromeArray(const Array& arr){
                        int size = sizeof(arr)/sizeof(arr[0]);
                        for(int i=0, j=size-1; i < j; i++, j--)
                            if(arr[i] != arr[j])
                                return false;
                        return true;
                    }
                template <class SC>
                    bool isPalindromeSContainer(const SC& ctn){
                        return SC(ctn.rbegin(), ctn.rend()) == ctn;
                    }
            /*  Some function   */
                template <class Type>
                    bool isInteger(const Type& num){
                        if(typeid(Type) == typeid(float) || typeid(Type) == typeid(double))
                            return num == (int)num;
                        string tmp = toString(num);
                        return tmp.find('.') == UINT32_MAX;
                    }
                template <class Type>
                    bool isSquareNum(const Type& num){
                        return sqrt(num)*sqrt(num) == num; 
                    }
                template <class Type>
                    map <int, int> factorAnalyze(Type num){
                        string data = "./Resources/PrimeNumbers.txt";
                        if(!isExist("Generator.exe"))
                            data = '.' + data;
                        ifstream fin(data);
                            map <int, int> res;
                            Type prime;
                            while(fin >> prime){
                                if(prime * prime > num)
                                    break;
                                int exp = 0;
                                while(num % prime == 0){
                                    ++exp;
                                    num /= prime;
                                }
                                if(exp) res[prime] = exp;
                            }
                            if(num > 1) res[(int)num] = 1;
                        fin.close();
                        return res;
                    }
                template <class Type>
                    vector <ll> divisorsOf(const Type& num){
                        vector <ll> res(1, 1);
                        for(const auto &div:factorAnalyze(num)){
                            vector <ll> tmp(res);
                            for(ll exp = 0, base = div.first; exp<div.second; exp++, base *= div.first)
                                for(const ll &ele:tmp)
                                    res.push_back(base * ele);
                        }
                        sort(res.begin(), res.end());
                        return res;
                    }
                template <class Type>
                    int numOfDivisors(const Type& num){
                        int res = 1;
                        for(const auto &ele:factorAnalyze(num))
                            res *= ele.second + 1;
                        return res;
                    }
    /**
     * Contributors:...No one has contributed yet.
    */
#endif