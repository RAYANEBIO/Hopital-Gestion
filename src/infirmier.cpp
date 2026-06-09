#include "infirmier.h"
#include <string>
#include <iostream>
#include "Medecin.h"
#include "User.h"
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <limits>

infirmier::infirmier(){

}
infirmier::~infirmier(){

}

infirmier::infirmier(const infirmier& other)
{
    //copy ctor
}
bool infirmier::menu(Ultimate_Database_Manager& db) {
    Patient p;
    Medecin m;
    User u;
    int result = 0;

    while (true) {
        #ifdef _WIN32
        system("cls");
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 2);
        #endif

        std::cout << "______________MENU INFIRMIER______________" << std::endl;
        std::cout << "[1]-Voir le dossier médical d'un patient" << std::endl;
        std::cout << "[2]-Voir Consultation" << std::endl;
        std::cout << "[3]-Entrer une note de Consultation" << std::endl;
        std::cout << "[4]-Déconnexion" << std::endl;
        std::cout << "__________________________________________" << std::endl;
        std::cout << "Choisissez une option entre [1-4]: ";
        std::cin >> result;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // flush newline

        switch (result) {
            case 1: {
                std::cout << "Veuillez entrer le nom du Patient: ";
                getline(std::cin, p.nom_Patient);
                if(p.exist(db,p)){
                if (m.accederDossier(db, p)) {
                    std::cout << "Le dossier médical est protégé par la loi et par le secret médical." << std::endl;
                } else {
                    std::cout << "Échec d'accès au dossier." << std::endl;
                }}
                else{
                    std::cout<<"Le patient n'existe pas";
                }
                break;
            }

            case 2: {
                std::cout << "Veuillez entrer le nom du Patient: ";
                getline(std::cin, p.nom_Patient);
                if(p.exist(db,p)){
                if (m.accederConsultation(db, p)) {
                    std::cout << "Voici la consultation." << std::endl;
                } else {
                    std::cout << "Échec d'accès à la consultation." << std::endl;
                }}
                else{
                    std::cout<<"Le patient est inexistant";
                }
                break;
            }

            case 3: {
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
                    std::cout<<"Le patient n'existe pas";
                }
                break;
            }

            case 4: {
                std::string option;
                std::cout << "Voulez-vous vous déconnecter (o/n)? ";
                std::cin >> option;

                if (option == "o") {
                    return u.menu(db);
                } else if (option == "n") {
                    return true;
                } else {
                    std::cout << "Entrez o/n." << std::endl;
                }
                break;
            }

            default:
                std::cout << "Veuillez entrer un nombre compris entre 1-4." << std::endl;
                break;
        }

        std::cout << "\nAppuyez sur Entrée pour continuer...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return true;
}
