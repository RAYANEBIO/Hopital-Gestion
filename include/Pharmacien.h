#ifndef PHARMACIEN_H
#define PHARMACIEN_H
#include "Ultimate_Database_Manager.h"
#include <professionnel_de_sante.h>


class Pharmacien : public professionnel_de_sante
{
    public:
        Pharmacien();
        ~Pharmacien();
        Pharmacien(const Pharmacien& other);
        bool menu(Ultimate_Database_Manager& db);
    protected:

    private:
};

#endif // PHARMACIEN_H
