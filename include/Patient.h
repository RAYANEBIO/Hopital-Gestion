#ifndef PATIENT_H
#define PATIENT_H
#include <string>

class Ultimate_Database_Manager;
class Patient
{
    public:
        Patient();
        ~Patient();
        Patient(const Patient& other);
    int Id_Patient;
    int numPatient;
    std::string nom_Patient;
    int Age;
    std::string Sexe;
    float Taille;
    float Poids;
    std::string Antecedents;
    std::string GroupeSanguin;
    std::string Accompagnateur;
    std::string MedecinEnCharge;
    std::string DateConsultation;
    bool exist(Ultimate_Database_Manager& db, const Patient& p);


    protected:

    private:

};

#endif // PATIENT_H
