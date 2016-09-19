#include <iostream>

#include "kmatchcore.h"
#include "kbbs.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    KMatchCore * pMatchCore = new KBBS();
    pMatchCore->imgload("D://MATLAB//Prjs//BBS_code_and_data_release_v1.0//data//pair0001_frm2_bolt_0052.jpg"
                        ,"D://MATLAB//Prjs//BBS_code_and_data_release_v1.0//data//pair0001_frm1_bolt_0032.jpg"
                        ,"D://MATLAB//Prjs//BBS_code_and_data_release_v1.0//data//pair0001_frm1_bolt_0032.txt");
    pMatchCore->run_match();
    pMatchCore->show_similar_map();
    pMatchCore->save_match_image("E://result.jpg");
    delete pMatchCore;
    return 0;
}

