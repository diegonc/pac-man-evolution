#ifndef __JUGADORLOCAL_H__
#define __JUGADORLOCAL_H__

/*
 * esta cosa seria para meter los datos del jugador local
 * en algun lado. pero tal vez no sea necesaria.
 */
class JugadorLocal
{
    // Singleton
    private:
        static JugadorLocal instance;

        JugadorLocal() {}

        ~JugadorLocal() {}

    public:
        static JugadorLocal& getInstance()
        {
            return instance;
        }

    private:
        bool es_pacman;

    public:
        void set_pacman( bool p ) { es_pacman = p; }

};

#endif // __JUGADORLOCAL_H__
