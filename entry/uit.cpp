#include <bits/stdc++.h>
#include <cxxopts.hpp>
using namespace std;

void uit_die(const string &s)
{
    cerr << "Error: " << s << endl;
    exit(1);
}

string read_all(istream &is)
{
    int c; string ret;
    while((c = is.get()) != char_traits<char>::eof())
        ret += c;
    return ret;
}
string read_all(const string &fn)
{
    ifstream is(fn);
    try
    {
        return read_all(is);
    }
    catch(exception &e)
    {
        uit_die("cannot read from " + fn);
    }
}

string translate(const string &s)
{
    return "#include <bits/stdc++.h>\nusing namespace std;\n" + s;
}

int main(int argc, char **argv)
{
    string prog;
    reference_wrapper<ostream> ouf(cout);
    {
        using namespace cxxopts;
        Options options("uit", "UINT Translator");
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
        if(result.count("input"))
            prog = read_all(result["input"].as<string>());
        else
            prog = read_all(cin);
        if(result.count("output"))
        {
            static ofstream ofs(result["output"].as<string>());
            ouf = ofs;
        }
    }
    ouf.get() << translate(prog) << flush;
    return 0;
}
