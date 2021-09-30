#include "../Header/Setup.hpp"
#include <sys/stat.h>

int main(){
    cout << "> INPUT TEST CASES CREATOR - START:\n";
    Problem_Info in4;
    Set_Info(in4);
    srand(time(NULL));
    string address = "Test";
    if(!isExist("Generator.exe"))
        address = "..\\" + address;
    bool exist_dir = mkdir(address.c_str());
    if(!exist_dir)   cout << "\t-    Create folder \"Test\" successfully!\n";
    cout << "\t-    Create " << in4.number_of_test_case << " input test case:\n";
    int normal = in4.number_of_test_case;
    #ifdef NIGHTMARE
        normal -= quantity;
    #endif
    for (int i = 0; i < in4.number_of_test_case; i++){
        string dir = address + '/' + to_string(i) + ".in";
        cout << "\t     +  Creating...";
        ofstream fout(dir.c_str());
            if      (i < normal/3)     Easy(fout);
            else if (i < 2*normal/3)     Medium(fout);
            else if (i < normal)    Hard(fout);
            else{
                #ifdef NIGHTMARE
                    NightMare(fout);
                #endif
            }
        fout.close();
        cout << "\33[2K\033[A\n\t     +    ";
        if(error_check(dir, in4) == "ERROR") return 1;
        cout << "Create input test case " << i << " successfully!" << endl;
    }
    cout << "\t=> Everything seems to be good!\n";
    cout << "INPUT TEST CASES CREATOR - END.\n";
    return 0;
}

