#include "../Header/Setup.hpp"
#include <dirent.h>

bool cleanMode = true;

int main () {
    Problem_Info in4;
    Set_Info(in4);

    vector <string> solutions;
    struct dirent *entry;
	DIR *dir = opendir("./");
    while ((entry = readdir(dir)) != NULL){
        string tmp = entry->d_name;
        if(tmp != "Comparator.cpp" && tmp.find(".cpp") != UINT32_MAX)
            solutions.push_back(tmp.substr(0, tmp.size() - 4));
    }
    if(solutions.empty()){
        cout << "Didn't find any solutions, make sure they exist in the lab!";
        return 0;
    }
    int methods = solutions.size();
    string res[in4.number_of_test_case];
    double total[methods], tmp;

    mkdir("Temp");
    for (int i = 0; i < methods; i++){
        mkdir(string("./Temp/" + to_string(i+1)).c_str());
        if(!isExist(".\\" + solutions[i]))
            system(string("g++ .\\" + solutions[i] + ".cpp -o .\\" + solutions[i]).c_str());
    	total[i] = 0;
    }
    
    for (int i=0; i<in4.number_of_test_case; i++) {
    	res[i] = "";
    	tmp = 10;
    	cout << "- Test:" << i+1 <<endl;
    	for(int j = 0; j < methods; j++){
	    	clock_t tStart = clock();
	        string command = solutions[j] + "< ../Test/" + to_string(i+1) + ".in > ./Temp/" + to_string(j+1) + '/' + to_string(i+1) + ".out";
	        system(command.c_str());
	        double Time = (double)(clock() - tStart)/CLOCKS_PER_SEC;
            cout << "	+ Method " << solutions[j] << ": " << setprecision(7) << fixed << Time << "s\n";
	    	total[j] += Time;
	    	if(tmp > Time){
	    		tmp = Time;
	    		res[i] = solutions[j];
			}
	    }
    }
    if(cleanMode)   system ("rmdir /s /q \"./Temp\"");
    cout << "***Result:" << endl;
    for(int i = 0; i < in4.number_of_test_case; i++)
    	cout << "Test " << i+1 << ": " << res[i] << ' ' << "win.\n";
	for(int i = 0; i < methods; i++)
    	cout << "Total time of " << solutions[i] << ": " << total[i] << endl;
    for(int i = 0; i < methods; i++){
    	remove(solutions[i].c_str());
        remove(string(solutions[i] + ".exe").c_str());
    }
    return 0;
}