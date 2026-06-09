#include <iostream>
#include "User.h"
#include <sqlite3.h>
#include "Ultimate_Database_Manager.h"
using namespace std;

int main()
{
    std::cout<< " ______Bienvenue sur la plateforme de Gestion_____" << std::endl;
    Ultimate_Database_Manager db("Gestionnaire.db");
    db.createTable("Gestionnaire.db");

    User u;
    if (u.seConnecter(db))
    {
        u.menu(db);
        return 0;
    }
}
