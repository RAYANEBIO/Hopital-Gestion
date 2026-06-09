#include "Pharmacien.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <windows.h>
#include <User.h>
#include "Patient.h"
#include <limits>

Pharmacien::Pharmacien()
{
    //ctor
}

Pharmacien::~Pharmacien()
{
    //dtor
}

Pharmacien::Pharmacien(const Pharmacien& other)
{
    //copy ctor
}
bool Pharmacien::menu(Ultimate_Database_Manager& db) {
    #ifdef _WIN32
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 2);
    #endif

    int result = 0;
    Patient p;
    User u;

    while (true) {
        std::cout << "______________MENU PHARMACIEN______________" << std::endl;
        std::cout << "[1]-Voir Prescriptions" << std::endl;
        std::cout << "[2]-Entrer une note de Consultation" << std::endl;
        std::cout << "[3]-Retour à la page d'accueil" << std::endl;
        std::cout << "____________________________________________" << std::endl;
        std::cout << "Choisissez une option entre [1-3]: ";
        std::cin >> result;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (result) {
            case 1: {
            sqlite3* DB;
            sqlite3_stmt* stmt;
                std::cout << "Entrez le nom du Patient: ";
                getline(std::cin, p.nom_Patient);
                if(p.exist(db,p)){
                if (sqlite3_open("Gestionnaire.db", &DB) != SQLITE_OK) {
                    std::cerr << "Erreur ouverture base : " << sqlite3_errmsg(DB) << std::endl;
                    return false;
                }

                std::string sql = "SELECT Prescription FROM Consultations WHERE nom_du_Patient=?;";
                if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
                    sqlite3_bind_text(stmt, 1, p.nom_Patient.c_str(), -1, SQLITE_TRANSIENT);

                    std::cout << "Voici les prescriptions du Patient:" << std::endl;
                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        std::cout << sqlite3_column_text(stmt, 0) << std::endl;
                    }
                } else {
                    std::cerr << "Erreur préparation requête: " << sqlite3_errmsg(DB) << std::endl;
                }
                }
                else{
                    std::cout<<"Ce patient n'existe pas";
                }

                sqlite3_finalize(stmt);
                sqlite3_close(DB);
                break;
            }

            case 2: {
                std::string entree;
                std::string role;
                std::cout << "Entrer le nom du patient consulté: ";
                getline(std::cin, p.nom_Patient);
                if(p.exist(db,p)){
                std::cout << "Note de la Consultation: ";
                getline(std::cin, entree);

                if (db.Notes("Gestionnaire.db", p, entree, role)) {
                    std::cout << "La note a été ajoutée." << std::endl;
                } else {
                    std::cout << "Échec de l'ajout de la note." << std::endl;
                }}
                else{
                    std::cout<<" Ce patient n'existe pas";
                }
                break;
            }

            case 3: {
                std::string option;
                std::cout << "Voulez-vous retourner au menu de départ (o/n)? ";
                std::cin >> option;
                if (option == "o") {
                    return u.menu(db);
                } else if (option == "n") {
                    return true; // exit menu
                } else {
                    std::cout << "Entrez o/n" << std::endl;
                }
                break;
            }

            default:
                std::cout << "Veuillez entrer un nombre compris entre 1-3." << std::endl;
                break;
        }

        std::cout << "\nAppuyez sur Entrée pour continuer...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
