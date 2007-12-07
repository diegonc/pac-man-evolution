#ifndef __LETERMINA_H__
#define __LETERMINA_H__

#include "server_LogEntry.h"
#include <string>
#include <iostream>

class LETermina : public LogEntry
{
    const std::string& tren;

    private:
        virtual ~LETermina() { }

    public:
        LETermina( const std::string& tren );

        virtual void print( std::ostream& out ) const;
};

#endif /* __LETERMINA_H__ */
