#include "Administrateur.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <windows.h>
#include "Ultimate_Database_Manager.h"

Administrateur::Administrateur()
{
    //ctor
}

Administrateur::~Administrateur()
{
    //dtor
}

Administrateur::Administrateur(const Administrateur& other)
{
    //copy ctor
}

bool Administrateur::Ajouter_utilisateur(Ultimate_Database_Manager& db) {
    User u;

    std::cout << "Entrer le nom du nouvel utilisateur" << std::endl;
    std::getline(std::cin, u.nomUtilisateur);

    std::cout << "Quel est le role du nouvel utilisateur (Medecin - Infirmier - Pharmacien - Administrateur) ? " << std::endl;
    std::getline(std::cin, u.role);

    u.password = Generateur_password();

    if (db.InsertUser("Gestionnaire.db", u)) {
        db.download_Identifiants("Gestionnaire.db", u);
        std::cout << "Utilisateur ajouté avec succès." << std::endl;
    } else {
        std::cerr << "Échec de l'ajout de l'utilisateur." << std::endl;
        return false;
    }

    return true;
}

std::string Administrateur::Generateur_password(){
    int length,x;
    srand(time(NULL));
    std::string pword;
    std::string charactere = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn1234567890";
    length = 8 ;
    for(int i= 0; i < length; i++)
    {
        x = rand()% charactere.length();
        pword += charactere[x];
    }

    return pword;
}

bool Administrateur::Supprimer_utilisateur(Ultimate_Database_Manager& db,User u ){
    std::cout<<"Entrer le nom de l'utilisateur"<<std::endl;
    getline(std::cin,u.nomUtilisateur);
    db.DeleteUser("Gestionnaire.db",u);
return true;
}
        bool Administrateur::Gerer_acces(Ultimate_Database_Manager& db ){

return true;
}
bool Administrateur::Mettre_a_jour (Ultimate_Database_Manager& db){
    User u;
    int resultat;
    std::string parametre;
    while (resultat!=4){
             #ifdef _WIN32
            system("cls");
            HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h,2);
            #endif

            std::cout <<"_________OPTIONS DE MISE A JOUR_________"<< std::endl;


        std::cout<<" [1]- Nom de l'utilisateur "<< std::endl;
         std::cout<<" [2]- role de l'utilisateur "<< std::endl;
          std::cout<<" [3]- Mot de passe de l'utilisateur "<< std::endl;
             std::cout<<" [4]- Retour au menu utilisateur \n"<< std::endl;
                std::cout<<"******************************"<<std::endl;
                std::cout<<"Choisissez une option entre [1,4]"<<std::endl;
               std::cin >> resultat;
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

switch(resultat) {
    case 1: {
        std::cout << "Entrer le nom de l'utilisateur" << std::endl;
        getline(std::cin, u.nomUtilisateur);
        std::cout << "Entrer le nouveau nom" << std::endl;
        std::string newNom;
        getline(std::cin, newNom);
        db.UpdateUserNom("Gestionnaire.db",nomUtilisateur, newNom);
        break;
    }
    case 2: {
        std::cout << "Entrer le nom de l'utilisateur" << std::endl;
        getline(std::cin, u.nomUtilisateur);
        std::cout << "Entrer le nouveau rôle" << std::endl;
        std::string newRole;
        getline(std::cin, newRole);
        db.UpdateUserRole("Gestionnaire.db",nomUtilisateur,newRole);
        break;
    }
    case 3: {
        std::cout << "Entrer le nom de l'utilisateur" << std::endl;
        getline(std::cin, u.nomUtilisateur);
        std::cout << "Entrer le nouveau mot de passe" << std::endl;
        std::string newPwd;
        getline(std::cin, newPwd);
        db.UpdateUserPwd("Gestionnaire.db",nomUtilisateur,newPwd);
        break;
    }
    default: {
        std::cout << "Veuillez rentrer une valeur comprise entre 1-3" << std::endl;
        break;
    }
    }

if (resultat != 4) {
    std::cout << "\nAppuyez sur Entrée pour continuer...";
    std::cin.get();
}
    }
return true;

}

bool Administrateur::Stat_shower(Ultimate_Database_Manager& db){
 db.show_stat("Gestionnaire.db");
return true;
    }
bool Administrateur::menu (Ultimate_Database_Manager& db){
    int number = 0;
    Administrateur a;
    while (number !=5){
            #ifdef _WIN32
            system("cls");
            HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h,2);
            #endif

             std::cout << "_______________Menu Administrateur_______________ \n"<<std::endl;
    std::cout<<"[1]- Ajouter un nouvelle utilisateur \n"<< std::endl;
    std::cout<<"[2]- Supprimer Utilisateur \n"<< std::endl;
    std::cout<<"[3]- Gestion les acces \n"<< std::endl;
    std::cout<<"[4]- Mettre à jour les informations d'utilisateur \n"<< std::endl;
    std::cout<<"[5]- Statistiques de l'hopital\n "<< std::endl;
    std::cout<< "____________________________________________________\n"<< std::endl;
            std::cout<<"Choisissez une option entre [1,5]"<<std::endl;

    std::cin>> number;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

// une option retour au menu principal doit etre presente pour chaque option
    switch(number)
    {
         case 1: {
            if ( a.Ajouter_utilisateur(db)){
            std::cout<< "le dossier a été ajouté à la base de données "<< std::endl;
            }
            else{
            std::cout<< "Une erreur a été commise veuillez reprendre"<<std::endl;
            }
            break;
         }
         case 2 :{
             User u;
             std::cout << "Entrez le Nom de l'utilisateur: ";
             getline(std::cin,u.nomUtilisateur);
            if (a.Supprimer_utilisateur(db,u)){
            std::cout<< "Cette utilisateur vient d'être supprimé" << std::endl;
             }   else{
            std::cout<< "Une erreur a été commise veuillez reprendre"<<std::endl;
                }
            break;
         }
         case 3: {
            if ( a.Gerer_acces(db) ){
            std::cout<< "Annuaire de gestion de la base de données "<< std::endl;
            }
            else {
            std::cout<< "Une erreur a été commise veuillez reprendre"<<std::endl;
            }
            break;
         }
         case 4: {
            if ( a.Mettre_a_jour(db) )
            {
            std::cout<< "le dossier a été mise à jour "<< std::endl;
            }
            else
            {
                std::cout<< "Une erreur a été commise veuillez reprendre"<<std::endl;
            }
            break;
         }
         case 5: {
            if ( a.Stat_shower(db) ){
            std::cout<< "le dossier a été ajouté à la base de données "<< std::endl;
            }
            else
            {
            std::cout<< "Une erreur a été commise veuillez reprendre"<<std::endl;
            }
            break;
         }
         default:{
            std::cout<< "veuillez rentrer une valeur comprise entre 1-5"<<std::endl;
         }
            break;
}
            if (number != 5) {
            std::cout << "\n Appuyez sur Entrée pour continuer...";
            std::cin.get();
            }
    }
    return true;
}
