/*!
*\file TodoBD.cpp
*\author NABE Mamoudou & KEITA Sidy
*\
*/


#include "TodoBD.h"

TodoBD::TodoBD(QObject *parent)
    : QObject{parent}
{
       BDOuvert=false;
        connexion();
}


TodoBD::~TodoBD()
{
      closeDb();
}



bool TodoBD::connexion()
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
            qDebug()<<"ouverture  todo reussie";
            BDOuvert=true;
            QSqlQuery query;
            query.exec("CREATE TABLE IF NOT EXISTS TODO"
                       "(id_todo integer primary key AUTOINCREMENT, "
                       "id_interaction integer NOT NULL,"
                       "datetodo TEXT,"
                       "contenu TEXT,"
                       "FOREIGN KEY (id_interaction) REFERENCES INTERACTION (id_interaction) ON DELETE CASCADE )");/*création de la table ,
    la contrainte pour la clé etrangère ça signifie si l'enregistrement parent est supprimé tous les enregistrements enfants vont suivre .*/
            if(!query.exec())
            {
                qDebug()<<"Erreur de creation todo";
            }
            else
            {
                qDebug()<<" creation table reussi";
            }
        }
        return  BDOuvert;
}


bool TodoBD::AjoutTodo(const int & id,Todo & inter)
{
        if(BDOuvert==true)
        {
            QSqlQuery query("SELECT * from TODO ");
            //Insertion de la requete
            query.prepare("INSERT INTO TODO(id_interaction,datetodo,contenu) "
                          "VALUES(:n, :m, :p)"); //insertion des données
            //remplissage de valeur
            query.bindValue(":n",QString::number(id));
            query.bindValue(":m", QString::fromStdString(inter.getDateTodo().fromDateString()));
            query.bindValue(":p",QString::fromStdString(inter.getContenuTodo()));

            if(!query.exec())
            {
                qDebug()<<"insertion todo non effectue";
                return false;
            }
            qDebug()<<"ajout todo effectue";

        }
        return true;
}

void TodoBD::BDAjoutTodo(int &i , Todo & inter)
{
      AjoutTodo(i,inter);
}


void TodoBD::ListeTodoContact(const int & id,std::list<Todo> &li)const
{
        li.clear();
        if(BDOuvert==true)
        {
            QSqlQuery query;
            query.prepare("SELECT TODO.id_todo ,TODO.id_interaction,TODO.datetodo,TODO.contenu "
                          "FROM TODO,INTERACTION,CONTACT WHERE "
                          "TODO.id_interaction=INTERACTION.id_interaction and "
                          "INTERACTION.id_contact=CONTACT.id_contact and "
                          "CONTACT.id_contact=:n");
            query.bindValue(":n",QString::number(id));
            query.exec();
            if(!query.exec())
            {
                qDebug()<<"liste  Todo non ressortie";
            }
            else {
                qDebug()<<"requete  todo reussie";
                while(query.next())
                {
                    Todo inter;
                    QString r=query.value(0).toString();
                    inter.setIdTodo(r.toInt());

                    r=query.value(1).toString();

                    inter.setIdInteractionTodo(r.toInt());
                    r=query.value(2).toString();

                    inter.setDateTodo(inter.getDateTodo().toDateString(r.toStdString()));
                    r=query.value(3).toString();

                    inter.setContenuTodo(r.toStdString());

                    li.push_back(inter);

                }
                li.sort();
            }

        }
    }

    void TodoBD::BDListeTodoContact(int & id, std::list<Todo> & li)
    {
        ListeTodoContact(id,li);
    }



    void TodoBD::ListeALLContact(std::list<Todo> & li) const
    {
        li.clear();
        if(BDOuvert==true)
        {

            QSqlQuery  query("SELECT TODO.id_todo ,TODO.id_interaction,TODO.datetodo,TODO.contenu FROM TODO,INTERACTION,CONTACT WHERE "
                            "TODO.id_interaction=INTERACTION.id_interaction and "
                            "INTERACTION.id_contact=CONTACT.id_contact");
            /*cette requete permet de récuperer toutes les taches de toutes les intéractions \n de tous les contacts dans la base de donnée.*/

            if(!query.exec())
            {
                qDebug()<<"liste  Todo ALL non ressortie";
            }
            else {
                qDebug()<<"requete  todo ALL reussie";
                while(query.next())
                {
                    Todo inter;
                    QString r=query.value(0).toString();
                    inter.setIdTodo(r.toInt());

                    r=query.value(1).toString();

                    inter.setIdInteractionTodo(r.toInt());
                    r=query.value(2).toString();

                    inter.setDateTodo(inter.getDateTodo().toDateString(r.toStdString()));
                    r=query.value(3).toString();

                    inter.setContenuTodo(r.toStdString());

                    li.push_back(inter);


                }
                li.sort(); //on trie la liste des taches par la date de création  .
            }

        }
}

void TodoBD::BDListeALLContact(std::list<Todo> & li)
{
      ListeALLContact(li);
}

void TodoBD::RechercheTodoCont(const int &id,QString & date1 ,QString & date2,std::list<Todo> & li) const
{
        li.clear();
        Date d;

        Date d1=d.toDateString(date1.toStdString());
        Date d2=d.toDateString(date2.toStdString());

        if(BDOuvert==true)
        {
            QSqlQuery query;
            query.prepare("SELECT TODO.id_todo ,TODO.id_interaction,TODO.datetodo,TODO.contenu FROM TODO,INTERACTION,CONTACT WHERE "
                          "TODO.id_interaction=INTERACTION.id_interaction and "
                          "INTERACTION.id_contact=CONTACT.id_contact and "
                          "CONTACT.id_contact=:n");
            query.bindValue(":n",QString::number(id));
            query.exec();


            if(!query.exec())
            {
                qDebug()<<"probleme niveau recherche contact entre 2 date";
            }
            else
            {
                qDebug()<<"commençons la  recherche de todo du contact";

                    while(query.next())
                {
                    QString r=query.value(2).toString();
                    Date dc=d.toDateString(r.toStdString());
                    if(d1<dc && dc<d2 )
                    {
                        Todo inter;
                        r=query.value(0).toString();
                        inter.setIdTodo(r.toInt());

                        r=query.value(1).toString();

                        inter.setIdInteractionTodo(r.toInt());

                        inter.setDateTodo(dc);
                        r=query.value(3).toString();

                        inter.setContenuTodo(r.toStdString());


                        li.push_back(inter);//on insert la tache dans la liste
                    }


                }
                li.sort();//on trie la liste par date de création
            }

        }
}

void TodoBD::BDRechercheTodoCont(int &id,QString & date1 ,QString & date2,std::list<Todo> & li)
{
      RechercheTodoCont(id,date1,date2,li);
}


void TodoBD::RechercheALLTodoCont(QString & date1 ,QString & date2,std::list<Todo> & li)const
{
    li.clear();
    Date d;

    Date d1=d.toDateString(date1.toStdString());
    Date d2=d.toDateString(date2.toStdString());

    if(BDOuvert==true)
    {

        QSqlQuery  query("SELECT TODO.id_todo ,TODO.id_interaction,TODO.datetodo,TODO.contenu FROM TODO,INTERACTION,CONTACT WHERE "
                        "TODO.id_interaction=INTERACTION.id_interaction and "
                        "INTERACTION.id_contact=CONTACT.id_contact");

        if(!query.exec())
        {
            qDebug()<<"probleme niveau recherche ALLcontact entre 2 date";
        }
        else
        {
            qDebug()<<"commençons la  recherche de todo ALL contact";

                while(query.next())
            {
                QString r=query.value(2).toString();
                Date dc=d.toDateString(r.toStdString());
                if(d1<dc && dc<d2 )
                {
                    Todo inter;
                    r=query.value(0).toString();
                    inter.setIdTodo(r.toInt());

                    r=query.value(1).toString();

                    inter.setIdInteractionTodo(r.toInt());

                    inter.setDateTodo(dc);
                    r=query.value(3).toString();

                    inter.setContenuTodo(r.toStdString());


                    li.push_back(inter); //ajout dans la liste des taches le Todo .
                }


            }
            li.sort();//trier la liste des taches
        }

    }
}

void TodoBD::BDRechercheALLTodoCont(QString & date1 ,QString & date2,std::list<Todo> & li)
{
      RechercheALLTodoCont(date1,date2,li);
}

void TodoBD::isOpen(bool &b)
{
      isDBopen(b);
}

void TodoBD::closeDb()
{
        if(BDOuvert==true)
        {
            BD.close();
        }

}

void TodoBD::isDBopen(bool &b)
{
      BDOuvert=b;
}
