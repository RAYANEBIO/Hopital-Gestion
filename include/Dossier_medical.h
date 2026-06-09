#ifndef DOSSIER_MEDICAL_H
#define DOSSIER_MEDICAL_H
#include <string>


class Dossier_medical
{
    public:
        Dossier_medical();
        ~Dossier_medical();
        Dossier_medical(const Dossier_medical& other);


    protected:
        std::string Patient ;
       int idDossier ;
       std::string antecedent  ;
        std::string MedecinEnCharge;
    private:
};

#endif // DOSSIER_MEDICAL_H


