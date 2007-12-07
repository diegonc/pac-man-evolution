#ifndef __FILELOGGER_H__
#define __FILELOGGER_H__

#include "common_Thread.h"
#include "server_Observable.h"
#include "server_LogEntry.h"
#include "common_Thread.h"
#include "server_LogEntry.h"
#include "server_EventPool.h"
#include "server_SyncQueue.h"
#include <string>
#include <fstream>

/*
 * Registra los eventos generados por los trenes en el archivo de log y la
 * consola del servidor.
 */
class FileLogger : public Thread, public Observable<LogEntry*>::Observer
{
    private:
        SyncQueue<LogEntry*> pending;
        std::ofstream fd;

    public:
        FileLogger( const std::string& s );
        ~FileLogger();

        void* run();

        void notify( LogEntry* le );
};

#endif /* __FILELOGGER_H__ */
