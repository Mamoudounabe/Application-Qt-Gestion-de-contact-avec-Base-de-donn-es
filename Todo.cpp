/*!
*\file Todo.cpp
*\author NABE Mamoudou & KEITA Sidy
*\
*/


#include"Todo.h"
#include <iostream>


Todo::Todo():date(),ContenuTodo("")
{

}

Todo::Todo(const Date &dat,const std::string & contenu):date(dat),ContenuTodo(contenu)
{

}

Date Todo::getDateTodo() const
{
      return date;
}

int Todo::getIdTodo() const
{
      return IdTodo;
}

int Todo ::getIdInteractionTodo() const
{
      return IdInter;
}


std::string Todo::getContenuTodo() const
{
     return ContenuTodo;
}

void Todo::setDateTodo(const Date &dat)
{
     date=dat;
}

void Todo::setContenuTodo(const std::string &c)
{
     ContenuTodo=c;
}

void Todo::setIdTodo(const int & v)
{
     IdTodo=v;
}

void Todo::setIdInteractionTodo(const int & v)
{
     IdInter=v;
}

bool Todo::operator<(const Todo &o) const
{
        if(this->getDateTodo() < o.getDateTodo())
        {
            return true;
        }
        else
        {
            return false;
        }
}

std::ostream& operator<<(std::ostream &os,const Todo &todo)
    {
        //os<<"@todo "<<todo.getContenuTodo()<<"@date "<<todo.getDateTodo()<<"";
      os << "@todo " << todo.getContenuTodo() << " @date " << todo.getDateTodo();
        return os;
}
