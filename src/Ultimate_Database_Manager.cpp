#include "Ultimate_Database_Manager.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <exception>
#include <fstream>
#include "Consultation.h"
#include "User.h"

 Ultimate_Database_Manager::Ultimate_Database_Manager() {
 }

Ultimate_Database_Manager::Ultimate_Database_Manager(const std::string& filename) {
    if (sqlite3_open(filename.c_str(), &DB)) {
        std::cerr << "Erreur ouverture base: " << sqlite3_errmsg(DB) << std::endl;
        DB = nullptr;
    }
}
Ultimate_Database_Manager::~Ultimate_Database_Manager() {
    if (DB) sqlite3_close(DB);
}
Ultimate_Database_Manager::Ultimate_Database_Manager(const Ultimate_Database_Manager& other)
{
    //copy ctor
}
bool Ultimate_Database_Manager::createTable(const char* s) {
    sqlite3* DB;
    int exit = sqlite3_open("Gestionnaire.db", &DB);

    std::string sqlUser =
        "CREATE TABLE IF NOT EXISTS User("
        "Id_User INTEGER PRIMARY KEY AUTOINCREMENT, "
        "nomUtilisateur TEXT NOT NULL, "
        "password TEXT NOT NULL, "
        "role TEXT"
        ");";

    std::string sqlAdmin =
        "INSERT INTO User(nomUtilisateur, password, role) "
        "VALUES ('admin', 'admin123', 'Administrateur');";
        char* errMsg = nullptr;
    exit = sqlite3_exec(DB, sqlAdmin.c_str(), nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "Erreur insertion admin : " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << " * Compte administrateur created" << std::endl;
    }
    std::string sqlMedec =
        "INSERT INTO User(nomUtilisateur, password, role) "
        "VALUES ('rayane', 'medec123', 'Medecin');";
    exit = sqlite3_exec(DB, sqlMedec.c_str(), nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "Erreur insertion medec : " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << " * Compte medecin created" << std::endl;
    }
     std::string sqlInf =
        "INSERT INTO User(nomUtilisateur, password, role) "
        "VALUES ('drake', 'infir123', 'Infirmier');";
    exit = sqlite3_exec(DB, sqlInf.c_str(), nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "Erreur insertion medec : " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << " * Compte infirmier created" << std::endl;
    }
     std::string sqlPhar =
        "INSERT INTO User(nomUtilisateur, password, role) "
        "VALUES ('kanye', 'pharm123', 'Pharmacien');";
    exit = sqlite3_exec(DB, sqlPhar.c_str(), nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "Erreur insertion medec : " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << " * Compte pharmacien created" << std::endl;
    }

    std::string sqlDossierMedical =
    "CREATE TABLE IF NOT EXISTS DossierMedical("
    "Id_du_Patient INTEGER PRIMARY KEY AUTOINCREMENT,"
    "Nom_du_Patient  TEXT,"
    "Age INTEGER NOT NULL,"
    "Sexe TEXT NOT NULL,"
    "Taille REAL NOT NULL,"
    "Poids REAL NOT NULL,"
    "GroupeSanguin TEXT NOT NULL,"
    "Antecedents TEXT,"
    "Accompagnateur TEXT,"
    "MedecinEnCharge  TEXT,"
    "DateConsultation TEXT);";

    std::string sqlPatient =
    "CREATE TABLE IF NOT EXISTS PATIENT ("
    "Id_du_Patient INTEGER PRIMARY KEY AUTOINCREMENT,"
    "Nom_du_Patient TEXT NOT NULL);";

    std::string sqlConsultation =
    "CREATE TABLE IF NOT EXISTS Consultations ("
    "IdConsultation INTEGER PRIMARY KEY AUTOINCREMENT ,"
    "Nom_du_Patient TEXT NOT NULL, "
    "Date_de_la_Consultation TEXT ,"
    "Etat_de_la_Consultation TEXT,"
    "Motif TEXT,"
    "Notes_du_medecin TEXT,"
    "Notes_infirmier TEXT,"
    "notes_pharmacien TEXT,"
    "Prescription TEXT,"
    "examens TEXT,"
    "Prochain_rendez_vous TEXT);";

try {
    int exit = 0;
    char* messageError = nullptr;
    exit = sqlite3_open("Gestionnaire.db", &DB);

    exit = sqlite3_exec(DB, sqlUser.c_str(), nullptr, nullptr, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error in createTable function (User)." << std::endl;
        sqlite3_free(messageError);
    } else {
        std::cout << " * Table User created " << std::endl;
    }
    exit = sqlite3_exec(DB, sqlDossierMedical.c_str(), nullptr, nullptr, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error in createTable function (Dossier)." << std::endl;
        sqlite3_free(messageError);
    } else {
        std::cout << " * Table Dossier created " << std::endl;
    }
    exit = sqlite3_exec(DB, sqlPatient.c_str(), nullptr, nullptr, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error in createTable function (Patient)." << std::endl;
        sqlite3_free(messageError);
    } else {
        std::cout << " * Table Patient created " << std::endl;
    }
    exit = sqlite3_exec(DB, sqlConsultation.c_str(), nullptr, nullptr, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error in createTable function (Consultation)." << std::endl;
        sqlite3_free(messageError);
    } else {
        std::cout << " * Table Consultation created " << std::endl;
    }


    sqlite3_close(DB);

} catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
}
return true;
}
bool Ultimate_Database_Manager::InsertUser(const char* s, const User& u){
sqlite3_stmt* stmt;
std::string sql = "INSERT INTO User (nomUtilisateur, password, role) VALUES (?, ?, ?);";
if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
    sqlite3_bind_text(stmt, 1, u.nomUtilisateur.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, u.password.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, u.role.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erreur dans InsertUser : " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return false;
    }
}
sqlite3_finalize(stmt);
sqlite3_close(DB);
return true;
}

/*bool Ultimate_Database_Manager::InsertUser(const char* s, const User& u) {
    sqlite3* DB;
    char* messageError = nullptr;

    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK) {
        std::cerr << "Erreur lors de l'ouverture de la base : "
                  << sqlite3_errmsg(DB) << std::endl;
        if (DB) sqlite3_close(DB);
        return false;
    }
    std::string sqlInsert =
        "INSERT INTO User (nomUtilisateur, password, role) VALUES ('" +
        u.nomUtilisateur + "','" + u.password + "','" + u.role + "');";

    int site = sqlite3_exec(DB, sqlInsert.c_str(), nullptr, 0, &messageError);
    if (site != SQLITE_OK) {
        std::cerr << "Erreur dans InsertUser : " << messageError << std::endl;
        sqlite3_free(messageError);
         sqlite3_close(DB);
        return false;
    }
    sqlite3_close(DB);
    return true;
}
*/
bool Ultimate_Database_Manager::InsertDossier(const char* s, const Patient& p) {
    sqlite3_stmt* stmt;

    // Requête paramétrée avec des placeholders '?'
    const char* sql =
        "INSERT INTO DossierMedical "
        "(Nom_du_Patient, Age, Sexe, Taille, Poids, GroupeSanguin, Antecedents, Accompagnateur, MedecinEnCharge, DateConsultation) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

    // Préparation de la requête
    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, p.nom_Patient.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, p.Age);
    sqlite3_bind_text(stmt, 3, p.Sexe.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 4, p.Taille);
    sqlite3_bind_double(stmt, 5, p.Poids);
    sqlite3_bind_text(stmt, 6, p.GroupeSanguin.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, p.Antecedents.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 8, p.Accompagnateur.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 9, p.MedecinEnCharge.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 10, p.DateConsultation.c_str(), -1, SQLITE_TRANSIENT);

    // Exécution
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erreur InsertDossier: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return false;
    }
    }
    // Nettoyage
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return true;
}

bool Ultimate_Database_Manager::UpdateDossier (const char* s,const Patient& p){
   sqlite3_stmt* stmt;
    std::string parametre;
    std::string entree;

std::string sql =
    "UPDATE DossierMedical SET " + parametre + " = ? WHERE Nom_du_Patient= ?;";

	if (sqlite3_prepare16_v2(DB,sql.c_str(),-1,&stmt,nullptr )== SQLITE_OK) {
		sqlite3_bind_text(stmt,1,p.nom_Patient.c_str(),-1,SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt,2,entree.c_str(),-1,SQLITE_TRANSIENT);

		 if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erreur UpdateDossier: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return false;
    }
	}

	sqlite3_finalize(stmt);
	sqlite3_close(DB);
return true;
}
bool Ultimate_Database_Manager::DeleteUser (const char* s,const User& u){
   sqlite3_stmt* stmt;
	const char* sql = "DELETE FROM User WHERE nomUtilisateur= ? ;";
    if(sqlite3_prepare16_v2(DB,sql,-1,&stmt,nullptr)==SQLITE_OK){
            sqlite3_bind_text(stmt,1,u.nomUtilisateur.c_str(),-1,SQLITE_TRANSIENT);

	if (sqlite3_step(stmt)!= SQLITE_DONE) {
		std::cerr << "Error in deleteData function." << std::endl;
		sqlite3_finalize(stmt);
		sqlite3_close(DB);
    return false;
	}
    }
	sqlite3_finalize(stmt);
		sqlite3_close(DB);
    return true;
}
bool Ultimate_Database_Manager::SelectRole(const char* s, const User& u)
{
	sqlite3* DB;
	char* messageError = nullptr;

	std::string sql = "SELECT role FROM User WHERE nomUtilisateur='"+u.nomUtilisateur+"';";

	int exit = sqlite3_open("Gestionnaire.db", &DB);
	exit = sqlite3_exec(DB, sql.c_str(), callback, nullptr, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectRole function." << std::endl;
		sqlite3_free(messageError);
	}
	return true;
}
bool Ultimate_Database_Manager::SelectId (const char* s, std::string nom_Patient){
    Patient p;
    sqlite3* DB;
	char* messageError = nullptr;

	std::string sql = "SELECT Id_du_Patient FROM DossierMedical WHERE Nom_du_Patient='"+p.nom_Patient+"';";

	int exit = sqlite3_open("Gestionnaire.db", &DB);
	exit = sqlite3_exec(DB, sql.c_str(), callback, nullptr, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectRole function." << std::endl;
		sqlite3_free(messageError);
	}
	return true;
}
int Ultimate_Database_Manager::callback(void* NotUsed, int argc, char** argv, char** azColName) {
    if (argc > 0 && argv[0]) {
        std::cout << argv[0] << std::endl;
    }
    return 0;
}

int Ultimate_Database_Manager::callbackcount(void* NotUsed, int argc, char** argv, char** azColName) {
    if (argc > 0 && argv[0]) {
        std::cout << argv[0] << std::endl;
    }
    return 0;
}

bool Ultimate_Database_Manager::delete_Consultation(const char* s,const Patient& p){
        sqlite3_stmt* stmt;

     const char* sqlDelete = "DELETE FROM Consultations WHERE Nom_du_Patient = ?;";
        if(sqlite3_prepare_v2(DB,sqlDelete,-1,&stmt,nullptr)==SQLITE_OK ){
        sqlite3_bind_text(stmt,1,p.nom_Patient.c_str(),-1,SQLITE_TRANSIENT);
        if(sqlite3_step(stmt)!= SQLITE_DONE){
            std::cout<<"Erreur dans Delete_Consultation"<<sqlite3_errmsg(DB)<<std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(DB);
            return false;
        }
        }
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
    return true;
    }


bool Ultimate_Database_Manager::createConsultation(const char* s, const Patient& p) {
    Consultation c;
        sqlite3_stmt* stmt = nullptr;

    const char* sql =
        "INSERT INTO Consultations ("
        "Nom_du_Patient, Date_de_la_Consultation, Etat_de_la_Consultation, Motif, "
        "Notes_du_medecin, Notes_infirmier, Notes_pharmacien, Prescription, examens, Prochain_rendez_vous"
        ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, p.nom_Patient.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, p.DateConsultation.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, c.Etat_de_la_Consultation.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, c.Motif.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, c.Notes_du_medecin.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, c.Notes_infirmier.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, c.Notes_pharmacien.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 8, c.Prescription.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 9, c.examens.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 10, c.Prochain_rendez_vous.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erreur création de Consultation: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return false;
    }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return true;
}

bool Ultimate_Database_Manager::download_Dossier (const char* s,const Patient& p){
        sqlite3_stmt* stmt;

         const char* sql="SELECT * FROM DossierMedical WHERE nom_Patient= ?;";

    if (sqlite3_prepare_v2(DB,sql,-1,&stmt,nullptr)== SQLITE_OK) {
        sqlite3_bind_text(stmt,1,p.nom_Patient.c_str(),-1,SQLITE_TRANSIENT);
        if(sqlite3_step(stmt)!= SQLITE_DONE){
        std::cerr << "Erreur création de Consultation: "<< sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return false;
        }
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
    }


    std::ofstream Dossier("Dossier_Med.csv");

    if(!Dossier){
        std::cout<< "Erreur d'ouverture du fichier"<<std::endl;
        return 1;
    }
        for (int j=0;j<10;j++){
            std::string Dossier_med[p.Id_Patient][j];
            Dossier << Dossier_med[p.Id_Patient][j];
            if (j<9) Dossier <<",";
         Dossier <<"\n";
    }
    Dossier.close();
    std::cout<< "Export reussie" << std::endl;
    return true;
}
bool Ultimate_Database_Manager::download_Identifiants(const char* s,const User& u) {
    sqlite3* DB;
    int exit = sqlite3_open("Gestionnaire.db", &DB);
    if (exit!= SQLITE_OK) {
        std::cerr<<"Erreur d'ouverture:"<<sqlite3_errmsg(DB)<<std::endl;
            return false;
        }

    std::ofstream Identifiants("identifiant.txt");
    if (!Identifiants) {
        std::cout << "Erreur d'ouverture du fichier" << std::endl;
        return false;
    }
    Identifiants << "Nom de l'utilisateur : " << u.nomUtilisateur << "\n";
    Identifiants << "Password de l'utilisateur : " << u.password << "\n";
    Identifiants << "Rôle de l'utilisateur : " << u.role << "\n";

    Identifiants.close();
    std::cout << "Identifiants exportés" << std::endl;
    return true;
}

bool Ultimate_Database_Manager::show_stat(const char* s) {
    sqlite3* DB;
    if (sqlite3_open("Gestionnaire.db", &DB) != SQLITE_OK) {
        std::cerr << "Erreur ouverture base : " << sqlite3_errmsg(DB) << std::endl;
        return false;
    }

    char* errMsg = nullptr;

    std::string sqlPat = "SELECT COUNT(*) FROM Dossier;";
    std::cout << "Le nombre de Patient est" << std::endl;
    if (sqlite3_exec(DB, sqlPat.c_str(), callbackcount, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Erreur sélection patients : " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(DB);
        return false;
    }

    std::string sqlMed = "SELECT COUNT(*) FROM User WHERE role='Medecin';";
    std::cout << "Le nombre de Medecin est"<< std::endl;
    if (sqlite3_exec(DB, sqlMed.c_str(), callbackcount, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Erreur sélection médecins : " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(DB);
        return false;
    }

    std::string sqlInf = "SELECT COUNT(*) FROM User WHERE role='Infirmier';";
    std::cout << "Le nombre d'infimier est" << std::endl;
    if (sqlite3_exec(DB, sqlInf.c_str(), callbackcount, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Erreur sélection infirmiers : " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(DB);
        return false;
    }

    sqlite3_close(DB);
    return true;
}
bool Ultimate_Database_Manager::UpdateUserRole (const char* s,const std::string& nomUtilisateur,const std::string& newRole){
sqlite3_stmt* stmt;
const char* sql =
    "UPDATE User SET role = ? WHERE nomUtilisateur = ?;";
    if (sqlite3_prepare_v2(DB,sql,-1,&stmt,nullptr) == SQLITE_OK ) {
		sqlite3_bind_text(stmt,1,newRole.c_str(),-1,SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt,2,nomUtilisateur.c_str(),-1,SQLITE_TRANSIENT);
		if(sqlite3_step(stmt)!= SQLITE_DONE){
            std::cerr << "Error in updateUser function." <<sqlite3_errmsg(DB) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(DB);
            return false;

		}
	}
	sqlite3_finalize(stmt);
	sqlite3_close(DB);
return true;
}
bool Ultimate_Database_Manager::UpdateUserNom (const char* s,const std::string& nomUtilisateur,const std::string& newNom){
            sqlite3_stmt* stmt;
const char* sql =
    "UPDATE User SET nomUtilisateur = ? WHERE nomUtilisateur= ? ;";
	if (sqlite3_prepare_v2(DB,sql,-1,&stmt,nullptr) == SQLITE_OK ) {
		sqlite3_bind_text(stmt,1,newNom.c_str(),-1,SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt,2,nomUtilisateur.c_str(),-1,SQLITE_TRANSIENT);
		if(sqlite3_step(stmt)!= SQLITE_DONE){
            std::cerr << "Error in updateUser function." <<sqlite3_errmsg(DB) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(DB);
            return false;
		}
	}
    sqlite3_finalize(stmt);
	sqlite3_close(DB);
return true;
}

bool Ultimate_Database_Manager::UpdateUserPwd (const char* s,const std::string& nomUtilisateur,const std::string& newPwd){
sqlite3_stmt* stmt;
const char* sql =
    "UPDATE User SET password = ? WHERE nomUtilisateur= ? ;";
   if (sqlite3_prepare_v2(DB,sql,-1,&stmt,nullptr) == SQLITE_OK ) {
		sqlite3_bind_text(stmt,1,newPwd.c_str(),-1,SQLITE_TRANSIENT);
		sqlite3_bind_text(stmt,2,nomUtilisateur.c_str(),-1,SQLITE_TRANSIENT);
		if(sqlite3_step(stmt)!= SQLITE_DONE){
            std::cerr << "Error in updateUser function." <<sqlite3_errmsg(DB) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(DB);
            return false;

		}
	}
    sqlite3_finalize(stmt);
	sqlite3_close(DB);
    return true;
}
bool Ultimate_Database_Manager::Notes(const char* s,
                                      const Patient& p,
                                      const std::string& entree,
                                      const std::string& role) {
    sqlite3* DB;
    char* messageError = nullptr;

    std::string sqlNotes;

    if (role == "Medecin") {
        sqlNotes = "UPDATE Consultations SET Notes_du_medecin='" + entree +
                   "' WHERE Nom_du_Patient='" + p.nom_Patient + "';";
    } else if (role == "Infirmier") {
        sqlNotes = "UPDATE Consultations SET Notes_infirmier='" + entree +
                   "' WHERE Nom_du_Patient='" + p.nom_Patient + "';";
    } else if (role == "Pharmacien") {
        sqlNotes = "UPDATE Consultations SET Notes_pharmacien='" + entree +
                   "' WHERE Nom_du_Patient='" + p.nom_Patient + "';";
    } else {
        std::cerr << "Rôle inconnu, impossible de mettre à jour les notes." << std::endl;
        return false;
    }

    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK) {
        std::cerr << "Erreur ouverture base : " << sqlite3_errmsg(DB) << std::endl;
        if (DB) sqlite3_close(DB);
        return false;
    }

    exit = sqlite3_exec(DB, sqlNotes.c_str(), nullptr, nullptr, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Erreur dans Notes : " << messageError << std::endl;
        sqlite3_free(messageError);
        sqlite3_close(DB);
        return false;
    }

    sqlite3_close(DB);
    return true;
}

