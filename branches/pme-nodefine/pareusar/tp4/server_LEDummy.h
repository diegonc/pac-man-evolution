#ifndef __LEDUMMY_H__
#define __LEDUMMY_H__

#include "server_LogEntry.h"
#include <string>
#include <iostream>

// Para destrabar observadores.
class LEDummy : public LogEntry
{
    private:
        virtual ~LEDummy() { }

    public:
        LEDummy( ) { }

        virtual void print( std::ostream& out ) const { }
};

#endif /* __LEDUMMY_H__ */
