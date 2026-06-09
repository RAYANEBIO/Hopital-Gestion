#include "Patient.h"
#include "Ultimate_Database_Manager.h"
#include <iostream>
#include <string>


Patient::Patient()
{
    //ctor
}

Patient::~Patient()
{
    //dtor
}

Patient::Patient(const Patient& other)
{
    //copy ctor
}
bool Patient::exist(Ultimate_Database_Manager& db, const Patient& p) {

    sqlite3_stmt* stmt;
    // On ne sélectionne que le nom, pas le mot de passe
    std::string sql = "SELECT Nom_du_Patient FROM DossierMedical WHERE Nom_du_Patient = ?;";

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur SELECT: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }

    // Bind du nom du patient
    sqlite3_bind_text(stmt, 1, p.nom_Patient.c_str(), -1, SQLITE_TRANSIENT);

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Si une ligne est trouvée, le patient existe
        found = true;
    }

    sqlite3_finalize(stmt);
    return found;
}
