#include <fstream>
#include "Log.h"

void Log::LogMessage(string message) {
    ofstream file;
    file.open("log.txt", ios::app);
    file << message << endl;
    file.close();
}

void Log::LogError(string message) {
    LogMessage(message);
    exit(1);
}