/*!
*\file InteractionBD.cpp
*\author NABE Mamoudou & KEITA Sidy
*\
*/

#include "InteractionBD.h"

InteractionBD::InteractionBD(QObject *parent)
    : QObject(parent)
{
        BDOuvert=false;
        connexion();
}

InteractionBD::~InteractionBD()
{
      closeDb();
}


bool InteractionBD::connexion()
{
        BD=QSqlDatabase::addDatabase("QSQLITE");
        QString Chemin="/tmp/bddprojet.sqlite";

        BD.setDatabaseName(Chemin);

        if(!BD.open())
        {
            qDebug()<<"base non ouvert\n";
            BDOuvert=false;
        }
        else
        {
            qDebug()<<"ouverture  interaction reussie";
            BDOuvert=true;
            QSqlQuery query;
            query.exec("CREATE TABLE IF NOT EXISTS INTERACTION"
                       "(id_interaction integer primary key AUTOINCREMENT, "
                       "id_contact integer NOT NULL,"
                       "dateinteraction TEXT,"
                       "contenu TEXT,"
                       "FOREIGN KEY (id_contact) REFERENCES CONTACT(id_contact) ON DELETE CASCADE )");
            if(!query.exec())
            {
                qDebug()<<"Echec de la création de la table interaction";
            }
            else
            {
                qDebug()<<" creation de la table reussi";
            }
        }
        return  BDOuvert;
}


bool InteractionBD::AjoutInteraction(const int & id,Interaction & inter)
{
        if(BDOuvert==true)
        {
            QSqlQuery query("PRAGMA foreign_keys = ON"
                            "SELECT * from INTERACTION ");
            //preparation de la requete
            query.prepare("INSERT INTO INTERACTION(id_contact,dateinteraction,contenu) "
                          "VALUES(:n, :m, :p)");
            //remplissage de valeur
            query.bindValue(":n",QString::number(id));
            query.bindValue(":m", QString::fromStdString(inter.getRDV().fromDateString()));
            query.bindValue(":p",QString::fromStdString(inter.getContenu()));

            if(!query.exec())
            {
                qDebug()<<"ajout de l'interaction non effectue";
                return false;
            }
            qDebug()<<"ajout de l'interaction bien réussi ";

        }
        return true;
}


void InteractionBD::bddAjoutInteraction(int &i , Interaction & inter)
{
      AjoutInteraction(i,inter);
}


void InteractionBD::ListeInteraction(const int & id, std::list<Interaction> & li) const
{
        li.clear();
        if(BDOuvert==true)
        {
            QSqlQuery query;
            query.prepare("SELECT * FROM INTERACTION WHERE id_contact=:n");
            query.bindValue(":n",QString::number(id));
            query.exec();
            if(!query.exec())
            {
                qDebug()<<"echec de la requete d'affichage de la liste";
            }
            else {
                qDebug()<<" affichage reussie";
                while(query.next())
                {
                    Interaction inter;
                    QString r=query.value(0).toString();
                    inter.setIdInteractionInter(r.toInt());

                    r=query.value(1).toString();

                    inter.setIdContactInter(r.toInt());
                    r=query.value(2).toString();

                    inter.setRDV(inter.getRDV().toDateString(r.toStdString()));
                    r=query.value(3).toString();

                    inter.setContenu(r.toStdString());

                    li.push_back(inter);

                }
                li.sort();
            }

        }
}

void InteractionBD::ListeInteractionALL(std::list<Interaction> & li) const
{
        li.clear();

        if(BDOuvert==true)
        {
            QSqlQuery query("SELECT  * FROM INTERACTION  ");



            if(!query.exec())
            {
                qDebug()<<"probleme d'affichage de recherche des interactions";
            }
            else
            {
                qDebug()<<"Affichage réussi pour la recherche interactions";

                    while(query.next())
                {

                    Interaction inter;
                    QString  r=query.value(0).toString();
                    inter.setIdInteractionInter(r.toInt());

                    r=query.value(1).toString();

                    inter.setIdContactInter(r.toInt());
                    r=query.value(2).toString();
                    inter.setRDV(inter.getRDV().toDateString(r.toStdString()));
                    r=query.value(3).toString();

                    inter.setContenu(r.toStdString());

                    li.push_back(inter);
                }


            }


        }

}

void InteractionBD::bddListeInteraction(int & id, std::list<Interaction> & li)
{
      ListeInteraction(id,li);
}





void InteractionBD::bddListeInteractionALL(std::list<Interaction> & li)
{
      ListeInteractionALL(li);
}

void InteractionBD::RechercheInteraction(QString & date1, QString & date2, std::list<Interaction> & li)
{
        li.clear();
        Date d;

        Date d1=d.toDateString(date1.toStdString());
        Date d2=d.toDateString(date2.toStdString());

        if(BDOuvert==true)
        {
            QSqlQuery query("SELECT  * FROM INTERACTION  ");



            if(!query.exec())
            {
                qDebug()<<"Requete échoué ";
            }
            else
            {
                qDebug()<<"Recherche réussi ";

                    while(query.next())
                {
                    QString r=query.value(2).toString();
                    Date dc=d.toDateString(r.toStdString());
                    if(d1<dc && dc<d2 )
                    {
                        Interaction inter;
                        r=query.value(0).toString();
                        inter.setIdInteractionInter(r.toInt());

                        r=query.value(1).toString();

                        inter.setIdContactInter(r.toInt());


                        inter.setRDV(dc);
                        r=query.value(3).toString();

                        inter.setContenu(r.toStdString());

                        li.push_back(inter);//ajout de l'intéraction dans la liste
                    }


                }
                li.sort(); //tri la liste d'intéraction

            }
        }


}

void InteractionBD::bddRechercheInteraction(QString & date1, QString & date2, std::list<Interaction> &li)
{
       RechercheInteraction(date1,date2,li);
}

void InteractionBD::RechercheInteractionCont(int & id, QString & date1, QString &date2, std::list<Interaction> & li)
{
        li.clear();
        Date d;

        Date d1=d.toDateString(date1.toStdString());
        Date d2=d.toDateString(date2.toStdString());

        if(BDOuvert==true)
        {
            QSqlQuery query;
            query.prepare("SELECT interaction.id_interaction ,interaction.id_contact ,interaction.dateinteraction,interaction.contenu"
                          " from INTERACTION,CONTACT "
                          "where INTERACTION.id_contact=CONTACT.id_contact"
                          " and "
                          "CONTACT.id_contact=:n");

            query.bindValue(":n",QString::number(id));
            query.exec();


            if(!query.exec())
            {
                qDebug()<<"probleme niveau recherche contact";
            }
            else
            {
                qDebug()<<"commençons la  recherche de l'interaction du contact";

                    while(query.next())
                {
                    QString r=query.value(2).toString();
                    Date dc=d.toDateString(r.toStdString());
                    if(d1<dc && dc<d2 )
                    {
                        Interaction inter;
                        r=query.value(0).toString();
                        inter.setIdInteractionInter(r.toInt());

                        r=query.value(1).toString();

                        inter.setIdContactInter(r.toInt());
                        r=query.value(2).toString();

                        inter.setRDV(dc);
                        r=query.value(3).toString();

                        inter.setContenu(r.toStdString());

                        li.push_back(inter);
                    }


                }
                li.sort();
            }

        }
}

void InteractionBD::bddRechercheInteractionCont(int & id, QString & date1, QString &date2, std::list<Interaction> & li)
{
     RechercheInteractionCont(id,date1,date2,li);
}

void InteractionBD::isOpen(bool &b)
{
     isDBopen(b);
}

void InteractionBD::closeDb()
{
        if(BDOuvert==true)
        {
            BD.close();
        }

}

void InteractionBD::isDBopen(bool &b)
{
         BDOuvert=b;
}

