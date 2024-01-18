/*!
*\file Interaction.cpp
*\author NABE Mamoudou & KEITA Sidy
*\
*/

#include "Interaction.h"

    /**
     * @brief Interaction::Interaction: implementation de notre constructeur avec 2 parametres
     * @param date: est de type Date
     * @param visite:est de type string
     * @details:Rien à mettre dans le corps du constructeur, tout a déjà été fait !
     */
Interaction::Interaction(const Date &date,const std::string  &visite):rdv(date),contenu(visite)
{

}
    /**
     * @brief Interaction::Interaction
     * @details:Rien à mettre dans le corps du constructeur, tout a déjà été fait !
     */
Interaction::Interaction():rdv(),contenu("")
{

}
    /**
     * @brief Interaction::getContenu: on recuperela variable contenu
     * @return la variable contenu
     */
std::string Interaction::getContenu() const
{
    return contenu;
}
    /**
     * @brief Interaction::setContenu: on fait la mise à jour de la variable  contenu
     * @param cont:est de string
     */
void Interaction::setContenu(const std::string  & cont)
{
    contenu=cont;
}



int Interaction::getIdInteractionInter() const
{
    return IdInteractionInter;
}

void Interaction::setIdInteractionInter(const int & id)
{
    IdInteractionInter=id;
}

int Interaction::getIdContactInter() const
{
    return IdContactInter;
}

void Interaction::setIdContactInter(const int &id)
{
    IdContactInter=id;
}


/**
     * @brief Interaction::getRDV: recupere la variable rdv
     * @return rdv
     */
Date Interaction::getRDV() const
{
    return rdv;
}

    /**
     * @brief Interaction::setRDV : modifie la variable rdv de la classe
     * @param date:est de type Date
     */
void Interaction::setRDV(const Date & date)
{
    rdv=date;
}

    /**
     * @brief Interaction::operator <
     * @param i1
     * @return true si le rdv actuel est anterieur
     */
bool Interaction::operator<(const Interaction &i1) const
{
    if(this->getRDV()<i1.getRDV())
    {
        return true;
    }
    return false;
}

    /**
     * @brief operator <<:pour afficher
     * @param o:est de type ostream
     * @param action:est de type Interaction
     * @return o
     */
std:: ostream& operator <<(std:: ostream & o, const Interaction & action)
{

    o<<"rdv le "<<action.getRDV()<<" Aperçu: "<<action.getContenu();

    return o;
}
