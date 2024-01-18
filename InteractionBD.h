/*!
*\file InteractionBD.h
*\author NABE Mamoudou & KEITA Sidy
*\
*/

#ifndef INTERACTIONBD_H
#define INTERACTIONBD_H

#include "Interaction.h"
#include <QObject>
#include <QString>
#include <string>
#include <QVariant>
#include <QObject>
#include <QDate>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <list>
/**
 * @brief The InteractionBD class
 * @details : Ajoute des interactions pour un contact donné
 */
class InteractionBD : public QObject
{
    Q_OBJECT
private:
    /**
        * @brief BD : connexion a la base de donnee
        */
       QSqlDatabase BD;
    /**
        * @brief BDOuvert: verifie l'etat de la base
        */
       bool BDOuvert;

       /**
        * @brief closeDb : ferme si elle est ouverte
        */
       void closeDb();

       /**
        * @brief connexion :permet d'etablir dans la base de données
        * et elle cree par la meme occasion une table Interaction dans la base
        * si elle n'est n'existe pas
       * @return true si la connexion a reussie sinon false
        */
       bool connexion();

       /**
        * @brief isDBopen: qui change l'etat de la base
        */
       void isDBopen(bool &);

       /**
        * @brief AjoutInteraction: ajout d'une interaction
        * permet d'ajouter une interaction pour un contact
        * @return true s'il est  inserer dans la base sinon false
        */
       bool AjoutInteraction(const int &,Interaction &);

       /**
        * @brief ListeInteraction: liste des Interactions
        * permet de recuperer la liste des interactions d'un contact selectionné
        *
        */
       void ListeInteraction(const int &,std::list<Interaction> &)const ;
 public:

       /**
        * @brief InteractionBD : Le constructeur
        * @param parent
        */
       explicit InteractionBD(QObject *parent = nullptr);
        /**
        * @brief ~InteractionBD : Le Destructeur
        */
       ~InteractionBD();

   signals:

 public:
       void ListeInteractionALL(std::list<Interaction> &)const ;
       void RechercheInteraction(QString &,QString &,std::list<Interaction> &);
       void RechercheInteractionCont(int &,QString &,QString &,std::list<Interaction> &);

 public slots:
       void bddAjoutInteraction(int &,Interaction &);
       void bddListeInteraction(int &,std::list<Interaction> &);
       void bddListeInteractionALL(std::list<Interaction> &);
       void bddRechercheInteraction(QString &,QString &,std::list<Interaction> &);
       void bddRechercheInteractionCont(int & , QString & , QString & , std::list<Interaction> &);
       void isOpen(bool &);
};

#endif // INTERACTIONBD_H
