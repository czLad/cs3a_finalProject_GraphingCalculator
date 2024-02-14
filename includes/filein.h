#ifndef FILEIN_H
#define FILEIN_H

#include "iomanip"
#include "iostream"
#include "fstream"
#include "string.h"

using namespace std;

class Filein
{
public:
    Filein(){}
    Filein(const string& filename)
    {
        _filename = filename;
    }
    //Reads from file till it sees newline char
    string read_from_file()
    {
        const bool debug = false;
        string read_line;
        getline(fin, read_line, '\n');
        if(debug)
        {
            cout <<"read_line: "<<read_line<<"\n";
            cout <<"read_line.size(): "<<read_line.size()<<"\n";
        }
        return read_line;
    }
    void close_file()
    {
        fin.close();
    }
    void open_file()
    {
        fin.open(_filename);
        if(fin.fail())
        {
            cout <<"Filein Error opening "<<_filename<<"\n";
            exit(1);
        }
    }
private:
    string _filename;
    ifstream fin;
};


#endif