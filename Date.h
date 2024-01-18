/**
    *@file Date.h
    *@brief Fichier d'en-tete de la classe Date
    *@author NABE Mamoudou
    *@author KEITA Sidy
*/

#ifndef DATE_H
#define DATE_H
#include<time.h>
#include<ctime>// equivalent de time.h en c++
#include<string>
#include <ostream>
#include <iostream>

    /**
     * @brief The Date class  : permet d'horlodater nos interactions ou nos evenements
     */

class Date{
        /**
     * @brief les attributs de la classe date on les symbolise par @var
     * @var date
     * @var jour
     * @var mois
     * @var annee
     */
private:
        struct tm *date;
        int jour;
        int mois;
        int annee;
public:

        /**
      * @brief Date Les constructeurs
      */

     Date();
     Date(const int &,const int &,const int &);


     /*Les getteurs ou les accesseurs qui vont nous permettre
     de recuperer  les differents attributs de la classe
     chaque methode renvoie un attribut   */
     /**
      * @brief getJour_strutm
      * @return recupere le jour de notre structure tm
      */
     int getJour_strutm() const;
     /**
      * @brief getMois_strutm
      * @return recupere le mois de notre structure tm
      */
     int getMois_strutm() const;
     /**
      * @brief getAnnee_strutm
      * @return recupere le mois de notre structure tm
      */
     int getAnnee_strutm() const;
     /**
      * @brief getJour_date
      * @return recupere le mois de notre structure tm
      */
     int getJour_date() const;
     /**
      * @brief getMois_date
      * @return recupere le mois de notre structure tm
      */
     int getMois_date() const;
     /**
      * @brief getAnnee_date
      * @return retourne le jour de la date
      */
     int getAnnee_date() const;


     /**
      * @brief les mutateurs
      */
     /**
      * @brief setJour_date: fait la mise à jour de l'attribut jour de la classe
      */
     void setJour_date(const int &);
     /**
      * @brief setMois_date: fait la mise à jour de l'attribut mois de la classe
      */
     void setMois_date(const int &);
     /**
      * @brief setAnnee_date:fait la mise à jour de l'attribut annee de la classe
      */
     void setAnnee_date(const int &);

     /**
      * @brief fromDate :methode pour remplir la date
      */
     void fromDate(const int &,const int &,const int &);
     /**
      * @brief fromDateString :methode pour remplir la date
      */
     std::string fromDateString() const;

     std::string  toString() const;
     /**
      * @brief toDateString:convertie le string  en type date
      */
     Date toDateString(const std:: string &) const;

     /**
      * @brief operator <:pour comparer une date courante à une date d'entrée
      */
     bool operator<(const Date &) const;
     /**
      * @brief operator <<:pour comparer une date courante à une date d'entrée
      */
     friend std::ostream& operator <<(std:: ostream&, const Date&);
};

#endif // DATE_H
