/*!
*\file TodoBD.h
*\author NABE Mamoudou & KEITA Sidy
*\
*/
#ifndef TODOBD_H
#define TODOBD_H

#include"Todo.h"
#include <QObject>
#include <list>
#include <QString>
#include <string>
#include <QVariant>
#include <QDate>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QtSql/QSqlQuery>

/**
 * @brief The TodoBD class
 */
class TodoBD : public QObject
{
    Q_OBJECT
private:
      QSqlDatabase BD;
      bool BDOuvert;
      bool connexion();
      void closeDb();
      void isDBopen(bool &);
      bool AjoutTodo(const int &,Todo &);
      void ListeTodoContact(const int &,std::list<Todo>&)const;
      void ListeALLContact(std::list<Todo>&) const;
      void RechercheALLTodoCont(QString &,QString &,std::list<Todo> &)const;
      void RechercheTodoCont(const int &,QString &,QString &,std::list<Todo> &)const;
public:
     explicit TodoBD(QObject *parent = nullptr);
      ~TodoBD();

public slots:
        void BDAjoutTodo(int &,Todo &);
        void BDListeTodoContact(int &,std::list<Todo>&);
        void BDListeALLContact(std::list<Todo> &);
        void BDRechercheTodoCont(int & , QString & , QString & , std::list<Todo> &);
        void BDRechercheALLTodoCont( QString & , QString & , std::list<Todo> &);
        void isOpen(bool &);

};

#endif // TODOBD_H
