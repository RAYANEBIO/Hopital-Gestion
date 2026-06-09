#ifndef INFIRMIER_H
#define INFIRMIER_H
#include "Ultimate_Database_Manager.h"

#include <professionnel_de_sante.h>


class infirmier : public professionnel_de_sante
{
    public:
        infirmier();
        ~infirmier();
        infirmier(const infirmier& other);
        infirmier(Medecin* m): medecin(m){};
        bool menu(Ultimate_Database_Manager& db);


    protected:

    private:
        Medecin* medecin;
};

#endif // INFIRMIER_H
