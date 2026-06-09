#ifndef ADMINISTRATEUR_H
#define ADMINISTRATEUR_H

#include "User.h"
#include <string>


class Ultimate_Database_Manager;
class Administrateur: public User {
public:
    Administrateur();
    ~Administrateur();
    Administrateur(const Administrateur& other);

    bool Ajouter_utilisateur(Ultimate_Database_Manager& db);

    bool Supprimer_utilisateur(Ultimate_Database_Manager& db, User u);

    bool Gerer_acces(Ultimate_Database_Manager& db);

    bool menu (Ultimate_Database_Manager& db);

    bool Stat_shower(Ultimate_Database_Manager& db);

    bool Mettre_a_jour(Ultimate_Database_Manager& db);

protected:
    std::string Generateur_password();
private:

};

#endif // ADMINISTRATEUR_H
