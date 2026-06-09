#include "User.h"
#include <iostream>
#include <sqlite3.h>
#include "Medecin.h"
#include "Administrateur.h"
#include "infirmier.h"
#include "pharmacien.h"
#include <windows.h>
#include "Ultimate_Database_Manager.h"


User::User() {}

User::User(std::string nomUtilisateur, std::string password): nomUtilisateur(nomUtilisateur), password(password) {}
User::~User() {}
User::User(const User& other) {}

bool User::seConnecter(Ultimate_Database_Manager& db) {
    User u;
    std::cout << "\n Entrez votre nom:" << std::endl;
    getline(std::cin,nomUtilisateur);
    std::cout << "\n Entrez votre mot de passe:" << std::endl;
    getline(std::cin,password);

    if (exist(db)) {
            HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h,2);
        std::cout << "***** Bonjour " << nomUtilisateur <<" nous vous souhaitons la bienvenue dans l'espace de gestion *****"<< std::endl;
        std::cout << "\n Appuyez sur Entree pour continuer...";
            std::cin.get();
        return true;
    } else {
        #ifdef _WIN32
            system("cls");
            #endif
        std::cout << "\n Nom/Mot de passe incorrect ou compte inexistant" << std::endl;
        std::cout << "\n Appuyez sur Entree pour recommencer...\n";
            std::cin.get();  // attend que l'utilisateur appuie sur Entrée
        return u.retour(db);
    }
    return true;
}

bool User::exist(Ultimate_Database_Manager& db) {
    sqlite3_stmt* stmt;
    std::string sql = "SELECT password FROM User WHERE nomUtilisateur='" + nomUtilisateur + "';";

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur SELECT: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }

    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string dbPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (dbPassword == password) {
            found = true;
        }
    }

    sqlite3_finalize(stmt);
    return found;
}

bool User::retour(Ultimate_Database_Manager& db){
    User u;
std::cout<< "\n *Entrez à nouveau vos identifiants et veillez a respecter la caste.\n *Si vous avez oublie votre code, notifier le à l'administration"<<std::endl;
if (u.seConnecter(db))
    {
        u.menu(db);
        return 0;
    }
}
bool User::menu(Ultimate_Database_Manager& db) {
    sqlite3_stmt* stmt;
    std::string sql = "SELECT role FROM User WHERE nomUtilisateur='" + nomUtilisateur + "';";

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur SELECT: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return true;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (role == "medecin") {
            std::cout << "Menu Médecin" << std::endl;
            Medecin m;
            m.menu(db);
        } else if (role == "Infirmier") {
            std::cout << "Menu Infirmier" << std::endl;
            infirmier i;
            i.menu(db);
        } else if (role == "Pharmacien") {
            std::cout << "Menu Pharmacien" << std::endl;
            Pharmacien ph;
            ph.menu(db);
        }  else if (role== "Administrateur"){
            std::cout<< "Menu Administrateur"<<std::endl;
            Administrateur a;
            a.menu(db);
        } else {
            std::cout << "Rôle inconnu" << std::endl;
       }
        sqlite3_finalize(stmt);
}
return true;
}
bool User::Notes(Ultimate_Database_Manager& db , std::string& nomPatient){
    User u;
    sqlite3*DB;
    sqlite3_stmt* stmt;
    std::string sql = "SELECT role FROM User WHERE nomUtilisateur='" + u.nomUtilisateur + "';";

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur SELECT: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return false;
    }

    bool success = true;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string updateSQL;

        if (role == "Medecin") {
            updateSQL = "UPDATE Consultation SET Notes_du_medecin = 'entrée' WHERE Nom_du_Patient='" + nomPatient + "';";
        } else if (role == "Infirmier") {
            updateSQL = "UPDATE Consultation SET Notes_infirmier = 'entrée' WHERE Nom_du_Patient='" + nomPatient + "';";
        } else if (role == "Pharmacien") {
            updateSQL = "UPDATE Consultation SET Notes_pharmacien = 'entrée' WHERE Nom_du_Patient='" + nomPatient + "';";
        }

        char* messageError = nullptr;
        int exit = sqlite3_exec(db.getDB(), updateSQL.c_str(), nullptr, nullptr, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error in updateUser function: " << messageError << std::endl;
            sqlite3_free(messageError);
            success = false;
        }
    }

    sqlite3_finalize(stmt);
    return success;
}



