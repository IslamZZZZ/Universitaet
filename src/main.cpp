#include <iostream>
#include <vector>
#include <vector>
#include <cmath>
#include <fstream>
#include "../include/rpn.h"

using namespace std;

int main() {
    cout << "Hallo, Deutschland und Nederland!" << endl;

    auto beispiel = reading_rpn();

    cout << beispiel.size() << endl;
    
    for(auto tokens : beispiel) {
        cout << "result is " << count_rpn(tokens) << endl;
    }

    writing_rpn(beispiel);



    return 0;
}