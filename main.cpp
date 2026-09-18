#include <iostream>
#include <string>
#include <cctype>

void tfm_upperStr(std::string& nama) {
    for (char& c : nama) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
}

void boom(const std::string& msg) {
    while (true) {
        std::cout << msg << '\n';
    }
}

std::string inp_upr_string() {
    std::string inp;
    std::getline(std::cin, inp);
    tfm_upperStr(inp);
    return inp;
}

void scrMain(const std::string& usrOpsec) {
    std::string ansOpsec;

    std::cout << "Hey, don't say that!\n";
    ansOpsec = inp_upr_string();
    
}

int main() {
    std::string hitam;
    std::string hitam_upr;
    std::getline(std::cin, hitam);
    hitam_upr = hitam;
    tfm_upperStr(hitam_upr);
    
    if (hitam_upr == "GG FUGGING EZ") scrMain();

    if (hitam_upr == "ATHALLA") boom("WUWU purple heart");
    if (hitam_upr == "FADLAN") boom("otw di-doxx sama rio :3");
    if (hitam_upr == "EZA") boom("yoda mati, twillight sparkle goated");

    std::cout << "Hello " << hitam << " :D" <<'\n'; 

    return 0;
}
