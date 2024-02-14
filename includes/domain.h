#ifndef DOMAIN_H
#define DOMAIN_H

#include <iostream>
#include <iomanip>

using namespace std;

struct Domain
{
public:
    double _lower_bound;
    double _upper_bound;
    Domain(): _lower_bound(0), _upper_bound(0) {}
    Domain(double lower_bound, double upper_bound): _lower_bound(lower_bound), _upper_bound(upper_bound) {}
    friend ostream& operator << (ostream& outs, const Domain& other)
    {
        // outs<<"hi domain\n";
        outs<<"Domain: [ "<<other._lower_bound<<" | "<<other._upper_bound<<" ]";
        return outs;
    }  
};


#endif