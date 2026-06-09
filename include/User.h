#ifndef USER_H
#define USER_H
#include <string>
#include <sqlite3.h>

class Medecin;
class infirmier;
class Administrateur;

class professionnel_de_sante;
class Ultimate_Database_Manager;
class User
{
    public:
        User();
        User(std::string nomUtilisateur,std::string password);
        ~User();
        User(const User& other);

        bool seConnecter ( Ultimate_Database_Manager& db);
        bool seDeconnecter (Ultimate_Database_Manager& db );
        bool exist(Ultimate_Database_Manager& db);
        bool menu(Ultimate_Database_Manager& db);
        bool Notes(Ultimate_Database_Manager& db , std::string& nomPatient);
        bool retour(Ultimate_Database_Manager& db);


    int id;
    std::string nomUtilisateur ;
    std::string password;
    std::string role;
    std::string specialite;
    protected:


    private:

};

#endif // USER_H
