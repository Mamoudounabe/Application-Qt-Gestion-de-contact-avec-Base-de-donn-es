/*!
*\file Date.cpp
*\author NABE Mamoudou & KEITA Sidy
*\
*/


#include "Date.h"

//DEBUT constructeurs
Date::Date()// constructeur par defaut
{
    time_t n=time(0);
    date =localtime(&n);
    this->setJour_date(getJour_strutm());
    this->setMois_date(getMois_strutm());
    this->setAnnee_date(getAnnee_strutm());

}
Date::Date(const int &a,const int &m,const int &j)// on fait appel à la methode fromDate()
{
    fromDate(j,m,a);//j m a remplacent la date courante
}
//FIN Constructeurs


// DEBUT getters
int Date::getJour_strutm() const
{
    return date->tm_mday;// retourne le jour en utilisant la structure
}
int Date::getMois_strutm() const
{
    return date->tm_mon+1;// retourne le mois en utilisant la structure
}
int Date::getAnnee_strutm() const
{
    return date->tm_year+1900;// retourne l'année en utilisant la structure
}

int Date::getJour_date() const
{
    return jour;
}
int Date::getMois_date()const
{
    return mois;
}
int Date::getAnnee_date()const
{
    return annee;
}
// FIN getters

//DBUT setters

/*void Date:: setJour_date(const int &j)
{
    fromDate(j,getMois_strutm(),getAnnee_strutm());
}*/
void Date::setJour_date(const int & j)
{
    fromDate(j,getMois_strutm(),getAnnee_strutm());
}

void Date::setMois_date(const int &mois)
{
    fromDate(getJour_strutm(),mois,getAnnee_strutm());
}
void Date::setAnnee_date(const int &annee)
{
    fromDate(getJour_strutm(),getMois_strutm(),annee);
}

void Date::fromDate(const int &J,const int &M,const int &A)
{
    time_t tim=time(NULL); //on initialise la structure
    struct tm * tem=localtime(&tim);//on met dans tem la date courrante
    tem->tm_mday=J;//on met dans tem le jour passé en parametre
    tem->tm_mon=M-1;

    tem->tm_year=A-1900;

    tim=mktime(tem);

    date=localtime(&tim);

    this->annee = getAnnee_strutm();//on récupère l'année
    this->mois = getMois_strutm();//on récupère le mois
    this->jour= getJour_strutm();//on récupère le jour
}

std::string  Date::fromDateString() const
{
    std::string momois=std::to_string(getMois_date());
    std::string mojour=std::to_string(getJour_date());
    if(getMois_date()<10)
    {
        momois="0"+std::to_string(getMois_date());
    }
    if(getJour_date()<10)
    {
        mojour="0"+std::to_string(getJour_date());
    }

    return std::to_string(getAnnee_date())+"-"+momois+"-"+mojour;
}

Date Date::toDateString(const std::string &d) const
{

    std::string d1=d.substr(0,4);
    std::string d2=d.substr(5,2);
    std::string d3=d.substr(8,2);
    int a=std::stoi(d1);
    int m=std::stoi(d2);
    int j=std::stoi(d3);
    Date dat(a,m,j);
    return    dat;
}

bool Date::operator<(const Date &d) const
{
    if(this->getAnnee_date()<d.getAnnee_date())
    {
        return true;
    }
    else if(this->getAnnee_date()==d.getAnnee_date() && this->getMois_date()<d.getMois_date())
    {
        return true;
    }
    else if(this->getAnnee_date()==d.getAnnee_date()&&this->getMois_date()==d.getMois_date()&&this->getJour_date()<d.getJour_date())
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::ostream& operator <<(std::ostream &os, const Date &temp)
{
    os<<temp.getAnnee_date() << "-" << temp.getMois_date() << "-" << temp.getJour_date()<<"";
    return os;
}



std::string Date:: toString() const
{
    std::string momois = std::to_string(getMois_date());
    std::string mojour = std::to_string(getJour_date());
    if (getMois_date() < 10) {
        momois = "0" + std::to_string(getMois_date());
    }
    if (getJour_date() < 10) {
        mojour = "0" + std::to_string(getJour_date());
    }

    return std::to_string(getAnnee_date()) + "-" + momois + "-" + mojour;
}
