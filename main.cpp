#include <iostream>

#include "kmatchcore.h"
#include "kbbs.h"

using namespace std;

int main()
{
    KMatchCore * pMatchCore = new KBBS(5);
//    pMatchCore->imgload("D://MATLAB//Prjs//BBS_code_and_data_release_v1.0//data//pair0001_frm2_bolt_0052.jpg"
//                        ,"D://MATLAB//Prjs//BBS_code_and_data_release_v1.0//data//pair0001_frm1_bolt_0032.jpg"
//                        ,"D://MATLAB//Prjs//BBS_code_and_data_release_v1.0//data//pair0001_frm1_bolt_0032.txt");
    pMatchCore->imgload("E://b.jpg"
                        ,"E://savetmp.jpg");
    pMatchCore->run_match();
    cout << "time used: " << difftime(std::time(nullptr), pMatchCore->get_begin_time()) << "s" << endl;
    pMatchCore->show_similar_map("E://map.bmp");
    pMatchCore->save_match_image("E://result.jpg");
    delete pMatchCore;
    return 0;
}

