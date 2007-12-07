#ifndef __APP_H__
#define __APP_H__

class App
{
    int argc;
    char** argv;
    short port;
    char* host;

    static void signal_handler( int num ) { }

    void setup_signal_handler();
    void parse_arguments();

    public:
        App( int argc, char** argv ) : argc( argc ), argv( argv ) { }

        int run();
};

#endif /* __APP_H__ */
