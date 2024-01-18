/*!
*\file Fenetre.h
*\author NABE Mamoudou & KEITA Sidy
*\
*/

#ifndef FENETRE_H
#define FENETRE_H


#include "Todo.h"
#include "Interaction.h"
#include "Date.h"
#include <QWidget>
#include <QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QTextEdit>
#include<QLineEdit>
#include<QTimeEdit>
#include<QTimer>
#include<QDateEdit>
#include<QFormLayout>
#include<QObject>
#include<QDialog>
#include<QComboBox>
#include<QMessageBox>
#include<list>
#include<QDebug>
#include<QString>
#include<QDate>
#include<string>
#include<QTextDocument>
#include<QRegularExpression>
#include<QStringList>
#include<QTextBlock>
#include<QJsonDocument>
#include<QIODevice>
#include<QFile>
#include<QJsonObject>
#include<QJsonArray>
#include <QObject>
#include <QDebug>
#include <QMainWindow>
#include "Contact.h"
#include "ContactBD.h"
#include"InteractionBD.h"
#include <QRegExp>
#include <algorithm>  // Inclure la bibliothèque pour std::transform
#include <cctype>     // Inclure la bibliothèque pour std::tolower
#include <string>


QT_BEGIN_NAMESPACE
namespace Ui { class Fenetre; }
QT_END_NAMESPACE

class Fenetre : public QMainWindow
{
    Q_OBJECT

private:
    Ui::Fenetre *ui;
    //********************* Les boites de Dialogue *********************

    /**
     * @brief Declaration des boites de dialogue
     */
    QDialog *dialogContact;
    QDialog *dialogModification;
    QDialog *dialogRemove;
    QDialog *dialogRechercher;
    QDialog *dialogList;
    QDialog *dialogDate;
    QDialog *dialogAffichDateCont;
    QDialog *dialogTache;
    QDialog *dialogRTache;
    QDialog *dialogAllTache;
    QDialog *dialogInteraction;
    QDialog *dialogALL;
    QDialog *dialogRechercheT;
    QDialog *dialogIdeuxDates;
    QDialog  *dialogRC;


    //********************* QComboBox pour une liste deroulante d'éléments dans une interface graphique *********************
    QComboBox *comboContact;
    QComboBox *comboModif;
    QComboBox *comboInteraction;
    QComboBox *comboList;
    QComboBox *comboRecherche;
    QComboBox *comboTache;
    QComboBox *comboTachesRecherche;


    //********************* Contact *********************

    /**
     * @brief Declaration des labels pour la boite de dialogue  creer un contact
     */
    QLabel *NomC;
    QLabel *PrenomC;
    QLabel *PhotoC;
    QLabel *EntrepriseC;
    QLabel *EmailC;
    QLabel *TelephoneC;

    /**
     * @brief Declaration des QlineEdit pour Creer Contact
     */
    QLineEdit *QLineNC;
    QLineEdit *QLinePC;
    QLineEdit *QLinePhC;
    QLineEdit *QLineEnC;
    QLineEdit *QLineEmC;
    QLineEdit *QLineTelC;

    //********************* Modifier *********************

    /**
     * @brief Declaration des labels pour la boite de dialogue Modification
     */
    QLabel *NomM;
    QLabel *PrenomM;
    QLabel *PhotoM;
    QLabel *EntrepriseM;
    QLabel *EmailM;
    QLabel *TelephoneM;

    /**
     * @brief Declaration des QLineEdit pour Modifier Contact
     */
    QLineEdit *qlineNom;
    QLineEdit *qlinePrenom;
    QLineEdit *qlineEntreprise;
    QLineEdit *qlineEmail;
    QLineEdit *qlineTel;
    QLineEdit *qlinePhoto;


    QLabel *NomComboM;
    QLabel *ImageInsereC;
    QLabel *ImageInsereM;
    QLabel *NomComboList;
    QLabel *lheure;


    //************************* Recherche Contact *************************

        QLabel *NomR;/*!< chercher Contact */
        QLabel *debut;/*!< déclaration d'un QLabel */
        QLabel *fin;/*!< déclaration d'un QLabel */

        QLineEdit *nR;/*!< déclaration d'un pointeur nR de type QlineEdit pour l'insertion du texte */
        QDateEdit *date1;/*!< déclaration d'un pointeur date1 de type QDateEdit pour l'insertion de la date 1 */
        QDateEdit *date2;/*!< déclaration d'un pointeur date2 de type QDateEdit pour l'insertion de la date 2 */


        //********************* Interaction *********************

        QLabel *nomContact;/*!< décalration du QLabel pour le contact à supprimer */
        QLabel *commentaire;
        QLabel *intertext;/*!< décalration du QLabel pour le contact à une interaction */
        QLabel *intertexts;/*!< décalration du QLabel pour le contact à liste d'interaction */
        QLabel *intertextsc;/*!< décalration du QLabel pour le contact entre 2 date de son interaction */
        QLabel *NomcomboList;

        QLineEdit *cInteraction;
        QLineEdit *interactiontext;/*!< décalration du QLabel pour le contact à son nom */
        QLineEdit *nomContacts;/*!< décalration du QLabel pour le contact à son nom */
        QLineEdit *interactiontexts;/*!< décalration du QLabel pour le contact à son nom */
        QLineEdit *interactiontextsc;/*!< décalration du QLabel pour le contact à son nom */


        //********************* Date *********************

        QDateEdit *dateAjout;
        QDateEdit *dateDebutI;
        QDateEdit *dateFinI;
        QDateEdit *date1RC;
        QDateEdit *date2RC;
        QTimer *ltime;
        QDateEdit *dateDebutTaches;
        QDateEdit *dateFinTaches;
        QDateEdit *dateDebutALL;
        QDateEdit *dateFinALL;
        QTextEdit *editTaches;

        //********************* QVBoxLayout pour organiser les widgets dans une fenetre graphique  *********************


        QVBoxLayout *vAligne1;
        QVBoxLayout *vAligne2;
        QVBoxLayout *vAligne3;
        QHBoxLayout *aligneHorizontal;
        QVBoxLayout *vAligne11;
        QVBoxLayout *vAligne22;
        QVBoxLayout *vAligne33;
        QHBoxLayout *aligneHH;
        QVBoxLayout *vAligneR;
        QVBoxLayout *vAligneR2;
        QHBoxLayout *hAlignH;
        QVBoxLayout *vAligne1I;
        QVBoxLayout *vAligne2I;
        QVBoxLayout *vAligne3I;
        QHBoxLayout *hAligneI;
        QVBoxLayout *vAligneList1;
        QVBoxLayout *vAligneList2 ;
        QHBoxLayout *hAligneList;
        QVBoxLayout *vAligne1Id;
        QVBoxLayout *vAligne2Id;
        QHBoxLayout *hAligneId ;
        QVBoxLayout *vAligneRRC;
        QVBoxLayout *vAligneR2RC;
        QHBoxLayout *hAlignHRC;
        QVBoxLayout *vAligneTaches;
        QHBoxLayout *hAligne1Taches;
        QHBoxLayout *hAligne2Taches;
        QHBoxLayout *hAligne3Taches;
        QVBoxLayout *vAligne1TachesR;
        QVBoxLayout *vAligne2TachesR;
        QHBoxLayout *hAligneTachesR;
        QVBoxLayout *vAligne1AL;
        QVBoxLayout *vAligne2ALL;
        QHBoxLayout *hAligneALL;
        QHBoxLayout *hAligne1I;
        QHBoxLayout *hAligne2I;
        QHBoxLayout *hAligne4I;
        QVBoxLayout *vAligneI;
        QVBoxLayout*vAligne1ALL;

        //********************* Creation Bouttons *********************

        QPushButton *BCvalider;
        QPushButton *BCannuler;
        QPushButton *Bvalider1;
        QPushButton *Bannuler1;
        QPushButton *BRechercher;
        QPushButton *BannulerR;
        QPushButton *Bsupprimer;
        QPushButton *BPhotoContact;
        QPushButton *BPhotoModifContact;
        QPushButton *BajoutInteraction;
        QPushButton *BannulerInteraction;
        QPushButton *BvaliderListI;
        QPushButton *BannulerListI;
        QPushButton *BrechercheIdate;
        QPushButton *BannulerIdate;
        QPushButton *BRechercherRC;
        QPushButton *BannulerRC;
        QPushButton *BajoutTaches;
        QPushButton *BannulerTaches;
        QPushButton *BrechercherTaches;
        QPushButton *BannulerTachesR;
        QPushButton *BrechercherALL;
        QPushButton *BannulerALL;
        QPushButton *BAffichC;
public:
     ContactBD BD;
     InteractionBD  inBDD;
     Fenetre(QWidget *parent = nullptr);
    ~Fenetre();

private slots:

            void on_actionSupprimer_triggered();
            void on_BafficheInter_clicked();
            void actionAjoutertriggered();
            void Remplir(const QString  & );
            void on_actionChercher_un_Contact_triggered();
            void on_actionModifier_2_triggered();
            void on_actionDetails_triggered();
            void on_actionAjouterInteraction_triggered();
            void on_actionLister_Interaction_triggered();
            void on_actionTaches_pour_tous_les_contacts_triggered();
            void on_actionCollecteContact_triggered();
            void on_actionInteraction_entre_deux_Dates_triggered();
            void on_actionInter_contact_triggered();
            void on_actionJson_Contact_Interaction_triggered();
            void ListeTodos();


            void on_actionAfficher_triggered();

        public slots:
            void AjoutContact();
            void BoutonAnnulerContact();
            void afficherPhoto();
            //void JsonContact();
            void AfficheModContact();
            void afficherPhotoM();
            void BoutonAnnulerModification();
            void Heure();
            void suppressionContact();
            //void ListeTodos();
            void BoutonAnnulerSupprimer();
            void RemplirSup(const QString &);
            void RechercheUnContact();
            void BoutonAnnulerRechercher();
            void AjoutUneInteraction();
            void AnnulerInteraction();
            void  RemplirSupInter(const QString  & );
            void AnnulerListeInteraction();
            void  RemplirSupInters(const QString  & );
            void ListeInteractionContact();
            void RechercheALLTodoCont();
            //void JsonInteraction();
            void AnnulerALL();
            void BoutonAnnulerRechercherT();
            void RechercheTodoCont();
            void RechercherInteractionEntreDeuxDates();
            void AnnulerInteractionEntreDeuxDates();
            void FindContact();
            void CancelContact();
            void  RemplirSupIntersc(const QString  & );
            void TotalContact(int &);
            //void JsonExport();
             //int NbrContact() const;
            void onListeALLContact(std::list<Todo> li);

signals:

    /*!
      *\brief Les signaux pour tout ce qui concerne le contact
      *Les signaux qu'on appœelera dans les slots pour pouvoir les lier dans le main avec les fonctions correspondantes dans la base de donnée
      */
    void sigGetContactList(std::list<Contact>&);
    void sigInsert( Contact &);
    void sigSupprimer( int  &);
    void sigModifier( int & , Contact &);
    void sigRechercheUnContact(QString & , QString & ,QString & ,std::list<Contact> & );
    void sigAjoutInteraction(int &,Interaction &);
    void sigListeInteraction(int &,std::list<Interaction> &);
    void sigListeInteractionALL(std::list<Interaction> &);
    void sigRechercheInteraction(QString &,QString &,std::list<Interaction> &);
    void sigRechercheInteractionCont(int & , QString & , QString & , std::list<Interaction> &);
    void sigAjoutTodo(int &,Todo &);
    void sigListeTodoContact(int &,std::list<Todo>&);
    void sigRechercheTodoCont(int & , QString & , QString & , std::list<Todo> &);
    void sigRechercheALLTodoCont( QString & , QString & , std::list<Todo> &);
    void sigListeALLContact(std::list<Todo> &);


};
#endif // FENETRE_H
