#include "common_Condition.h"

Condition::Condition()
{
    pthread_cond_init( &cvar, NULL );
}

Condition::~Condition()
{
    pthread_cond_destroy( &cvar );
}

void Condition::signal()
{
    pthread_cond_broadcast( &cvar );
}
