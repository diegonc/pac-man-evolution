#ifndef __LOGENTRY_H__
#define __LOGENTRY_H__

#include "common_Mutex.h"
#include "common_Time.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

class LogEntry
{
    Time timestamp;
    Mutex m;
    int ref_count;

    public:
        /* Tipos de entrada de Log */
        static LogEntry* crear_sale( const std::string& tren, const std::string& anden );
        static LogEntry* crear_para( const std::string& tren, const std::string& anden, bool libre );
        static LogEntry* crear_entra( const std::string& tren, const std::string& anden, int espera );
        static LogEntry* crear_termina( const std::string& tren );
        static LogEntry* crear_dummy( );

    protected:
        virtual ~LogEntry() {}

        void print_time( std::ostream& out ) const;

    public:
        LogEntry( ) : ref_count( 1 ) { }

        inline void set_time( const Time& t ) { timestamp = t; }

        void add_refs( int n );

        virtual void print( std::ostream& out ) const = 0;

        inline void print() const { print( std::cout ); }

        std::string raw_form() const;

        void destruir();
};

#endif /* __LOGENTRY_H__ */
