#ifndef __LESALE_H__
#define __LESALE_H__

#include "server_LogEntry.h"
#include <string>
#include <iostream>

class LESale : public LogEntry
{
    const std::string& tren;
    const std::string& anden;

    private:
        virtual ~LESale() { }

    public:
        LESale( const std::string& tren, const std::string& anden );

        virtual void print( std::ostream& out ) const;
};

#endif /* __LESALE_H__ */
