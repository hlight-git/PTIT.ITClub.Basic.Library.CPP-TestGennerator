#include "../Header/Setup.hpp"
#include <dirent.h>

bool cleanMode = true;

int main () {
    Problem_Info in4;
    Set_Info(in4);

    vector <string> solution;
    struct dirent *entry;
	DIR *dir = opendir("./");
    while ((entry = readdir(dir)) != NULL){
        string tmp = entry->d_name;
        if(tmp != "Comparator.cpp" && tmp.find(".cpp") != UINT32_MAX)
            solution.push_back(tmp.substr(0, tmp.size() - 4));
    }
    int methods = solution.size();
    int res[in4.number_of_test_case];
    double total[methods], tmp;

    mkdir("Temp");
    for (int i = 0; i < methods; i++){
        mkdir(string("./Temp/" + to_string(i+1)).c_str());
        if(!isExist(".\\" + solution[i]))
            system(string("g++ .\\" + solution[i] + ".cpp -o .\\" + solution[i]).c_str());
    	total[i] = 0;
    }
    
    for (int i=0; i<in4.number_of_test_case; i++) {
    	res[i] = 0;
    	tmp = 10;
    	cout << "- Test:" << i+1 <<endl;
    	for(int j = 0; j < methods; j++){
	    	clock_t tStart = clock();
	        string command = solution[j] + "< ../Test/" + to_string(i+1) + ".in > ./Temp/" + to_string(j+1) + '/' + to_string(i+1) + ".out";
	        system(command.c_str());
	        double Time = (double)(clock() - tStart)/CLOCKS_PER_SEC;
	    	printf("	+ Method %d: %.7fs\n",j+1, Time);
	    	total[j] += Time;
	    	if(tmp > Time){
	    		tmp = Time;
	    		res[i] = j+1;
			}
	    }
    }
    for (int i = 0; i < methods; i++){
    	remove(solution[i].c_str());
        remove(string(solution[i] + ".exe").c_str());
    }
    if(cleanMode)   system ("rmdir /s /q \"./Temp\"");
    cout << "***Result:" << endl;
    for(int i=0; i<in4.number_of_test_case; i++)
    	cout << "Test " << i+1 << ": " << res[i] << ' ' << "win.\n";
	for(int i = 0; i < methods; i++)
    	cout << "Total time of method " << i+1 << ": " << total[i] << endl;
    return 0;
}