#ifndef __LEENTRA_H__
#define __LEENTRA_H__

#include "server_LogEntry.h"
#include <string>
#include <iostream>

class LEEntra : public LogEntry
{
    const std::string& tren;
    const std::string& anden;
    int espera;

    private:
        virtual ~LEEntra() { }

    public:
        LEEntra( const std::string& tren, const std::string& anden, int t );

        virtual void print( std::ostream& out ) const;
};

#endif /* __LEENTRA_H__ */
