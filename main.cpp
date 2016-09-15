#include <iostream>

#include "kmatchcore.h"
#include "kbbs.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    KMatchCore * pMatchCore = new KBBS();
    pMatchCore->imgload("E://test.jpg","E://tmp.jpg");
    pMatchCore->run_match();
    pMatchCore->show_similar_map();
    delete pMatchCore;
    return 0;
}

