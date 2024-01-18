
/**
    *@file Interaction.h
    *@brief Fichier d'en-tete de la classe Interaction
    *@author NABE Mamoudou
    *@author KEITA Sidy
*/

#ifndef INTERACTION_H
#define INTERACTION_H

#include<ostream>
#include<string>
#include"Date.h"
#include <iostream>

    /**
    *@class InteractionTodo
    *@brief  cette classe permet de gerer une liste de tache à faire
    *tout en ajoutant un contact et en le supprimant .
    */

class Interaction
{
private:
    /**
     * @brief les attributs de la classe Interaction on les symbolise par @var
     * @brief rdv
     * @brief contenu
     */
    Date rdv;
    std::string contenu;
    int IdInteractionInter=0;
    int IdContactInter=0;



public :
    /**
     * @brief Interaction le construteur
     */
    Interaction();

    /**
     * @brief Interaction
     * @param Date: definie une date de rdv
     * @param string: commentaire du rdv
     */

    Interaction(const Date &,const std::string &);

    /**
     * @brief getContenu: une methode getter
     * @return le contenu du rdv
     */
    std::string getContenu()const;

    /**
     * @brief getRDV :une methode getter
     * @return la date du rdv
     */
    Date getRDV() const;

    int getIdInteractionInter() const;
    int getIdContactInter() const;

    void setIdInteractionInter(const int &);
    void setIdContactInter(const int &);

    /**
     * @brief setRDV:une methode setter
     * @param Date:modifie la date du rdv
     */
    void setRDV(const Date &);

    /**
     * @brief setRDV:une methode
     * @param modifie le contenu du rdv
     */
    void setContenu(const std::string &);

    /**
     * @details fait la comparaison de l'interaction courante suivant
     *  le @param Interaction
     *
     */
    bool operator<(const Interaction &) const;

    /**
     * @details affiche une Interaction
     *
     */
    friend std:: ostream& operator <<(std::ostream &,const Interaction &);

};

#endif // INTERACTION_H
