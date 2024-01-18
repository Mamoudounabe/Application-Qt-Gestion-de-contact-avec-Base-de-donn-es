/*!
*\file ContactBD.cpp
*\author NABE Mamoudou & KEITA Sidy
*\
*/
#include "ContactBD.h"

ContactBD::ContactBD(QObject *parent)
    : QObject{parent}
{
    BDOuvert=false;
    connexionBD();
}

ContactBD::~ContactBD()
{
    closeBD();
}

void ContactBD::closeBD()
{
    if(BDOuvert==true)
    {
        BD.close();
    }
}

bool ContactBD::connexionBD()
{

    QString Chemin="/tmp/bddprojet.sqlite";
    BD=QSqlDatabase::addDatabase("QSQLITE");

    BD.setDatabaseName(Chemin);

    if(!BD.open())
    {
        qDebug()<<"Impossible d'ouvrir la base \n";
        BDOuvert=false;
    }
    else
    {
        qDebug()<<"ouverture de la base reussie";
        BDOuvert=true;
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS CONTACT"
                   "(id_contact integer primary key AUTOINCREMENT, "
                   "nom TEXT NOT NULL,"
                   "prenom TEXT NOT NULL,"
                   "entreprise TEXT NOT NULL,"
                   "mail TEXT NOT NULL,"
                   "telephone TEXT NOT NULL,"
                   "photo TEXT NOT NULL ,"
                   "datecreation TEXT)");
        if(!query.exec())
        {
            qDebug()<<"Erreur de la création de table contact";
        }
        else
        {
            qDebug()<<"création de la table reussi";
        }
    }
    return  BDOuvert;
}

void ContactBD::isBDopen(bool & b)
{
    BDOuvert=b;
}

void ContactBD::ListContact(std::list<Contact> &lc) const
{


    lc.clear();

    if(BDOuvert==true)
    {
        QSqlQuery query("SELECT * FROM CONTACT ");
        if(!query.exec())
        {
            qDebug()<<"Affichage echoue";
        }
        else
        {
            qDebug()<<"Requete reussie";

            while(query.next())
            {
                Contact co;
                QString r=query.value(0).toString();
                co.setIdContact(r.toInt());

                r=query.value(1).toString();

                co.setNom(r.toStdString());
                r=query.value(2).toString();

                co.setPrenom((r.toStdString()));
                r=query.value(3).toString();

                co.setEmtreprise((r.toStdString()));
                r=query.value(4).toString();

                co.setMail((r.toStdString()));
                r=query.value(5).toString();

                co.setTel((r.toStdString()));
                r=query.value(6).toString();

                co.setPhoto((r.toStdString()));
                r=query.value(7).toString();
                co.setDateDecreation(co.getDateDecreation().toDateString(r.toStdString()));

                lc.push_back(co);

            }
        }
    }
}


void ContactBD::BDListeContact(std::list<Contact> & co)
{
    ListContact(co);
    int n=NbrContact();
    emit NbrTotalContact(n);
}


int ContactBD::NbrContact() const
{
    if(BDOuvert==true)
    {
        QSqlQuery query;
        query.prepare("select  count(*) from CONTACT");//Requete pour compter le nombre de contact
        query.exec();
        if(!query.exec())
        {
            qDebug()<<"Compte échoué"  ;
                return -1;
        }

        else
        {
            int total; //déclaration d'un entier
            while(query.next())
            {
                total=query.value(0).toInt();//On met dans l'entier total la valeur qui se trouve à la position 0 convertie en entier

            }
            qDebug()<<"Compte reussi "  ;
            return total;
        }

    }
}

void ContactBD::BDNouveauContact(Contact & co)
{
    NouvContact(co);
}


bool ContactBD::NouvContact(const Contact & co) const
{
    if (BDOuvert == true)
    {
        QSqlQuery query("PRAGMA foreign_keys = ON;"
                        "SELECT * FROM CONTACT");
        // préparation de  la requêtez
        //QSqlQuery query("PRAGMA foreign_keys = ON");
        query.prepare("INSERT INTO CONTACT (nom, prenom, entreprise, mail,telephone, photo, datecreation) "
                      "VALUES(:n, :p, :e, :m, :t, :u, :d)");

        // remplir les valeurs
        query.bindValue(":n", QString::fromStdString(co.getNom()));
        query.bindValue(":p", QString::fromStdString(co.getPrenom()));
        query.bindValue(":e", QString::fromStdString(co.getEntreprise()));
        query.bindValue(":m", QString::fromStdString(co.getMail()));
        query.bindValue(":t", QString::fromStdString(co.getTel()));
        query.bindValue(":u", QString::fromStdString(co.getPhoto()));
        query.bindValue(":d", QString::fromStdString(co.getDateDecreation().fromDateString()));

        if (!query.exec())
        {
            qDebug() << "Insertion a échoué";
            return false;
        }
        qDebug() << "Insertion réussie";
    }
    return true;
}


bool ContactBD::ModifContact(const int &id,const Contact & co) const
{
    if(BDOuvert)
    {   QSqlQuery query("PRAGMA foreign_keys = ON");


        query.prepare("UPDATE CONTACT SET nom=:nn, prenom=:np, entreprise=:ne, mail=:nm, telephone=:nt, photo=:npp, datecreation=:nd WHERE id_contact=:n ");
        query.bindValue(":n", QString::number(id));
        query.bindValue(":nn",QString::fromStdString(co.getNom()));
        query.bindValue(":np",QString::fromStdString(co.getPrenom()));
        query.bindValue(":ne",QString::fromStdString(co.getEntreprise()));
        query.bindValue(":nm",QString::fromStdString(co.getMail()));
        query.bindValue(":nt",QString::fromStdString(co.getTel()));
        query.bindValue(":npp",QString::fromStdString(co.getPhoto()));
        query.bindValue(":nd",QString::fromStdString(co.getDateDecreation().fromDateString()));
        if(!query.exec())
        {
            qDebug()<<"Modification   echoue";
            return false;
        }
        qDebug()<<"Modification   accepté";
    }
    return true;
}

void ContactBD::BDModifContact(int & id,Contact &co)
{
    ModifContact(id,co);
}

bool ContactBD::RemoveContact(const int & id) const
{
    if(BDOuvert==true)
    {
        QSqlQuery query("PRAGMA foreign_keys = ON");
        query.prepare("DELETE  FROM CONTACT WHERE id_contact=:n");
        query.bindValue(":n", QString::number(id));
        query.exec();

        if(!query.exec())
        {
            qDebug()<<"Suppression echoue";
            return false;
        }
        qDebug()<<"Suppression reussie";

    }
    return true;
}

void ContactBD::BDRemoveContact(int & id)
{
    RemoveContact(id);
}


void ContactBD::RechercherContact(QString & noms, QString & date1 ,  QString & date2 ,std::list<Contact> & lc ) const
{
    lc.clear();
    Date d;

    Date d1=d.toDateString(date1.toStdString());
    Date d2=d.toDateString(date2.toStdString());

    if(BDOuvert==true)
    {
        QSqlQuery query;
        query.prepare("SELECT  * FROM CONTACT where nom=:n ");//Requete pour chercher dans la table contact le nom
        query.bindValue(":n",QString::fromStdString(noms.toStdString()));
        query.exec();


        if(!query.exec())
        {
            qDebug()<<"Recherche échoué";
        }
        else
        {
            qDebug()<<"Recherche réussi";

                while(query.next())
            {
                QString r=query.value(7).toString();
                Date dc=d.toDateString(r.toStdString());
                if(d1<dc && dc<d2 )
                {
                    Contact co;
                    r=query.value(0).toString();
                    co.setIdContact(r.toInt());
                    r=query.value(1).toString();
                    co.setNom(r.toStdString());
                    r=query.value(2).toString();
                    co.setPrenom((r.toStdString()));
                    r=query.value(3).toString();
                    co.setEmtreprise((r.toStdString()));
                    r=query.value(4).toString();
                    co.setMail((r.toStdString()));
                    r=query.value(5).toString();
                    co.setTel((r.toStdString()));
                    r=query.value(6).toString();
                    co.setPhoto((r.toStdString()));
                    co.setDateDecreation(dc);
                    lc.push_back(co);
                }


            }
            lc.sort();//on trie les contacts qui se trouvent dans la liste en faisant appel à la fonction c++ sort() .

        }
    }

}


void ContactBD::BDRechercherContact( QString & nom, QString & date1 ,  QString & date2 ,std::list<Contact> & lc )
{
    RechercherContact(nom,date1,date2,lc);
}




