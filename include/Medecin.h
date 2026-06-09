#ifndef MEDECIN_H
#define MEDECIN_H
#include <iostream>
#include <string>
#include "Patient.h"
#include "Ultimate_Database_Manager.h"


#include "professionnel_de_sante.h"

class Ultimate_Database_Manager;
class professionnel_de_sante;
class Medecin : public professionnel_de_sante
{
    public:
        Medecin();
        Medecin(Ultimate_Database_Manager& db);
        ~Medecin();
        Medecin(const Medecin& other);
    bool menu(Ultimate_Database_Manager& db);
    bool creerDossier(Ultimate_Database_Manager& db);
    bool accederDossier(Ultimate_Database_Manager& db,Patient& p);
    bool majDossier(Ultimate_Database_Manager& db,Patient& p);
    bool creerConsultation(Ultimate_Database_Manager& db,Patient& p);
    bool accederConsultation(Ultimate_Database_Manager& db,const Patient& p);
    bool annulerConsultation(Ultimate_Database_Manager& db,const Patient& p );
    bool telechargerDossier(Ultimate_Database_Manager& db,Patient& p );

    protected:

    private:
        std::string nom;
        int motDePasse;
};

#endif // MEDECIN_H
