#include "marathon/_base.hpp"
using namespace std;

int main(void) {
    string pwd = "C:/Users/81802/vscode/kuhaku";
    string rm = "rm " + pwd + "/score";
    system(rm.c_str());
    for (int i = 0; i < 50; ++i) {
        string txt = to_string(i);
        while (txt.size() < 4) txt.insert(txt.begin(), '0');
        txt += ".txt";

        string cmd = pwd + "/a.exe <" + pwd + "/tools/in/" + txt + " >" + pwd +
                     "/tools/out/" + txt + " 2>>" + pwd + "/score";
        system(cmd.c_str());
    }
    string cmd = pwd + "/sum.exe";
    system(cmd.c_str());

    return 0;
}
