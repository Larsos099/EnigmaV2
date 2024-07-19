#include "main.hpp"
int main(){
    std::string cppver = {};
    std::string ev2ver = "Alpha1";
    if (__cplusplus == 202101L) cppver = "CPP23";
    else if (__cplusplus == 202002L) cppver = "CPP20";
    else if (__cplusplus == 201703L) cppver = "CPP17";
    else if (__cplusplus == 201402L) cppver = "CPP14";
    else if (__cplusplus == 201103L) cppver = "CPP11";
    else if (__cplusplus == 199711L) cppver = "CPP98";
    else cppver = "\npre-standard CPP:\n" + __cplusplus;
     
    std::cout << "Modern Enigma, aka EnigmaV2 "
              << ev2ver << std::endl
              << "- Lars Lindner 2024" << std::endl
              << "Details:" << std::endl
              << "eV2_" << cppver
              << " running on " << getOsName() <<":"<< std::endl;
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    std::string milliseconds = std::to_string(ms);
    if(milliseconds.size() < 16){
        milliseconds.resize(16, '0');
    }
    if(milliseconds.size() > 16){
        milliseconds.resize(16);
    }
    std::string input = "";
    while(true){
        std::cout << "<eV2> " << std::flush;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        std::vector<std::string> tokens;
        std::string token;

        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) {
            continue;
        }

        std::string command = tokens[0];
        if(command == "exit"){
            std::cout << "goodbye!";
            return 99;
        }
        else if(command == "help"){
            std::cout << "EnigmaV2 help: (" << ev2ver << ")" << std::endl
                      << "Avaible Commands:\n"
                      << "help -> displays this help message\n"
                      << "exit -> Exits the eV2 Software.\n"
                      << "send -> send message to someone\n"
                      << "inbox -> check your inbox\n"
                      << "shutdown -> Shuts down your eV2 hardware\n"
                      << "restart -> Restarts your eV2 hardware\n"
                      << "social -> Displays all important information for communication\n"
                      << "debug -> Displays debug info\n";

        }
        else if(command == "send"){
            std::cout << "Type your message: \n";
            std::string txt = {};
            std::cin >> txt;
            std::cout << txt;
            send(txt);
        }
        else{
            std::cout << "Incorrect eV2 Command. type \"help\" for the help page.\n";
        }
    }
    return 0;
}