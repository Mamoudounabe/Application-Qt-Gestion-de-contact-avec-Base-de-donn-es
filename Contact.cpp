/*!
*\file Contact.cpp
*\author NABE Mamoudou & KEITA Sidy
*\
*/

#include "Contact.h"
#include "Date.h"
#include<string>
/**
   *@brief Debut Construsteurs
   *@details Ce constructeur ne prend pas de parametres

*/
Contact::Contact():nom(""),prenom(""),entreprise(""),mail(""),tel(""),URphoto(""),DateDecreation()
{

    //Rien à mettre dans le corps du constructeur, tout a déjà été fait !
}
Contact::Contact(const std::string & Nom,const std::string & Prenom,const std::string & Entreprise,const std::string & Mail,const std::string & Tel,const std::string & Photo):nom(Nom),
prenom(Prenom),entreprise(Entreprise),mail(Mail),tel(Tel),URphoto(Photo)
{

}

//Fin Constructeurs


//Debut getters
std:: string Contact::getNom() const
{
    return nom;
}
std:: string Contact::getPrenom()const
{
    return prenom;
}
std:: string Contact::getEntreprise() const
{
    return entreprise;
}

std::string Contact::getMail() const
{
    return mail;
}

std:: string Contact::getTel() const
{
    return tel;
}
std:: string Contact ::getPhoto() const
{
    return URphoto;
}
Date Contact:: getDateDecreation() const
{
    return DateDecreation;
}

int Contact::getIdContact() const
{
    return IdContact;
}
// Fin getters



// DEBUT setters
void Contact:: setNom(const std::string &Nom)
{
    nom=Nom;
}

void Contact:: setPrenom(const std::string &Prenom)
{
    prenom=Prenom;
}

void Contact:: setEmtreprise(const std::string &Entreprise)
{
    entreprise=Entreprise;
}

void Contact:: setMail(const std::string &Mail)
{
    mail=Mail;
}
void Contact:: setTel(const std::string &Tel)
{
    tel=Tel;
}

void Contact:: setPhoto(const std::string &Photo)
{
    URphoto=Photo;
}


void Contact::setDateDecreation(const Date &d)
{
    DateDecreation=d;
}

void Contact :: setIdContact(const int &v)
{
    IdContact=v;
}

//FIN setters


bool Contact::operator==(const Contact &c) const
{
    if (getNom()==c.getNom() && getPrenom()==c.getPrenom() && getEntreprise()==c.getEntreprise() && getTel()==c.getTel() && getPhoto()==c.getPhoto())
    {
         return true;
    }
    else {
         return false;
    }

}

bool Contact::operator<(const Contact &d) const
{
    if(this->getDateDecreation()<d.getDateDecreation())
    {
         return true;
    }
    else
    {
         return false;
    }
}

std::ostream& operator <<(std:: ostream &o,const Contact &c)
{
    o<<"\n"<<c.getNom()<<"\n";
    o<<c.getPrenom()<<"\n";
    o<<c.getEntreprise()<<"\n";
    o<<c.getMail()<<"\n";
    o<<c.getTel()<<"\n";
    o<<c.getPhoto()<<"\n";
    o<<c.getDateDecreation().fromDateString()<<"\n";

    return o;

}
