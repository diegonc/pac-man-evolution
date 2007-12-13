#ifndef __PriorityQueue_H__
#define __PriorityQueue_H__

#include <list>
#include <algorithm>

template<class T, class Comparer>
class PriorityQueue
{
    private:
        typedef std::list<T> Contenedor;
        Contenedor elementos;

    public:
        void push( T v, Comparer comp )
        {
            typename Contenedor::iterator it = elementos.begin();
            for( ; it != elementos.end(); ++it ) {
                if( comp( v, *it ) )
                    break;
            }

            elementos.insert(it, v );
        }

        T pop()
        {
            T  v = elementos.back();
            elementos.pop_back();
            return v;
        }
        void clear()
        {
            return elementos.clear();
        }

        bool empty()
        {
            return elementos.empty();
        }

        void sort( Comparer comp )
        {
            elementos.sort( comp );
        }

    public:
        class Filler
        {
            private:
                PriorityQueue& queue;
                Comparer& comp;

            public:
                Filler( PriorityQueue& q, Comparer& c ):queue( q ),comp(c ) { }

                void operator()( T v )
                {
                    queue.push( v, comp );
                }

        };
};

#endif /* __PriorityQueue_H__ */
