#include "Medecin.h"
#include <iostream>
#include <string>
#include "Patient.h"
#include <limits>
#include <windows.h>
#include "Consultation.h"
#include "Ultimate_Database_Manager.h"

Medecin::Medecin(){

}
Medecin::Medecin(Ultimate_Database_Manager& db){

}

Medecin::~Medecin()
{
    //dtor
}

Medecin::Medecin(const Medecin& other)
{
    //copy ctor
}
bool Medecin::menu(Ultimate_Database_Manager& db ){
    int number= 0;
    Medecin m;
    Patient p;
    User u;
    while (number !=8){
             #ifdef _WIN32
            system("cls");
            HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h,2);
            #endif

             std::cout << "_______________Menu Medecin_______________ \n"<<std::endl;
    std::cout<<"[1]- Creer un nouveau dossier medical \n"<< std::endl;
    std::cout<<"[2]- Acceder au dossier médical d'un patient \n"<< std::endl;
    std::cout<<"[3]- Mettre a jour le dossier medical d'un patient \n"<< std::endl;
    std::cout<<"[4]- Creer une nouvelle consultation \n"<< std::endl;
    std::cout<<"[5]- Voir Consultation\n"<<std::endl;
    std::cout<<"[6]- Annuler une consultation   \n "<< std::endl;
    std::cout<<"[7]- Telecharger le dossier médical  \n"<< std::endl;
    std::cout<<"[8]- Retour au menu\n"<< std::endl;
    std::cout<< "____________________________________________________\n"<< std::endl;
    std::cout<<"Choisissez une option entre [1-8]\n"<<std::endl;
    std::cin>> number;
// une option retour au menu principal doit etre presente pour chaque option
    switch(number)
    {
         case 1: {
            if ( m.creerDossier(db) ){
            std::cout<< "le dossier ajoute à la base de données "<< std::endl;
            }
            else
            {
            std::cout<< "Une erreur commise, veuillez reprendre"<<std::endl;
            }
            break;
         }
         case 2 :{
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Entrez le Nom du patient: ";
             getline(std::cin,p.nom_Patient);
             if(p.exist(db,p)){
             if( m.accederDossier(db,p)){
                std::cout<< "Les informations présentes dans ce dossier doivent absolument restées confidentielles" << std::endl;
               }
            else
            {
            std::cout<< "Une erreur a été commise veuillez reprendre"<<std::endl;
            }
            }
            else{
               std::cout<<" Ce patient n'est pas enregistree ";
            }
            break;
         }
         case 3: {
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Entrez le nom du patient";
            getline(std::cin,p.nom_Patient);
            if(p.exist(db,p)){
            if (m.majDossier(db,p)){
            std::cout<<"Le dossier a été mise à jour avec succès" <<std::endl;
            }
            else
            {
            std::cout<< "Une erreur a été commise veuillez reprendre"<<std::endl;
            }
            }
             else{
               std::cout<<" Ce patient n'est pas enregistree ";
            }
            break;
         }
         case 4: {
             std::cout<<"Entrez le nom du patient";
            getline(std::cin,p.nom_Patient);
             if(p.exist(db,p)){
            if ( m.creerConsultation(db,p))
            {
            std::cout<< " Une consultation a été créé " <<std::endl;
            }
            else{
            std::cout<< "Une erreur a été commise veuillez reprendre"<<std::endl;
            }
            }
             else{
               std::cout<<" Ce patient n'est pas enregistree ";
            }
            break;
         }
         case 5:{
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrez le Nom du patient: ";
             getline(std::cin,p.nom_Patient);
            if(p.exist(db,p)){
             if(m.accederConsultation(db,p)){
                std::cout<<"Voici la consultation du Patient"<<std::endl;
             }
             }
             else{
               std::cout<<" Ce patient n'est pas enregistree ";
            }
             break;
         }
         case 6: {
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Entrez le Nom du patient: ";
             getline(std::cin,p.nom_Patient);

            if(p.exist(db,p)){
            if ( m.annulerConsultation( db,p) )
            {
            std::cout<< "La consultation a été suppriméé"<<std::endl;
            }
            else
            {
                std::cout<< "Une erreur a été commise veuillez reprendre"<<std::endl;
            }
            }
            else{
               std::cout<<" Ce patient n'est pas enregistree ";
            }
            break;
         }
         case 7: {
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Entrez le Nom du patient: ";
             getline(std::cin,p.nom_Patient);
            if(p.exist(db,p)){
            if ( m.telechargerDossier(db,p)) {
            std::cout<<"le dossier a été télécharger"     <<std::endl;
            }
            else {
                std::cout<< "Une erreur a été commise veuillez reprendre"<<std::endl;
            }
            }
            else{
               std::cout<<" Ce patient n'est pas enregistree ";
            }
            break;
         }
         case 8:{
            std::string option;
            std::cout<<"Voulez vous retourner au menu de départ (o/n)?"<<std::endl;
            std::cin>> option;
            if(option == "o"){
                return u.menu(db);
            }
            else if(option == "n"){
               break;
            }
            else {
                std::cout << "Entrez o/n" << std::endl;
            }
            break;
         }
         default:{
            std::cout<<"Veuiller entrer un nombre compris entre 1-7"<<std::endl;
            break;

           }
    }
    if (number != 8) {
            std::cout << "\nAppuyez sur Entrée pour continuer...";
            std::cin.get();  // attend que l'utilisateur appuie sur Entrée
            }
    }
    return true;
}

    bool Medecin::creerDossier(Ultimate_Database_Manager& db) {
    Patient p;
    std::cout << "______NOUVEAU DOSSIER______\n" << std::endl;

    std::cout << "Nom du Patient: ";
    getline(std::cin, p.nom_Patient);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    std::cout << "Age: ";
    while (!(std::cin >> p.Age)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Veuillez entrer un nombre valide pour l'âge: ";
    }

    std::cout << "Sexe (M/F): ";
    std::cin >> p.Sexe;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Taille (m): ";
    while (!(std::cin >> p.Taille)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Veuillez entrer un nombre valide pour la taille: ";
    }

    std::cout << "Poids (kg): ";
    while (!(std::cin >> p.Poids)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Veuillez entrer un nombre valide pour le poids: ";
    }

    std::cout << "Groupe sanguin: ";
    std::cin >> p.GroupeSanguin;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Antécédents: ";
    getline(std::cin, p.Antecedents);

    std::cout << "Accompagnateur: ";
    getline(std::cin, p.Accompagnateur);

    std::cout << "Médecin en charge: ";
    getline(std::cin, p.MedecinEnCharge);

    std::cout << "Date de consultation: ";
    getline(std::cin, p.DateConsultation);

    // Call InsertDossier and return its result
    if (db.InsertDossier("Gestionnaire.db", p)) {
        std::cout << "Dossier créé avec succès." << std::endl;
        return true;
    } else {
        std::cerr << "Échec de la création du dossier." << std::endl;
        return false;
    }
    return true;
}


    bool Medecin::accederDossier(Ultimate_Database_Manager& db, Patient& p) {
   sqlite3_stmt* stmt;
sqlite3* DB;
       std::cout << "______ DOSSIER MEDICAL DE " << p.nom_Patient << " ______\n" << std::endl;
    const char* sql = "SELECT * FROM DossierMedical WHERE Nom_du_Patient= ?;";

    if (sqlite3_prepare_v2(DB,sql,-1,&stmt,nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt,1,p.nom_Patient.c_str(),-1,SQLITE_TRANSIENT);

    if (sqlite3_step(stmt)!= SQLITE_DONE) {
        std::cerr << "Erreur sélection des informations : " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return false;
    }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return true;
}


        /* std::cout <<"______DOSSIER DE " << p.nom_Patient <<"______ \n"<< std::endl;

    std::cout <<"1- Id du Patient:"<< p.Id_Patient << "\n"<< std::endl;

    std::cout <<"2- Nom du Patient:"<< p.nom_Patient  << "\n"<< std::endl;

    std::cout <<"3- Age: " << p.Age  << "\n"<< std::endl;

    std::cout <<"4- Sexe: " << p.Sexe << "\n"<< std::endl;

    std::cout <<"5- Taille: " << p.Taille << "\n"<< std::endl;

    std::cout << "6- Poids: "<< p.Poids << "\n"<< std::endl;

    std::cout<< "7- GroupeSanguin:" << p.GroupeSanguin << "\n"<< std::endl;

    std::cout<<"8- Accompagnateur:"<< p.Accompagnateur << " \n"<< std::endl;

    std::cout<<"9- MedecinEnCharge:"<< p.MedecinEnCharge<<" \n"<< std::endl;

    std::cout<<"10- DateConsultation:"<< p.DateConsultation <<" \n"<< std::endl;
    std::cout<<"___________________________________"<<std::endl;

    return true;
    } */

    bool Medecin::majDossier(Ultimate_Database_Manager& db, Patient& p){
        sqlite3* DB;
        Medecin m;
        int maj = 0;
        std::string parametre;
        std::string entree;

        #ifdef _WIN32
            system("cls");
            HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(h,2);
            #endif
            std::cout<<"Entrer le nom du patient"<<std::endl;
            getline(std::cin,p.nom_Patient);
        while (maj != 10) {
        m.accederDossier(db,p);
        std::cout <<"1- Id du Patient\n"<< std::endl;

    std::cout <<"2- Nom du Patient\n"<< std::endl;

    std::cout <<"3- Age\n"<< std::endl;

    std::cout <<"4- Sexe\n"<< std::endl;

    std::cout <<"5- Taille\n"<< std::endl;

    std::cout << "6- Poids\n"<< std::endl;

    std::cout<< "7- GroupeSanguin\n"<< std::endl;

    std::cout<<"8- Accompagnateur\n"<< std::endl;

    std::cout<<"9- MedecinEnCharge\n"<< std::endl;

    std::cout<<"10- DateConsultation\n"<< std::endl;
    std::cout<<"___________________________________"<<std::endl;
        std::cout << "Veuillez indiquer la référence ( 1-10 ) du paramètre que vous souhaitez modifier" <<std::endl;
        std::cin >> maj;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (maj) {
    case 1:{
        parametre = "Id_du_Patient";   // nom de colonne
        std::cout<<"Entrer la nouvelle valeur: ";
        getline(std::cin,entree);
        break;
    }
    case 2:{
        parametre = "Nom_du_Patient";
        std::cout<<"Entrer la nouvelle valeur: ";
        getline(std::cin,entree);
        break;
    }
    case 3:{
        parametre = "Age";
        std::cout<<"Entrer la nouvelle valeur: ";
        getline(std::cin,entree);
        break;
    }
    case 4:{
        parametre = "Sexe";
        std::cout<<"Entrer la nouvelle valeur: ";
        getline(std::cin,entree);
        break;
    }
    case 5:{
        parametre = "Taille";
        std::cout<<"Entrer la nouvelle valeur: ";
        getline(std::cin,entree);
        break;
    }
    case 6:{
        parametre = "Poids";
        std::cout<<"Entrer la nouvelle valeur: ";
        getline(std::cin,entree);
        break;
    }
    case 7:{
        parametre = "GroupeSanguin";
        std::cout<<"Entrer la nouvelle valeur: ";
        getline(std::cin,entree);
        break;
    }
    case 8:{
        parametre = "Accompagnateur";
        std::cout<<"Entrer la nouvelle valeur: ";
        getline(std::cin,entree);
        break;
    }
    case 9:{
        parametre = "MedecinEnCharge";
        std::cout<<"Entrer la nouvelle valeur: ";
        getline(std::cin,entree);
        break;
    }
    case 10:{
        parametre = "DateConsultation";
        std::cout<<"Entrer la nouvelle valeur: ";
        getline(std::cin,entree);
        break;
    }
    default: {
        std::cout << "⚠️ Choix invalide. Veuillez entrer un nombre entre 1 et 10." << std::endl;
        break;
    }

}
        if (maj != 10) {
            std::cout << "\nAppuyez sur Entrée pour continuer...";
            std::cin.get();  // attend que l'utilisateur appuie sur Entrée
            }
    }
    return true;
    }
    bool Medecin::annulerConsultation(Ultimate_Database_Manager& db,const Patient& p){
         sqlite3_stmt* stmt;
         sqlite3* DB;
          const char* sqlDelete="DELETE FROM Consultations WHERE Nom_du_Patient= ?;";

    if (sqlite3_prepare_v2(DB,sqlDelete,-1,&stmt,nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt,1,p.nom_Patient.c_str(),-1,nullptr);
        if(sqlite3_step(stmt)!= SQLITE_DONE ){
            std::cerr<<"Erreur d'acces aux consultations"<<std::endl;

            return false;
        }
    }
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return true;
    }
    bool Medecin::creerConsultation(Ultimate_Database_Manager& db,Patient& p ){
        Consultation c;
       std::cout <<"______NOUVELLE CONSULTATION______ \n"<< std::endl;

    std::cout <<"Nom du Patient \n"<< std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(std::cin,p.nom_Patient);
    std::cout <<"Date de Consultation \n"<< std::endl;
    getline(std::cin, c.Date );
    std::cout <<"Etat de la Consultation(Option:En cours;Effectuée;Annulée ) \n"<< std::endl;
    getline(std::cin, c.Etat_de_la_Consultation );
    std::cout <<"Motif \n"<< std::endl;
    getline(std::cin, c.Motif );
    std::cout <<"Notes du médecin \n"<< std::endl;
    getline(std::cin,c.Notes_du_medecin);
    std::cout <<"Notes infirmier \n"<< std::endl;
    getline(std::cin,c.Notes_infirmier);
    std::cout << "Prescription \n"<< std::endl;
    getline(std::cin,c.Prescription);
    std::cout<< "Examen effectues \n"<< std::endl;
    getline(std::cin, c.examens);
    std::cout<<"Accompagnateur \n"<< std::endl;
    getline (std::cin,c.Prochain_rendez_vous);
    db.createConsultation("Gestionnaire.db",p);
// DELETE
    return true;
    }
    bool Medecin::accederConsultation(Ultimate_Database_Manager& db,const Patient& p){
        sqlite3_stmt* stmt;
        sqlite3* DB;
        std::cout << "__________CONSULTATION DU PATIENT__________" << p.nom_Patient << std::endl;
        const char* sql = "SELECT * FROM Consultations WHERE Nom_du_Patient= ?;";


    if (sqlite3_prepare_v2(DB,sql,-1,&stmt,nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt,1,p.nom_Patient.c_str(),-1,nullptr);
        if(sqlite3_step(stmt)!= SQLITE_DONE ){
            std::cerr<<"Erreur d'acces aux consultations"<<std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(DB);
            return false;
        }
    }
    sqlite3_finalize(stmt);
        sqlite3_close(DB);
        return true;
    }
    bool Medecin::telechargerDossier(Ultimate_Database_Manager& db,Patient& p){
        std::cout <<"Entrer le nom du patient\n"<< std::endl;
        getline (std::cin,p.nom_Patient);
           if (db.download_Dossier ("Gestionnaire.db",p)){
             std::cout<<"le dossier est telecgarger"<<std::endl;
           }
           else{
            std::cout<<"Erreur dans le telechargement"<<std::endl;
           }
    return true;
    }

