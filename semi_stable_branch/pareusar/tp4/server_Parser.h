#ifndef __PARSER_H__
#define __PARSER_H__

#define NEEDS_REDVIAL
#define NEEDS_TREN
#include "server_Forwards.h"

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <stdexcept>

class Parser {
    private:
        RedVial& red;
        void processLine( std::string& line );
        void agregar_vertice( const std::string& id, const std::string& tipo );
        void agregar_arista( const std::string& vId1,
                             const std::string& vId2,
                             const std::string& aId,
                             const std::string& tipo,
                             float peso );

    public:
        Parser( RedVial& red );
        void parseConfig( std::istream& fd );
        std::vector<Tren*> parseItinerario( std::istream& fd );

    public:
        class InvalidFormat : public std::runtime_error
        {
            public:
                InvalidFormat( const std::string& s ) : std::runtime_error(s)
                {

                }
        };
};

#endif /* __PARSER_H__ */
