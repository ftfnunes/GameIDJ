#include <iostream>

#ifndef GAMEIDJ_LOG_H
#define GAMEIDJ_LOG_H

using namespace std;

class Log {
public:
    static void LogMessage(string message);
    static void LogError(string message);
};


#endif //GAMEIDJ_LOG_H
