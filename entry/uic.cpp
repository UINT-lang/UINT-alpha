#include <bits/stdc++.h>
#include <cxxopts.hpp>
#include <unistd.h>
using namespace std;
using namespace cxxopts;

void uic_die(const string &s)
{
    cerr << "Error: " << s << endl;
    exit(1);
}

int main(int argc, char **argv)
{
    Options options("uic", "UINT Compiler");
    options.add_options()
        ("h,help", "Print help")
        ("i,input", "Set input file", value<string>())
        ("o,output", "Set output file", value<string>())
    ;
    auto result = options.parse(argc, argv);
    if(result.count("help"))
    {
        cout << options.help() << endl;
        return 0;
    }
    
    string ifn, ofn;
    if(result.count("input"))
        ifn = result["input"].as<string>();
    else
        uic_die("no input file specified");
    if(result.count("output"))
        ofn = result["output"].as<string>();
    else
        uic_die("no output file specified");
    
    string uit = string(get_current_dir_name()) + "/" + argv[0];
    uit[uit.size() - 1] = 't';
    string cmd;
    cmd += "bash -c \"";
        cmd += uit + " -i " + ifn;
    cmd += " | ";
        cmd += "g++ -O2 --std=c++17 -xc++ - -o " + ofn;
    cmd += "\"";
    // cout << cmd << endl;
    return system(cmd.c_str());
}
