/*
 *  - Coleccion de predeclaraciones de tipos.
 *  - Typedef para tipos parametrizados.
 */

#ifdef NEEDS_ALL
    #undef NEEDS_ALL
    #define NEEDS_MODELO
    #define NEEDS_VERTICE
    #define NEEDS_ARCO
    #define NEEDS_GRAFO
    #define NEEDS_DIJKSTRA
    #define NEEDS_TREN
    #define NEEDS_EVENTO
    #define NEEDS_THREAD
    #define NEEDS_PARADA
#endif

#ifdef NEEDS_REDVIAL
    #undef NEEDS_REDVIAL
    #ifndef DECLARED_REDVIAL
        class RedVial;
        #define DECLARED_REDVIAL
    #endif
#endif

#ifdef NEEDS_VERTICE
    #undef NEEDS_VERTICE
    #ifndef DECLARED_VERTICE
        class Vertice;
        #define DECLARED_VERTICE
    #endif
#endif

#ifdef NEEDS_ARCO
    #undef NEEDS_ARCO
    #ifndef DECLARED_ARCO
        class Arco;
        #define DECLARED_ARCO
    #endif
#endif

#ifdef NEEDS_GRAFO
    #undef NEEDS_GRAFO
    #ifndef DECLARED_GRAFO
        template <class TVertice, class TArco, class TId>
        class Grafo;
/*
        // Define nombres cortos para la especializacion utilizada.
        #define NEEDS_SMARTPOINTER
        #define NEEDS_VERTICE
        #define NEEDS_ARCO
        #include "Forwards.h"

        typedef Grafo<SmartPointer<Vertice>, SmartPointer<Arco> > MiGrafo;
*/
        #define DECLARED_GRAFO
    #endif
#endif

#ifdef NEEDS_DIJKSTRA
    #undef NEEDS_DIJKSTRA
    #ifndef DECLARED_DIJKSTRA
        class Dijkstra;
        #define DECLARED_DIJKSTRA
    #endif
#endif

#ifdef NEEDS_TREN
    #undef NEEDS_TREN
    #ifndef DECLARED_TREN
        class Tren;
        #define DECLARED_TREN
    #endif
#endif

#ifdef NEEDS_EVENTO
    #undef NEEDS_EVENTO
    #ifndef DECLARED_EVENTO
        class Evento;
        #define DECLARED_EVENTO
    #endif
#endif

#ifdef NEEDS_THREAD
    #undef NEEDS_THREAD
    #ifndef DECLARED_THREAD
        class Thread;
        #define DECLARED_THREAD
    #endif
#endif

#ifdef NEEDS_PARADA
    #undef NEEDS_PARADA
    #ifndef DECLARED_PARADA
        class Parada;
        #define DECLARED_PARADA
    #endif
#endif
