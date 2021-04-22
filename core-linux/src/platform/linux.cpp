#include <string>
#include <libgen.h>
#include <stdio.h>
#include "log.h"

using namespace std;

namespace linux {
    string getDirectoryName(string filename){
        return dirname((char*)filename.c_str());
    }

    string execCommand(string command){
        std::array<char, 128> buffer;
        std::string result = "";
        std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe) {
            WARN() << "linux::execCommand: Pipe open failed.";
        }
        else {
            while (!feof(pipe.get())) {
                if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
                    result += buffer.data();
            }
        }
        return result;
    }
}