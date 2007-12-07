#ifndef __LEPARA_H__
#define __LEPARA_H__

#include "server_LogEntry.h"
#include <string>
#include <iostream>

class LEPara : public LogEntry
{
    const std::string& tren;
    const std::string& anden;
    bool libre;

    private:
        virtual ~LEPara() { }

    public:
        LEPara( const std::string& tren, const std::string& anden, bool libre );

        virtual void print( std::ostream& out ) const;
};

#endif /* __LEPARA_H__ */
