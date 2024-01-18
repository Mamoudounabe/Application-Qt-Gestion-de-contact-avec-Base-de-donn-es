/*!
*\file main.cpp
*\author NABE Mamoudou & KEITA Sidy
*\
*/

#include"Fenetre.h"
#include<QApplication>
#include"ContactBD.h"
#include"InteractionBD.h"
#include"TodoBD.h"
#include <QApplication>

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        Fenetre w;
        ContactBD c;
        InteractionBD interact;
        TodoBD taches;


        QObject::connect(&w,SIGNAL(sigGetContactList(std::list<Contact>&)),&c,SLOT( BDListeContact(std::list<Contact> &)));

        QObject::connect(&w,SIGNAL(sigInsert( Contact &)),&c,SLOT( BDNouveauContact(Contact &)));

        QObject::connect(&w,SIGNAL(sigModifier( int & , Contact &)),&c,SLOT( BDModifContact( int & , Contact &)));

        QObject::connect(&w,SIGNAL(sigSupprimer( int &)),&c,SLOT( BDRemoveContact( int  & )));

        QObject::connect(&w,SIGNAL(sigRechercheUnContact(QString &  ,QString & ,QString & ,std::list<Contact> & )),
                         &c,SLOT(BDRechercherContact(QString &,QString & ,QString & ,std::list<Contact>&)));

        QObject::connect(&w,SIGNAL(sigAjoutInteraction(int &,Interaction &)),
                         &interact,SLOT(bddAjoutInteraction(int &,Interaction &)));

        QObject::connect(&w,SIGNAL(sigListeInteraction(int &,std::list<Interaction> &)),
                         &interact,SLOT( bddListeInteraction(int &,std::list<Interaction> &)));

        QObject::connect(&w,SIGNAL(sigListeInteractionALL(std::list<Interaction> &)),
                         &interact,SLOT( bddListeInteractionALL(std::list<Interaction> &)));

        QObject::connect(&w,SIGNAL( sigRechercheInteraction(QString &,QString &,std::list<Interaction> &)),
                         &interact,SLOT( bddRechercheInteraction(QString &,QString &,std::list<Interaction> &)));

        QObject::connect(&w,SIGNAL( sigRechercheInteractionCont(int & , QString & , QString & , std::list<Interaction> &)),
                         &interact,SLOT( bddRechercheInteractionCont(int & , QString & , QString & , std::list<Interaction> &)));


         QObject::connect(&c,SIGNAL(NbrTotalContact( int &  )),&w,SLOT(TotalContact(int &)));

         QObject::connect(&w,SIGNAL(sigAjoutTodo(int &,Todo &)),&taches,SLOT(BDAjoutTodo(int &,Todo &)));

         QObject::connect(&w,SIGNAL(sigListeALLContact(std::list<Todo> &)),&taches,SLOT(BDListeALLContact(std::list<Todo> &)));
        // std::list<Todo> li;
         //w.emit sigListeALLContact(li);
        // QObject::connect(&w, SIGNAL(sigListeALLContact(std::list<Todo>)), &w, SLOT(onListeALLContact(std::list<Todo>)));

         QObject::connect(&w,SIGNAL( sigRechercheTodoCont(int & , QString & , QString & , std::list<Todo> &)),
                        &taches,SLOT( BDRechercheTodoCont(int & , QString & , QString & , std::list<Todo> &)));

         QObject::connect(&w,SIGNAL( sigRechercheALLTodoCont( QString & , QString & , std::list<Todo> &)),
                        &taches,SLOT( BDRechercheALLTodoCont( QString & , QString & , std::list<Todo> &)));

        w.show();
        return a.exec();
}
