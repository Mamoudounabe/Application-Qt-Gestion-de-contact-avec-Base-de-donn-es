/**
    *@file Contact.h
    *@brief Fichier d'en-tete de la classe Contact
    *@author NABE Mamoudou
    *@author KEITA Sidy
*/

#ifndef CONTACT_H
#define CONTACT_H
#include"Date.h"
#include<string>
#include<iostream>
#include <ostream>
    /**
     * @brief Creation de la classe Contact :nous permet de creer un ou plusieurs contact pour notre application
    */

class Contact{


     /**
     * @brief : Declaration des attributs de la classe Contact on les symbolise par @var
     * @var nom
     * @var prenom
     * @var mail
     * @var tel
     * @var URphoto
     * @var DateDecreation
     */

private:
        std::string nom;
        std::string prenom;
        std::string entreprise;
        std::string mail;
        std::string tel;
        std::string URphoto;
        Date DateDecreation ;
        int IdContact=0;
 public:

     /**
      * @brief Creation de nos constructeurs
      * @details: Le rôle principal du constructeur est d'initialiser les attributs
      */

     Contact();
     Contact(const std::string & nom,const std::string & prenom,const std::string & entreprise,
             const std::string & mail,const std::string & tel,const std::string & photo);


     /**
      * @details 1: Les getteurs ou les accesseurs qui vont nous permettre
      *  de recuperer  les differents attributs de la classe
      *   chaque methode renvoie un attribut
      */



     /**
      * @brief getNom
      * @return on recupere le nom de la classe methode
      */
     std::string getNom() const;
     /**
      * @brief getPrenom
      * @return on recupere le prenom de la classe methode
      */
     std::string getPrenom() const;
     /**
      * @brief getEntreprise
      * @return on recupere l'entreprise de la classe methode
      */
     std::string getEntreprise() const;
     /**
      * @brief getMail
      * @return on recupere le mail de la classe methode
      */
     std::string getMail() const;
     /**
      * @brief getTel
      * @return on recupere le telephone de la classe methode
      */
     std::string getTel() const;
     /**
      * @brief getPhoto
      * @return on recupere la photo de la classe methode
      */
     std::string getPhoto() const;

     /**
      * @brief getDateDecreation
      * @return on recupere la date de creation de la classe methode
      */
     Date getDateDecreation() const;

     /**
     * @brief getIdContact
     * @return identifiant de contact
     */
    int getIdContact() const;
     /**
      * @details 2:les setters ou les mutateurs vont nous permettre de modifier les attributs
      *  chaque methode fait la mise à jour de  un attribut
      */

     /**
      * @brief setNom: fait la mise à de l'attribut nom par le @param donné par la methode
      * @param :string
      */
     void setNom(const std:: string &);

     /**
      * @brief setPrenom: fait la mise à jour dde l'attribut  prenom par le @param donné par la methode
      * @param :string
      */
     void setPrenom(const std:: string &);


     /**
      * @brief setEmtreprise :fait la mise à jour de l'attribut  l'Emtreprise par le @param donné par la methode
      * @param :string
      */
     void setEmtreprise(const std:: string &);
     /**
      * @brief setMail:fait la mise à jour de l'attribut   mail par le @param donné par la methode
      * @param:string
      */
     void setMail(const std:: string &);
     /**
      * @brief setTel :fait la mise à jour de l'attribut   telephone par le @param donné par la methode
      * @param:string
      */
     void setTel(const std:: string &);
     /**
      * @brief setPhoto:fait la mise à jour de l'attribut  URphoto par le @param donné par la methode
      * @param string
      */
     void setPhoto(const std:: string &);
     /**
      * @brief setDateDecreation : fait la mise à jour de l'attribut   DateDecreation
      */
     void setDateDecreation(const Date &);

      void setIdContact(const int &);

     /**
      * @brief operator ==: permet de faire la comparaison d'un contact à un autre suivant
      * leur nom prenom nom Entreprise email telephone au contact courant
      * @return  bool
      */
     bool operator==(const Contact &)const;
     /**
      * @brief operator <: fait une comparaison
      * @return bool
      */
     bool operator<(const Contact &) const;
     /**
      * @brief operator <<:pour l'affichage  des propriete d'un  contact
      * @return
      */
     friend std::ostream& operator<<(std:: ostream&,const Contact&);



};

#endif // CONTACT_H
