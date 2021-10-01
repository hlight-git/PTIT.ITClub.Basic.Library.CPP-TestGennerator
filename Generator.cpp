#include "Header/ITPlib.hpp"
#include <windows.h>
// #include <strsafe.h>

bool cleanMode = false;

bool pyInstalled(){
    FILE *cmd;
	char content[100];
	cmd = popen("python --version", "r");
	while (fgets(content, sizeof(content), cmd) != NULL)
    	if(string(content)[0] == 'P')
            return true;
    return false;
}

// void selfDestruct(){
//     TCHAR szModuleName[MAX_PATH];
//     TCHAR szCmd[2 * MAX_PATH];
//     STARTUPINFO si = {0};
//     PROCESS_INFORMATION pi = {0};
//     GetModuleFileName(NULL, szModuleName, MAX_PATH);
//     StringCbPrintf(szCmd, 2 * MAX_PATH, TEXT("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\""), szModuleName);
//     CreateProcess(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
//     CloseHandle(pi.hThread);
//     CloseHandle(pi.hProcess);
// }

int main(){
    int interrupted = 0;
    if(!isExist(".\\Creator\\InCreator"))
        system("g++ .\\Creator\\InCreator.cpp -o .\\Creator\\InCreator");
    interrupted = system(".\\Creator\\InCreator");
    remove(".\\Creator\\InCreator");
    remove(".\\Creator\\InCreator.exe");
    if(interrupted){
        cout << endl;
        system("pause");
        // if(cleanMode)   selfDestruct();
        return 0;
    }
    if(!isExist(".\\Creator\\OutCreator"))
        interrupted = system("g++ .\\Creator\\OutCreator.cpp -o .\\Creator\\OutCreator");
    interrupted = system(".\\Creator\\OutCreator");
    remove(".\\Creator\\OutCreator");
    remove(".\\Creator\\OutCreator.exe");
    remove(".\\Solutions\\MainSolution");
    remove(".\\Solutions\\MainSolution.exe");
    if(interrupted){
        cout << endl;
        system("pause");
        // if(cleanMode)   selfDestruct();
        return 0;
    }
    Sleep(1000);
    cout << endl;
    if(pyInstalled()){
        interrupted = system("python .\\Packager.py");
        if(interrupted){
            cout << endl;
            system("pause");
            // if(cleanMode)   selfDestruct();
            return 0;
        }
        cout << "Packaged successfully!\n";
    }
    cout << "Everything is done!\n";
    system("pause");
    // if(cleanMode)   selfDestruct();
    return 0;
}