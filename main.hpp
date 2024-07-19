#include <iostream>
#include <chrono>
#include <string>
#include <sys/xattr.h>
#include <sys/types.h>
#include <fstream>
#include <cstring>
#include <cryptopp/cryptlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>
#include <iomanip>
#include <sstream>
#include <filesystem>
using namespace CryptoPP;

std::string generateIV(){
    AutoSeededRandomPool srp;
    SecByteBlock iv(AES::BLOCKSIZE);
    srp.GenerateBlock(iv, iv.size());
    std::string final(reinterpret_cast<const char*>(iv.data()), iv.size());
    return final;
}
std::string getOsName(){
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
} 

std::string send(std::string text){
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    std::string milliseconds = std::to_string(ms);
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm* now_tm = std::localtime(&now_time_t);
    std::stringstream ss;
    ss << now_tm->tm_mday << "."
       << (now_tm->tm_mon + 1) << "."
       << (now_tm->tm_year + 1900) << " "
       << now_tm->tm_hour << "-"
       << now_tm->tm_min;
    std::string fln = ss.str() + ".ev2";
    std::ofstream file(fln);
    if(file.is_open()){
        file << text;
        file.close();
    }
    std::string ivMk = "user.rjiv.ev2";
    std::string iv = generateIV();
    std::string msMk = "user.utof.ev2";
    int result = setxattr(fln.c_str(), ivMk.c_str(), iv.c_str(), strlen(iv.c_str()), 0);
    if(result == 0){
        std::cout << "[eV2_alert] setxattr 1 complete. " << ivMk << std::endl;
    }
    else{
        std::cerr << "[eV2_critical] setxattr 1 failed. <eV2_destroy_all>" << std::endl;
        try{
            if(std::filesystem::remove(fln)){
                std::cout << "[eV2_alert] <eV2_destroy_all> success.";
            }
            else{
                std::cerr << "[eV2_alert] <eV2_base_error>: file not found?\n something broke.";
            }
        }
        catch(const std::filesystem::filesystem_error& e){
            std::cerr << "[eV2_critical] std::filesystem exception:\n" << e.what() << "<eV2_cpp_runtime_fatal>";
            return "";
        }
    }
    result = setxattr(fln.c_str(), msMk.c_str(), milliseconds.c_str(), strlen(milliseconds.c_str()), 0);
    if(result == 0){
        std::cout << "[eV2_alert] setxattr 2 complete. " << msMk << std::endl;
    }
    else{
        std::cerr << "[eV2_critical] setxattr 2 failed. <eV2_destroy_all>" << std::endl;
        try{
            if(std::filesystem::remove(fln)){
                std::cout << "[eV2_alert] <eV2_destroy_all> success.";
            }
            else{
                std::cerr << "[eV2_alert] <eV2_base_error>: file not found?\n something broke.";
            }
        }
        catch(const std::filesystem::filesystem_error& e){
            std::cerr << "[eV2_critical] std::filesystem exception:\n" << e.what() << "<eV2_cpp_runtime_fatal>";
            return "";
        }
    }
    return "success!";
}