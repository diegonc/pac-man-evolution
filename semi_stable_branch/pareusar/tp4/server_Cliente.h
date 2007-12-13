#ifndef __CLIENTE_H__
#define __CLIENTE_H__

#include "common_Thread.h"
#include "common_Socket.h"
#include "server_Log.h"
#include "server_LogEntry.h"
#include "server_Observable.h"
#include "server_EventPool.h"
#include "server_SyncQueue.h"

class Cliente : public Thread, public Observable<LogEntry*>::Observer
{
    private:
        Socket* sock;
        unsigned int id;
        SyncQueue<LogEntry*> pending;

    public:
        Cliente( Socket* s, unsigned int id );

        ~Cliente();

        void* run();

        void notify( LogEntry* le );
};

#endif /* __CLIENTE_H__ */
