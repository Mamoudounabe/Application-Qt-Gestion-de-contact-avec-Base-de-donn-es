/**
    *@file Contact.h
    *@brief Fichier d'en-tete de la classe Contact
    *@author NABE Mamoudou
    *@author KEITA Sidy
*/

#ifndef TODO_H
#define TODO_H
#include"Date.h"
#include<ostream>
#include<string>
#include <iostream>
    /**
     * @brief The Todo class
     * @details: gere une tache suivant son contenu et sa date de creation
     */
class Todo{
     /**
     * @details: indique une date de tache
     * @var date
     * @var ContenuTodo
     */
private:
    Date date;
    std::string ContenuTodo;
    int IdTodo=0;
    int IdInter=0;


public:
    /**
     * @brief Todo :constructeur sans parametre
     */
     Todo();
    /**
     * @brief Todo: constructeur avec 2 parametres
     * @param Date: definie une date de tache a faire
     * @param string: commentaire d'un contenu de la tache
     */
    Todo(const Date &,const std::string &);

    /**
     * @brief getDateTodo: une methode getter
     * @return la date de tache
     */
    Date getDateTodo() const;

    /**
     * @brief getContenuTodo: methode getter
     * @return le contenu d'une tache à faire
     */

    std::string getContenuTodo() const;


    int getIdTodo() const;

    int getIdInteractionTodo() const;

    /**
     * @brief stDateTodo : une methode setter
     * @param Date: modifie la date d'une tache courante
     */
     void setDateTodo(const Date &);

    /**
     * @brief setContenuTodo: une methode setter
     * @param string : modifie le contenu d'une tache
     */
    void setContenuTodo(const std::string &);

    void setIdTodo(const int &);
    void setIdInteractionTodo(const int &);


    /**
     * @details : compare la tache courante à celle passée en @param (Todo
     *
     */
    bool operator<(const Todo &) const;

    /**
     * @details affiche les proprietes d'une tache
     *
     */
    friend std::ostream& operator<<(std::ostream&,const Todo&);


};

#endif // TODO_H
