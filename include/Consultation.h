#ifndef CONSULTATION_H
#define CONSULTATION_H
#include <string>


class Consultation
{
    public:
        Consultation();
        ~Consultation();
        Consultation(const Consultation& other);
        int idConsultation ;
        std::string Date;
         std::string Etat_de_la_Consultation;
         std::string Prescription;
         std::string Nom_Patient;
         std::string Nom_Medecin;
         std::string Motif;
       std::string Notes_du_medecin ;
       std::string Notes_infirmier;
        std::string Notes_pharmacien;
       std::string examens;
       std::string Prochain_rendez_vous;

        void maj();


    protected:

    private:
};

#endif // CONSULTATION_H

