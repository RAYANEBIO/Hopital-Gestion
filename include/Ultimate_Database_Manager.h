#ifndef ULTIMATE_DATABASE_MANAGER_H
#define ULTIMATE_DATABASE_MANAGER_H
#include <sqlite3.h>
#include <string>
#include "Patient.h"

class Patient;
class User;
class Ultimate_Database_Manager
{
    public:
        Ultimate_Database_Manager();
        Ultimate_Database_Manager(const std::string& filename);
        ~Ultimate_Database_Manager();
        Ultimate_Database_Manager(const Ultimate_Database_Manager& other);
bool createDatabase( const char* s);
bool createTable(const char* s);
bool InsertUser (const char* s, const User& u);
bool InsertDossier (const char* s,const Patient& p);
bool UpdateDossier (const char* s,const Patient& p);
bool DeleteUser (const char* s,const User& u);
bool SelectRole (const char* s,const User& u);
bool SelectId (const char* s,std::string nom_Patient);
bool delete_Consultation(const char* s , const Patient& p);
static int callback( void* NotUsed, int argc, char** argv, char** azColName);
static int callbackcount (void* NotUsed, int argc, char** argv, char** azColName);

bool download_Dossier (const char* s, const Patient& p);
bool download_Identifiants (const char* s,const User& u);
bool show_stat(const char* s);
bool UpdateUserRole (const char* s, const std::string& nomUtilisateur,const std::string& newRole);
bool UpdateUserPwd (const char* s,const std::string& nomUtilisateur,const std::string& newPwd);
bool UpdateUserNom (const char* s,const std::string& nomUtilisateur,const std::string& newNom);
bool Notes(const char* s,const Patient& p,const std::string& entree,const std::string& role );

bool createConsultation (const char* s,const Patient& p);

sqlite3* getDB() const { return DB; }

    protected:
    sqlite3*DB;
    private:
};
#endif // ULTIMATE_DATABASE_MANAGER_H
