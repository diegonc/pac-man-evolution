#ifndef __STRINGUTIL_H__
#define __STRINGUTIL_H__

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

namespace StringUtil
{
        class ConversionInvalida : public std::runtime_error
        {
            public:
                ConversionInvalida( std::string s ) : std::runtime_error( s )
                {

                }
        };

        const char* buscarToken( const char* str, char token );

        const char* saltearToken( const char* str, char token );

        void nuevaPieza( std::vector<std::string>& destino,
                                const char* inicio,
                                const char* fin );

        std::vector<std::string> explode( const char* str, char token );

        template<class T>
        inline void convertir( const std::string& str, T& t )
            throw( ConversionInvalida )
        {
            std::istringstream ss( str );
            ss >> t;
            if( ss.fail() )
                throw ConversionInvalida( str + " no se puede convertir. " );
        }

        inline void convertir( const std::string& str, std::string& s )
            throw( ConversionInvalida )
        {
            s = str;
        }
}

#endif // __STRINGUTIL_H__
