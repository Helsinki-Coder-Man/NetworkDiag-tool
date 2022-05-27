#ifndef Windows.h;
#include<Windows.h>;
#elif
#include<unistd.h>;
#define _popen popen
#endif

#include <iostream>
#include<cstdio>
#include<memory>
#include<stdexcept>
#include<string>
#include<array>



/*

Writen by Noah P in 2022 for personal use, if you find yourself in the use of this software you are free to use it as you wish.
However, if you plan on uploading this software some place , please give credit to the original author(me)

- Noah P
*/





std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&_pclose)> _pipe(_popen(cmd, "r"), _pclose);
    if(!_pipe)
    {
        throw std::runtime_error("\n\n\nPIPE FAILED TO EXECUTE");
    }
    while(fgets(buffer.data(),buffer.size(),_pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

struct
{


    std::string arp()
    {
        return exec("arp -a");
    }

   


    std::string ipconf()
    {
        return exec("ipconfig");
    }


    std::string ping(std::string Ip_DNS)
    {
        std::string cmd = "Ping " + Ip_DNS;
        
        std::string output = exec(cmd.c_str()); Beep(850, 800);
        if(output == "Ping request could not find host "+ Ip_DNS + " Please check the name and try again.")
        {
            return "Invalid IP/DNS. Enter a new ip/dns";
        }
        else 
        {
        
            return output;
        
        }
    }

   
}net;
int main()
{
    char* buf = new char[250];
  
    std::cout << "\nNetwork diagnostics";
    std::cout << "\n\n\nCommands that will run:\n\n- Ping [IP or DNS]\n\n - Ipconfig\n\n - Arp [-a]\n\n\n\n";
   std::cout<< "====================================================================================================\n\nPing\n\n\n";
    std::cout << "Ping: "; std::cin >> buf;
    std::cout << net.ping(buf);
    delete buf;
    std::cin.get();
    buf = new char[250];
    std::cout << "====================================================================================================\n\n\nIpconfig\n\n\n";
    std::cin.get();
    std::cout << net.ipconf();
    std::cin.get();
    std::cout << "\n====================================================================================================\n\n\n\n\nArp\n\n";
    
    std::cout<<net.arp();
    std::cin.get();


}
