#ifndef PROFESSIONNEL_DE_SANTE_H
#define PROFESSIONNEL_DE_SANTE_H
#include "User.h"
#include <string>

class professionnel_de_sante : public User

{ public:
        professionnel_de_sante();
        ~professionnel_de_sante();
        professionnel_de_sante(const professionnel_de_sante& other);


    protected:
    std::string specialite;
    private:
};


#endif // PROFESSIONNEL_DE_SANTE_H
