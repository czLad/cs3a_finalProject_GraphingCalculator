#ifndef FILEOUT_H
#define FILEOUT_H

#include "iomanip"
#include "iostream"
#include "fstream"
#include "string.h"

using namespace std;

class Fileout
{
public:
    Fileout(){}
    Fileout(const string& filename)
    {
        _filename = filename;
        // fout.open(_filename);
        // if(fout.fail())
        // {
        //     cout <<"Error opening "<<_filename<<"\n";
        //     exit(1);
        // }
    }
    void write_to_file(const string& data)
    {
        fout.open(_filename, fstream::app);
        if(fout.fail())
        {
            cout <<"Fileout Error opening "<<_filename<<"\n";
            exit(1);
        }
        fout << data << "\n";
        fout.close();
    }
    void overwrite_to_file(const string& data)
    {
        fout.open(_filename);
        if(fout.fail())
        {
            cout <<"Fileout Error opening "<<_filename<<"\n";
            exit(1);
        }
        fout << data << "\n";
        fout.close();
    }
    // void close_file()
    // {
    //     fout.close();
    // }
private:
    ofstream fout;
    string _filename;
};



#endif