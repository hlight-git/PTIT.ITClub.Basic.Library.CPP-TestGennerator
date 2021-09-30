#include "../Header/Setup.hpp"
#include <sys/stat.h>

int main(){
    Problem_Info in4;
    Set_Info(in4);
    cout << "> OUTPUT TEST CASES CREATOR - START:\n";
    string fname = "MainSolution";
    fname = solution_check(fname);
    string fpath = ".\\Test\\";
    if(fname[1] == '.')
        fpath = "." + fpath;
    for (int i = 0; i < in4.number_of_test_case; i++) {
        if(error_check(fpath + to_string(i) + ".in", in4) == "ERROR") return 1;
        cout << "\t     +  Creating...";
        string command = fname + "<" + fpath + to_string(i) + ".in > " + fpath + to_string(i) + ".out";
    	clock_t tStart = clock();
        system(command.c_str());
        double time_cost = (double)(clock() - tStart)/CLOCKS_PER_SEC;
        cout << "\33[2K\033[A\n\t     +    ";
        if(error_check(fpath + to_string(i) + ".out", in4) == "ERROR") return 1;
        cout << "Create output test case " << i << " suscessfully in " << setprecision(5) << fixed << time_cost << " seconds!\n";
    }
    cout << "\t=> Everything seems to be good!\n";
    cout << "OUTPUT TEST CASES CREATOR - END.\n";
    return 0;
}
