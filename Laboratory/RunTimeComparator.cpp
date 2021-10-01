#include "../Header/Setup.hpp"
#include <dirent.h>

bool cleanMode = true;

int main () {
    Problem_Info in4;
    Set_Info(in4);

    vector <string> methods;
    struct dirent *entry;
	DIR *dir = opendir("./Methods/");
    while ((entry = readdir(dir)) != NULL){
        string tmp = entry->d_name;
        if(tmp.find(".cpp") != UINT32_MAX)
            methods.push_back(tmp.substr(0, tmp.size() - 4));
    }
    if(methods.empty()){
        cout << "Didn't find any solutions, make sure they exist in the folder \"Methods\"!";
        return 0;
    }
    int files = methods.size();
    string res[in4.number_of_test_case];
    double total[files], tmp;

    mkdir("Temp");
    for (int i = 0; i < files; i++){
        mkdir(string("./Temp/" + methods[i]).c_str());
        if(!isExist("./Methods/" + methods[i])){
            if(!system(string("g++ ./Methods/" + methods[i] + ".cpp -o ./" + methods[i]).c_str()))
                cout << methods[i] << " compiled successfully!\n";
        }
    	total[i] = 0;
    }
    
    bool interrupted = false;

    for (int i=0; i<in4.number_of_test_case; i++) {
    	res[i] = "";
    	tmp = 10;
    	cout << "- Test " << i << ':' << endl;
    	for(int j = 0; j < files; j++){
	    	clock_t tStart = clock();
	        string command = methods[j] + " < ../Test/" + to_string(i) + ".in > ./Temp/" + methods[j] + '/' + to_string(i) + ".out";
            if(system(command.c_str())){
                interrupted = true;
                break;
            }
	        double Time = (double)(clock() - tStart)/CLOCKS_PER_SEC;
            cout << "	+ Method " << methods[j] << ": " << setprecision(3) << fixed << Time << "s.\n";
	    	total[j] += Time;
	    	if(tmp > Time){
	    		tmp = Time;
	    		res[i] = methods[j];
			}
	    }
        if(interrupted)
            break;
    }
    if(cleanMode)   system ("rmdir /s /q \"./Temp\"");
    if(!interrupted){
        cout << "***Result:" << endl;
        for(int i = 0; i < in4.number_of_test_case; i++)
            cout << "Test " << i+1 << ": " << res[i] << ' ' << "win.\n";
        for(int i = 0; i < files; i++)
            cout << "Total time of " << methods[i] << ": " << total[i] << endl;
    }
    for(int i = 0; i < files; i++){
    	remove(methods[i].c_str());
        remove(string(methods[i] + ".exe").c_str());
    }
    return 0;
}