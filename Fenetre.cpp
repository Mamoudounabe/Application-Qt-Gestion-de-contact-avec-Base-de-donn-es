/*!
*\file Fenetre.cpp
*\author NABE Mamoudou & KEITA Sidy
*\
*/

#include "Fenetre.h"
#include "ui_Fenetre.h"
#include<QFileDialog>
#include "ContactBD.h"
#include"InteractionBD.h"


Fenetre::Fenetre(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Fenetre)
{
    ui->setupUi(this);

     comboContact= new QComboBox();
     comboModif=new QComboBox();
     comboInteraction=new QComboBox();
     comboList=new class QComboBox();
     comboRecherche=new QComboBox();
     comboTache=new QComboBox();
     comboTachesRecherche=new QComboBox();


qDebug() << " 1 Action 'Ajouter '' déclenchée.";
    connect(ui->bajoute,SIGNAL(triggered()),this,SLOT(actionAjoutertriggered()));
connect(ui->BoutonModif,SIGNAL(triggered()),this,SLOT(on_actionModifier_2_triggered()));
    connect(ui->BSupprimer,SIGNAL(triggered()),this,SLOT(on_actionSupprimer_triggered()));
    connect( ui->actionDetails,SIGNAL(triggered()),this,SLOT(on_actionDetails_triggered()));
    ltime=new QTimer(this);//Déclaration de ltime on l'initialise à this .
    connect(ltime,SIGNAL(timeout()),this,SLOT(Heure()));
    ltime->start(1000);//à chaque 1000 milliseconde la seconde s'incrémente .
    connect(ui->B_Rechercher,SIGNAL(triggered()),this,SLOT(on_actionChercher_un_Contact_triggered()));
    connect(ui->actionAjouter_Interaction,SIGNAL(triggered()),this,SLOT(on_actionAjouterInteraction_triggered()));
    connect(ui->actionListerInteraction,SIGNAL(triggered()),this,SLOT(on_actionLister_Interaction_triggered()));
    connect(ui->actionTaches_Taches,SIGNAL(triggered()),this,SLOT(on_actionTaches_pour_tous_les_contacts_triggered()));
    connect(ui->actionAffiches_Taches,SIGNAL(triggered()),this,SLOT(ListeTodos()));
    connect(ui->action_Collecte_Contact,SIGNAL(triggered()),this,SLOT(on_actionCollecteContact_triggered()));
    connect(ui->actInteraction_2_Dates,SIGNAL(triggered()),this,SLOT(on_actionInteraction_entre_deux_Dates_triggered()));
    connect(ui->actionInter_contact,SIGNAL(trigerred()),this,SLOT());


    connect(ui->actionAfficher,SIGNAL(triggered()),this,SLOT(on_actionAfficher_triggered()));
    /**
     * @details : consigne du prof "Affichage automatique de la lise des contacts sans appuie d'un bouton
     */

     /*       on_BafficheC_clicked();
            QTimer *timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(on_BafficheC_clicked()));
            timer->start(1000);  // Appelle on_BafficheC_clicked toutes les 1000 millisecondes (1 seconde)

    //timer->start(10000);*/





 /**
      * @detais Association des deux Json(Contact && Interaction)
      */
     connect(ui->actionJson_Contact_Interaction,SIGNAL(triggered()),this,SLOT(on_BafficheInter_clicked()));


}




Fenetre::~Fenetre()
{
    delete ui;
}


void Fenetre::Heure()
{
    QTime timeValue;
    timeValue=QTime::currentTime();
    QString format=" H:m:s";
    ui->heure->setText(timeValue.toString(format));

}


void Fenetre::actionAjoutertriggered()
{

    qDebug() << " 2 Action 'Ajouter' déclenchée.";
    dialogContact=new QDialog(this);
    dialogContact->setWindowTitle("Ajouter un contact ");
    dialogContact->resize(400,10);
    dialogContact->setModal(true);

    NomC=new QLabel(" Nom ");
    PrenomC = new QLabel(" Prenom ");
    PhotoC= new QLabel(" Ajouter une photo ");
    ImageInsereC=new QLabel(" Ma photo ");
    EntrepriseC  = new QLabel(" Entreprise ");
    EmailC = new QLabel(" Email ");
    TelephoneC = new QLabel(" Telephone ");
    /*Les textes*/
    QLineNC=new QLineEdit();
    QLinePC=new QLineEdit();
    QLineEnC=new QLineEdit();
    QLineEmC=new QLineEdit();
    QLineTelC=new QLineEdit();
    QLinePhC=new QLineEdit();

    /****Dimension****/
    // pour la disposition
    vAligne1=new QVBoxLayout();
    vAligne2=new QVBoxLayout();
    vAligne3=new QVBoxLayout();
    aligneHorizontal=new QHBoxLayout();

    BCvalider= new QPushButton("Valider");
    BCannuler= new QPushButton("Annuler");
    BPhotoContact= new QPushButton("Parcourir");
    vAligne1->addWidget(NomC);
    vAligne1->addWidget(PrenomC);
    vAligne1->addWidget(EntrepriseC);
    vAligne1->addWidget(EmailC);
    vAligne1->addWidget(TelephoneC);
    vAligne1->addWidget(PhotoC);
    vAligne1->addWidget(BCannuler);
    aligneHorizontal->addLayout(vAligne1);

    vAligne2->addWidget(QLineNC);
    vAligne2->addWidget(QLinePC);
    vAligne2->addWidget(QLineEnC);
    vAligne2->addWidget(QLineEmC);
    vAligne2->addWidget(QLineTelC);
    vAligne2->addWidget(BPhotoContact);
    vAligne2->addWidget(BCvalider);
    aligneHorizontal->addLayout(vAligne2);

    vAligne3->addWidget(ImageInsereC);
    aligneHorizontal->addLayout(vAligne3);//ajout vAligne1 en dimension horizontale

    dialogContact->setLayout(aligneHorizontal);
    dialogContact->show();



    connect(BCvalider,SIGNAL(clicked()),this,SLOT(AjoutContact()));
    connect(BPhotoContact,SIGNAL(clicked()),this,SLOT(afficherPhoto()));
    connect(BCannuler,SIGNAL(clicked()),this,SLOT(BoutonAnnulerContact()));
}
void Fenetre:: AjoutContact()
{
    qDebug() << " 3 Action 'Ajouter' déclenchée.";
    Contact c;
    if (QLineNC->text() != nullptr && QLinePC->text() != nullptr &&
        QLineEnC->text() != nullptr && QLineEmC->text() != nullptr && QLineTelC->text() != nullptr)
    {
        c.setNom(QLineNC->text().toStdString());
        c.setPrenom(QLinePC->text().toStdString());
        c.setEmtreprise(QLineEnC->text().toStdString());
        c.setMail(QLineEmC->text().toStdString());
        c.setTel(QLineTelC->text().toStdString());
        c.setPhoto(QLinePhC->text().toStdString());


       emit sigInsert(c);/*!< signal qu'on envoie vers le main qu'on recupera afin de faire les connections avec la BD*/
        std::list<Contact> lp;
       ui->afficherTexte->clear();
        lp.clear();
        emit sigGetContactList(lp);


        QMessageBox::information(this,"Création d'un contact "," Contact créé avec succés !!!!" );
        comboInteraction->clear();//Raffraichier la combo lors de la création d'un contact
        comboTachesRecherche->clear();//Raffraichier la combo lors de la création d'un contact
        comboRecherche->clear();//raffraichir la combo lors de la création d'un contact .
        comboContact->clear();//raffraichir la combo
        comboList->clear();//raffraichir la combo
        comboModif->clear();//raffraichir la combo

        dialogContact->close();
    }

    else
    {
        QMessageBox::warning(this,"Création d'un contact "," Remplissez toutes les cases  !!!" );

    }

}

 void Fenetre::BoutonAnnulerContact()
{
      dialogContact->close();
 }


void Fenetre::on_actionAfficher_triggered()
{

        std::list<Contact> lp;

        ui->afficherTexte->clear();//raffraichier le textEdit
        comboContact->clear();//raffraichir la combo
        comboModif->clear();//raffraichir la combo
        comboInteraction->clear();//raffraichir la combo
        comboList->clear();//raffraichir la combo
        comboRecherche->clear();//raffraichir la combo
        comboTache->clear();//raffraichir la combo
        comboTachesRecherche->clear();//Raffraichier la combo pour la recherche d'une tache d'un contact .

        emit sigGetContactList(lp);//envoi du signal qu'on liera dans le main avec la BD

        QString texte;

        QString vu;
        vu+="  idContact\t|";
        vu+="  Nom\t|";
        vu+="  Prenom\t|";
        vu+="  Entreprise\t|";
        vu+="  Email\t|";
        vu+="  Photo\t|";
        vu+="  Telephone\t|";
        vu+="  Date \t\n\n";
        ui->afficherTexte->insertPlainText(vu);
        for(auto &p:lp)
        {   texte+=QString::number(p.getIdContact())+ "\t";
            texte+=QString::fromStdString(p.getNom())+ " \t";
            texte+=QString::fromStdString(p.getPrenom())+ "\t";
            texte+=QString::fromStdString(p.getEntreprise())+ "\t";
            texte+=QString::fromStdString(p.getMail())+ " \t";
            texte+=QString::fromStdString(p.getPhoto())+ "\t";
            texte+=QString::fromStdString(p.getTel())+ "\t";
            texte+=QString::fromStdString(p.getDateDecreation().fromDateString())+ "\n";

            //actualiser les comboBoxs dans l'application
            comboContact->addItem(QString::number(p.getIdContact()));
            comboModif->addItem(QString::number(p.getIdContact()));
            comboList->addItem(QString::number(p.getIdContact()));
            comboRecherche->addItem(QString::number(p.getIdContact()));
            comboInteraction->addItem(QString::number(p.getIdContact()));
            comboTachesRecherche->addItem(QString::number(p.getIdContact()));


        }

        ui->afficherTexte->insertPlainText(texte);//insertion sur le textedit le QString afin de faire l'affichage
   }


void Fenetre::afficherPhoto()
{
        int w = ImageInsereC->width();
        int h = ImageInsereC->height();

        QString dir = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier "),QString(),
                                                   "Images (*.png *.gif *.jpg *.jpeg *.bmp)");
        ImageInsereC->setPixmap(QPixmap(dir).scaled(w,h,Qt::KeepAspectRatio));
        QLinePhC->setText(dir);

 }

void Fenetre::on_actionModifier_2_triggered()
{
        dialogModification=new QDialog();
        dialogModification->setWindowTitle(tr("Modifier Contact"));
        dialogModification->resize(400,10);
        dialogModification->setModal(true);


        NomComboM=new QLabel("Liste contact ");
        NomM=new QLabel("Nom");
        PrenomM=new QLabel(" Prenom ");
        PhotoM=new QLabel(" Ajouter une Photo ");
        ImageInsereM=new QLabel("MA PHOTO");
        EntrepriseM=new QLabel(" Entreprise ");
        EmailM=new QLabel(" Email ");
        TelephoneM = new QLabel(" Telephone ");

        //les champs de texte
        qlineNom=new QLineEdit();
        qlinePrenom=new QLineEdit();
        qlineEntreprise=new QLineEdit();
        qlineEmail=new QLineEdit();
        qlineTel=new QLineEdit();
        qlinePhoto=new QLineEdit();

        /*****bouton valider et annuler****/
        Bvalider1= new QPushButton("Valider");
        Bannuler1= new QPushButton("Annuler");
        BPhotoModifContact= new QPushButton("Parcourir");
        /***** disposition**********/
        vAligne11=new QVBoxLayout();
        vAligne22=new QVBoxLayout();
        vAligne33=new QVBoxLayout();
        aligneHH=new QHBoxLayout();


        /****création et ajout des widget***********/
    vAligne11->addWidget(NomComboM);
    vAligne11->addWidget(NomM);
    vAligne11->addWidget(PrenomM);
    vAligne11->addWidget(EntrepriseM);
    vAligne11->addWidget(EmailM);
    vAligne11->addWidget(TelephoneM);
    vAligne11->addWidget(PhotoM);
    vAligne11->addWidget(Bannuler1);
    aligneHH->addLayout(vAligne11);

    vAligne22->addWidget(comboContact);
    vAligne22->addWidget(qlineNom);
    vAligne22->addWidget(qlinePrenom);
    vAligne22->addWidget(qlineEntreprise);
    vAligne22->addWidget(qlineEmail);
    vAligne22->addWidget(qlineTel);
    vAligne22->addWidget(BPhotoModifContact);
    vAligne22->addWidget(Bvalider1);
    aligneHH->addLayout(vAligne22);

    vAligne33->addWidget(ImageInsereM);
    aligneHH->addLayout(vAligne33);


    dialogModification->setLayout(aligneHH);
    dialogModification->show();
    connect(Bvalider1,SIGNAL(clicked()),this,SLOT(AfficheModContact()));
    connect(BPhotoModifContact,SIGNAL(clicked()),this,SLOT(afficherPhotoM()));
    connect(Bannuler1,SIGNAL(clicked()),this,SLOT(BoutonAnnulerModification()));
    connect(comboContact,SIGNAL(currentTextChanged(const QString  & )),this,SLOT(Remplir(const QString  & )));


}

void Fenetre::afficherPhotoM()
{
    int w = ImageInsereM->width();
    int h = ImageInsereM->height();

    QString photo = QFileDialog::getOpenFileName(this, tr("Ouvrir un fichier "),QString(),
                                                 "Images (*.png *.gif *.jpg *.jpeg *.bmp)");
    ImageInsereM->setPixmap(QPixmap(photo).scaled(w,h,Qt::KeepAspectRatio));
    qlinePhoto->setText(photo);
}



void Fenetre:: Remplir(const QString  & valeur)
{

    std::list<Contact> lp;
    lp.clear();
    emit sigGetContactList(lp);
    qDebug() <<"debut rempli";
    //int val = valeur.trimmed().toInt();
    int val=valeur.toInt();
     qDebug() << "Taille de la liste des contacts : " << val;

    qDebug() << "Taille de la liste des contacts : " << lp.size();
    for(auto &p:lp)
    {
            if(p.getIdContact()==val)
            {
                qDebug()<<"affiche remplir ok";
                qlineNom->setText(QString::fromStdString(p.getNom()));
                qlinePrenom->setText(QString::fromStdString(p.getPrenom()));
                qlineEntreprise->setText(QString::fromStdString(p.getEntreprise()));
                qlineEmail->setText(QString::fromStdString(p.getMail()));
                qlineTel->setText(QString::fromStdString(p.getTel()));
                qlinePhoto->setText(QString::fromStdString(p.getPhoto()));

            }
    }

    qDebug()<<"affiche remplir";
}


void Fenetre::BoutonAnnulerModification()
{
    dialogModification->close();
}

void Fenetre:: AfficheModContact()
{

    Contact  c2;
    if(qlineNom->text()!=NULL && qlinePrenom->text()!=NULL && qlineEntreprise->text()!=NULL &&
        qlineEmail->text()!=NULL && qlineTel->text()!=NULL)
    {
            ui->afficherTexte->clear();
            c2.setNom(qlineNom->text().toStdString());
            c2.setPrenom(qlinePrenom->text().toStdString());
            c2.setEmtreprise(qlineEntreprise->text().toStdString());
            c2.setMail(qlineEmail->text().toStdString());
            c2.setTel(qlineTel->text().toStdString());
            c2.setPhoto(qlinePhoto->text().toStdString());

            QString t=comboContact->currentText();
            int  c=t.toInt();

            emit sigModifier(c,c2);
            std::list<Contact> lp;
            lp.clear();
            emit sigGetContactList(lp);
            comboContact->clear();
            comboInteraction->clear();
            comboModif->clear();

            QString texte;
            QString vu;
            vu+="idContact \t | ";
            vu+=" Nom \t | ";
            vu+=" Prenom \t | ";
            vu+="Entreprise \t | ";
            vu+=" Email \t | ";
            vu+=" Photo \t | ";
            vu+=" Telephone \t | ";
            vu+=" Date \n\n";
            ui->afficherTexte->insertPlainText(vu);
            for(auto &p:lp)
            {
                texte+=QString::number(p.getIdContact())+ "\t";
                texte+=QString::fromStdString(p.getNom())+ "\t";
                texte+=QString::fromStdString(p.getPrenom())+ "\t";
                texte+=QString::fromStdString(p.getEntreprise())+ "\t";
                texte+=QString::fromStdString(p.getMail())+ "\t";
                texte+=QString::fromStdString(p.getPhoto())+ "\t";
                texte+=QString::fromStdString(p.getTel())+ "\t";
                texte+=QString::fromStdString(p.getDateDecreation().fromDateString())+ "\n";
                comboContact->addItem(QString::number(p.getIdContact()));
                comboModif->addItem(QString::number(p.getIdContact()));
                comboInteraction->addItem(QString::number(p.getIdContact()));


            }


            ui->afficherTexte->insertPlainText(texte);
            dialogModification->close();

    }
    else

    {
            QMessageBox::warning(this,"Modification d'un contact "," Remplissez toutes les cases  !!!" );

    }

}


void Fenetre::on_actionSupprimer_triggered()
{

    dialogRemove=new QDialog(this);
    dialogRemove->setWindowTitle(tr("Suppression Contact"));
    dialogRemove->setModal(true);




    Bsupprimer= new QPushButton("Supprimer");
    QPushButton *Bannuler= new QPushButton("Annuler");

    /****Dimension****/
    QVBoxLayout *vAligne1=new QVBoxLayout();
    QVBoxLayout *vAligne2=new QVBoxLayout();
    QHBoxLayout *hAligne=new QHBoxLayout();

    QLabel *Ncontact=new QLabel(" Indice Contact ");
    QLabel      *nomContact=new QLabel("Nom/Prenom");
    nomContacts=new QLineEdit();
    vAligne1->addWidget(Ncontact);
    vAligne1->addWidget(nomContact);
    vAligne1->addWidget(Bannuler);

    hAligne->addLayout(vAligne1);

    vAligne2->addWidget(comboModif);
    vAligne2->addWidget(nomContacts);
    vAligne2->addWidget(Bsupprimer);

    hAligne->addLayout(vAligne2);

    dialogRemove->setLayout(hAligne);
    dialogRemove->show();

    connect(Bsupprimer,SIGNAL(clicked()),this,SLOT(suppressionContact()));
    connect(Bannuler,SIGNAL(clicked()),this,SLOT(BoutonAnnulerSupprimer()));
    connect(comboModif,SIGNAL(currentTextChanged(const QString  & )),this,SLOT(RemplirSup(const QString  & )));/*!< la connection de la combo au IHM lorsque l'on appui sur la Combo box */


}

void Fenetre::BoutonAnnulerSupprimer()
{
    dialogRemove->close();
}

void Fenetre::RemplirSup(const QString  & valeur )
{
    std::list<Contact> lp;
    lp.clear();
    emit sigGetContactList(lp);
    int val=valeur.toInt();
    for(auto &p:lp)
    {
            if(p.getIdContact()==val)
            {
                nomContacts->setText(QString::fromStdString(p.getNom())+"  "+QString::fromStdString(p.getPrenom()));
                qDebug()<<QString::fromStdString(p.getNom());
            }
    }
}


void Fenetre ::suppressionContact()
{

    ui->afficherTexte->clear();
    QString t=comboModif->currentText();

    if(t!=NULL)
    {
            int  c=t.toInt();
            qDebug()<<" "+ QString::number(c);
            emit sigSupprimer(c);
            std::list<Contact> lp;
            lp.clear();
            emit sigGetContactList(lp);
            comboModif->clear();
            comboContact->clear();
            comboInteraction->clear();
            comboList->clear();
            comboRecherche->clear();
            comboTachesRecherche->clear();
            comboTache->clear();
            QString vu;
            vu+="\tidContact \t | ";
            vu+=" \tNom \t  | ";
            vu+="\t Prenom \t | ";
            vu+="\tEntreprise\t| ";
            vu+=" \tEmail \t | ";
            vu+="\t Photo \t | ";
            vu+=" \tTelephone \t | ";
            vu+="\t Date \n\n";
            ui->afficherTexte->insertPlainText(vu);

            QString texte;
            for(auto &p:lp)
            {
                texte+=QString::number(p.getIdContact())+ "\t";
                texte+=QString::fromStdString(p.getNom())+ "\t";
                texte+=QString::fromStdString(p.getPrenom())+ "\t";
                texte+=QString::fromStdString(p.getEntreprise())+ "\t";
                texte+=QString::fromStdString(p.getMail())+ "\t\t";
                texte+=QString::fromStdString(p.getPhoto())+ "\t\t";
                texte+=QString::fromStdString(p.getTel())+ "\t";
                texte+=QString::fromStdString(p.getDateDecreation().fromDateString())+ "\n";
                //Actualiser les comboBoxs
                comboModif->addItem(QString::number(p.getIdContact()));
                comboContact->addItem(QString::number(p.getIdContact()));
                comboInteraction->addItem(QString::number(p.getIdContact()));
                comboList->addItem(QString::number(p.getIdContact()));
                comboRecherche->addItem(QString::number(p.getIdContact()));
                comboTachesRecherche->addItem(QString::number(p.getIdContact()));
                comboTache->addItem(QString::number(p.getIdContact()));
            }
            ui->afficherTexte->insertPlainText(texte);
            on_BafficheInter_clicked();/*!< appel de la fonction pour actualiser l'affichage de toutes les intéractions aprés suppression .*/
            ListeTodos();/*!< appel de la fonction pour actualiser l'affichage des listes de taches à faire aprés suppression*/
    }
    else
    {
            QMessageBox::warning(this,"Suppression Contact","Impossible de faire la suppression sans\n"
                                                              "voir la liste des contacts ");
    }
    dialogRemove->close();
}


void Fenetre :: on_BafficheInter_clicked()
{
    ui->textEditInteraction->clear();
    std::list<Interaction> li;
    li.clear();

    comboTache->clear();
    sigListeInteractionALL(li);
    QString texte;
    QString inter;

    inter+="idContact  | ";
    inter+="idInteract | ";

    inter+="dateInter |   ";
    inter+=" Contenu  |\n\n ";


    ui->textEditInteraction->insertPlainText(inter);
    for(auto &p:li)
    {

            texte+=QString::number(p.getIdInteractionInter())+ " \t| ";
            texte+=QString::number(p.getIdContactInter())+ " \t| ";
            texte+=QString::fromStdString(p.getRDV().fromDateString())+ " \t| ";
            texte+=QString::fromStdString(p.getContenu())+" \t \n";

            comboTache->addItem(QString::number(p.getIdContactInter()));

    }
    ListeTodos();
    ui->textEditInteraction->insertPlainText(texte);

}




void Fenetre::on_actionDetails_triggered()
{
   QMessageBox::information(this, "Apropos de notre Projet CDAA",
                            " On a developpé cette applilcation QT (c++) en faisant \n"
                            "  dialoguer l'application et une base de donnée SQL .\n"
                            " Ce projet est fait  par  \n"
                            "NABE Mamoudou  \n"
                            "& KEITA sidy\n"
                            "  \n"
                            "de l'equipe  MM !\n"
                            "Professeur: Monsieur Raffin Romain "
                            "\t\t Année:2023-2024 \n\n");


}



void Fenetre::on_actionChercher_un_Contact_triggered()
{
   dialogRechercher=new QDialog(this);
   dialogRechercher->setWindowTitle(tr("Rechercher un contact "));
   dialogRechercher->setModal(true);


   //nom debut nR date1 dateAjout dateDebutI
   NomR=new QLabel(" Nom");
   //label date debut
   debut=new QLabel("Date début");
       //label date fin
       fin=new QLabel("Date de fin ");

   //champs de texte
   nR=new QLineEdit();
   date1= new QDateEdit();
   date2= new QDateEdit();

   /****Dimension****/
vAligneR=new QVBoxLayout();
vAligneR2=new QVBoxLayout();
hAlignH=new QHBoxLayout();

//Bouton
BRechercher= new QPushButton("Rechercher");
BannulerR= new QPushButton("Annuler");
vAligneR->addWidget(NomR);
vAligneR->addWidget(debut);
   vAligneR->addWidget(fin);
   vAligneR->addWidget(BannulerR);
   hAlignH->addLayout(vAligneR);


   vAligneR2->addWidget(nR);
   vAligneR2->addWidget(date1);
   vAligneR2->addWidget(date2);
   vAligneR2->addWidget(BRechercher);
   hAlignH->addLayout(vAligneR2);

   dialogRechercher->setLayout(hAlignH);

   dialogRechercher->show();

   connect(BRechercher,SIGNAL(clicked()),this,SLOT(RechercheUnContact()));
   connect(BannulerR,SIGNAL(clicked()),this,SLOT(BoutonAnnulerRechercher()));

}

void Fenetre::RechercheUnContact()
{
   std::list<Contact> lp;
   ui->afficherTexte->clear();//Pour raffraichir l'affichage sur la base de donnée
   QString date01="";
   QString date02="";
   QString sep="-";

   QString tr=date1->text();
   date01=(((date01.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

   tr=date2->text();
   date02=(((date02.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

   tr=nR->text();
   emit sigRechercheUnContact(tr,date01,date02,lp);

   QString texte;
   QString vu;
   vu+="idContact \t | ";
   vu+=" Nom \t | ";
   vu+=" Prenom \t | ";
   vu+="Entreprise \t | ";
   vu+=" Email \t | ";
   vu+=" Photo \t | ";
   vu+=" Telephone \t | ";
   vu+=" Date \n\n";
   ui->afficherTexte->insertPlainText(vu);
   for(auto &p:lp)
   {
            texte+=QString::number(p.getIdContact())+ "\t";
            texte+=QString::fromStdString(p.getNom())+ "\t";
            texte+=QString::fromStdString(p.getPrenom())+ "\t";
            texte+=QString::fromStdString(p.getEntreprise())+ "\t";
            texte+=QString::fromStdString(p.getMail())+ "\t";
            texte+=QString::fromStdString(p.getPhoto())+ "\t";
            texte+=QString::fromStdString(p.getTel())+ "\t";
            texte+=QString::fromStdString(p.getDateDecreation().fromDateString())+ "\n";
   }

   ui->afficherTexte->insertPlainText(texte);
   dialogRechercher->close();
}

void Fenetre::BoutonAnnulerRechercher()
{
   dialogRechercher->close();
}
void Fenetre::AjoutUneInteraction()
{
   Interaction interaction;
   QString t=comboInteraction->currentText();

   if(t!=NULL)
   {

            int  c1=t.toInt();
            interaction.setContenu(cInteraction->text().toStdString());
            interaction.setIdContactInter(c1);
            emit  sigAjoutInteraction(c1,interaction);
            QTextDocument * qdoc=editTaches->document();
            QTextCursor c(qdoc);
            QTextDocument::FindFlag  fcs=(QTextDocument::FindFlag) 0;
            QStringList ltodos;
            while(!c.isNull())
            {
                QRegularExpression qreg("^@todo .*$");
                c=qdoc->find(qreg, c.position(),fcs);
                if(!c.isNull())
                {
                    QTextBlock qtb = c.block ();
                    ltodos.append(qtb.text());
                }

            }

            int position;
            QString contenu;
            int  ci=t.toInt();
            for(auto& s:ltodos)
            {
                Todo in;

                in.setIdInteractionTodo(ci);
                position=s.toStdString().find("@date");
                if(position>0)
                {
                    QString date=s.mid(position+6,s.size());
                    std::string tmp(date.toStdString());
                    tmp.erase(std::remove(tmp.begin(), tmp.end(), ' '), tmp.end());
                    QString date1="";
                    QString sep="-";
                    date=QString::fromStdString(tmp);
                    date1=(((date1.append(date.mid(6,4)).append(sep)).append(date.mid(3,2)).append(sep)).append(date.mid(0,2)));
                    contenu=s.mid(6,position-6);
                    in.setContenuTodo(contenu.toStdString());
                    in.setDateTodo(in.getDateTodo().toDateString(date1.toStdString()));

                }
                else
                {
                    contenu=s.mid(6,s.size());
                    contenu+= " à faire maintenant";

                               in.setContenuTodo(contenu.toStdString());

                }
                emit  sigAjoutTodo(ci,in);
            }





            QMessageBox msgBox;
            msgBox.setText("L'intéraction  a été ajouté avec succés sur le  contact qui a pour identifiant "
                           +QString::number(interaction.getIdContactInter()));
            msgBox.exec();




   }
   else
   {
            QMessageBox::warning(this,"Ajouter une intéraction ","Impossible d'ajouter une intéraction sans voir la liste des contacts \n"
                                                                   "ou sans entrer un contenu \n"
                                                                   "veuillez afficher les contacts sur la fenetre principale avant ." );
   }
   comboTache->clear();
   ui->textEditInteraction->clear();
   dialogInteraction->close();
}

void Fenetre::AnnulerInteraction()
{
   dialogInteraction->close();
}

void Fenetre::RemplirSupInter(const QString  & valeur )
{
   std::list<Contact> lp;
   lp.clear();
   emit sigGetContactList(lp);
   int val=valeur.toInt();
   for(auto &p:lp)
   {
            if(p.getIdContact()==val)
            {
                interactiontext->setText(QString::fromStdString(p.getNom())+"  "+QString::fromStdString(p.getPrenom()));

            }
   }
}

void Fenetre::on_actionAjouterInteraction_triggered()
{
   dialogInteraction=new QDialog(this);
   dialogInteraction->setWindowTitle(tr("Ajout Intéraction "));
   dialogInteraction->resize(300,1);
   dialogInteraction->setModal(true);


   //Prenom
   commentaire=new QLabel("Commentaire");
   cInteraction=new QLineEdit();

   QLabel *NomContact=new QLabel("Indice Contact ");

   BajoutInteraction= new QPushButton("Ajout Interaction");
   BannulerInteraction= new QPushButton("Annuler");

   //champ de texte
   editTaches=new QTextEdit();


   /****Dimension****/
   hAligne1I=new QHBoxLayout();
   hAligneI=new QHBoxLayout();
   hAligneI=new QHBoxLayout();
   hAligne2I=new QHBoxLayout();
   hAligne4I=new QHBoxLayout();
   vAligneI=new QVBoxLayout(this);
   intertext=new QLabel("nom/Prenom");
   interactiontext=new QLineEdit();


   hAligne1I->addWidget(NomContact);

   hAligne1I->addWidget(comboInteraction);
   hAligne1I->addWidget(intertext);
   vAligneI->addLayout(hAligne1I);



   hAligne2I->addWidget(commentaire);
   hAligne2I->addWidget(cInteraction);
   hAligne2I->addWidget(interactiontext);

   vAligneI->addLayout(hAligne2I);

   hAligneI->addWidget(editTaches);
   vAligneI->addLayout(hAligneI);



   hAligne4I->addWidget(BajoutInteraction);
   hAligne4I->addWidget(BannulerInteraction);
   vAligneI->addLayout(hAligne4I);


   dialogInteraction->setLayout(vAligneI);
   dialogInteraction->show();

   connect(BajoutInteraction,SIGNAL(clicked()),this,SLOT(AjoutUneInteraction()));/*!< connection du bouton BajoutInteraction de l'application au slot AjoutUneInteraction*/
   connect(BannulerInteraction,SIGNAL(clicked()),this,SLOT(AnnulerInteraction()));/*!< la connection pour le bouton annuler pour fermet la fenetre */
   connect(comboInteraction,SIGNAL(currentTextChanged(const QString  & )),this,SLOT(RemplirSupInter(const QString  & )));/*!< la connection de la combo au IHM lorsque l'on appui sur la Combo box */

}


void Fenetre::AnnulerListeInteraction()
{
   dialogList->close();
}


void Fenetre::RemplirSupInters(const QString  & valeur )
{
   std::list<Contact> lp;
   lp.clear();
   emit sigGetContactList(lp);
   int val=valeur.toInt();
   for(auto &p:lp)
   {
            if(p.getIdContact()==val)
            {
                interactiontexts->setText(QString::fromStdString(p.getNom())+"  "+QString::fromStdString(p.getPrenom()));

            }
   }
}

void Fenetre::ListeInteractionContact()
{

   ui->textEditInteraction->clear();
   QString t=comboList->currentText();
   int  c=t.toInt();

   if(t!=NULL)
   {
            std::list<Interaction> li;
            li.clear();
            emit sigListeInteraction(c,li);
            QString texte;

            QString inter;
            inter+="idInteract |   ";
            inter+="idContact  |   ";
            inter+="dateInter  |\t  ";
            inter+=" Contenu \n\n";
            ui->textEditInteraction->insertPlainText(inter);
            for(auto &p:li)
            {
                texte+=QString::number(p.getIdInteractionInter())+ "\t";
                texte+=QString::number(p.getIdContactInter())+"\t";
                texte+=QString::fromStdString(p.getRDV().fromDateString())+ "\t";
                texte+=QString::fromStdString(p.getContenu())+"\n";
            }
            ui->textEditInteraction->insertPlainText(texte); /*!< insertion de l'affichage sur le textEdit dedié .*/
              }
    else
      {
        QMessageBox::warning(this,"Liste intéractions","Impossible d'afficher les intéractions d'un contact sans connaitre le contact ! \n"
                                       "veuillez afficher la liste des contacts sur la fenetre principale avant");
      }

     dialogList->close();

}


void Fenetre::on_actionLister_Interaction_triggered()
{
   dialogList=new QDialog(this);
   dialogList->setWindowTitle(tr("Liste des Interactions "));
   dialogList->setModal(true);

   vAligneList1=new QVBoxLayout(this);
   vAligneList2=new QVBoxLayout(this);
   hAligneList=new QHBoxLayout();

   //Bouton
   BvaliderListI= new QPushButton("valider");
   BannulerListI= new QPushButton("Annuler");
   NomcomboList=new QLabel(" Liste des Conctact ");
   intertexts=new QLabel("nom/Prenom");
   interactiontexts=new QLineEdit();

   vAligneList1->addWidget(NomcomboList);
   vAligneList1->addWidget(intertexts);

   vAligneList1->addWidget(BannulerListI);
   hAligneList->addLayout(vAligneList1);

   vAligneList2->addWidget(comboList);
   vAligneList2->addWidget(interactiontexts);

   vAligneList2->addWidget(BvaliderListI);
   hAligneList->addLayout(vAligneList2);

   dialogList->setLayout(hAligneList);
   dialogList->show();

   connect(BvaliderListI,SIGNAL(clicked()),this,SLOT(ListeInteractionContact()));
   connect(BannulerListI,SIGNAL(clicked()),this,SLOT(AnnulerListeInteraction()));
   connect(comboList,SIGNAL(currentTextChanged(const QString  & )),this,SLOT(RemplirSupInters(const QString  & )));

}



void Fenetre::on_actionTaches_pour_tous_les_contacts_triggered()
{
   dialogALL=new QDialog(this);
   dialogALL->setWindowTitle(tr("Listes des taches de tous les contacts entre deux dates "));
   dialogALL->resize(450,1);
   dialogALL->setModal(true);

   //Bouton
   BrechercherALL= new QPushButton("Recherche");
   BannulerALL= new QPushButton("Annuler");

   //nom et date deubt
   QLabel *NomdateDebutALL=new QLabel("Date debut ");
   dateDebutALL=new QDateEdit();


   //nom et date fin
   QLabel *NomdateFinALL=new QLabel("Date Fin ");
   dateFinALL=new QDateEdit();


   vAligne1ALL=new QVBoxLayout();
   vAligne2ALL=new QVBoxLayout();
   hAligneALL=new QHBoxLayout();


   vAligne1ALL->addWidget(NomdateDebutALL);
   vAligne1ALL->addWidget(NomdateFinALL);
   vAligne1ALL->addWidget(BannulerALL);
   hAligneALL->addLayout(vAligne1ALL);

   vAligne2ALL->addWidget(dateDebutALL);
   vAligne2ALL->addWidget(dateFinALL);
   vAligne2ALL->addWidget(BrechercherALL);
   hAligneALL->addLayout(vAligne2ALL);


   dialogALL->setLayout(hAligneALL);

   dialogALL->show();

   connect(BrechercherALL,SIGNAL(clicked()),this,SLOT(RechercheALLTodoCont()));
   connect(BannulerALL,SIGNAL(clicked()),this,SLOT(AnnulerALL()));


}

void Fenetre::AnnulerALL()
{
   dialogALL->close();
}


void Fenetre::RechercheALLTodoCont()
{
   std::list<Todo> li;
   li.clear();
   ui->plainTextEditTodo->clear();
   QString date1="";
   QString date2="";
   QString sep="-";

   QString tr=dateDebutALL->text();
   date1=(((date1.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

   tr=dateFinALL->text();
   date2=(((date2.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

   emit  sigRechercheALLTodoCont( date1,date2,li);
   QString texte;
   QString Tach;
   Tach+="idTodo    | ";
   Tach+="idIntera  | ";
   Tach+=" ContenuTodo | ";
   Tach+="  dateTodo\n\n";
   ui->plainTextEditTodo->insertPlainText(Tach); /*!< insertion de l'affichage sur le textEdit dedié .*/

   for(auto &p:li)
     {

      texte+=QString::number(p.getIdTodo())+ "\t";
      texte+=QString::number(p.getIdInteractionTodo())+"\t";
      texte+=QString::fromStdString(p.getDateTodo().fromDateString())+ "\t";
      texte+=QString::fromStdString(p.getContenuTodo())+"\n";

  }
  ui->plainTextEditTodo->insertPlainText(texte);
  dialogALL->close();

}


void Fenetre::on_actionCollecteContact_triggered()
{
  dialogRechercheT=new QDialog(this);
  dialogRechercheT->setWindowTitle(tr("Listes des taches d'un contact entre deux Dates "));
  dialogRechercheT->resize(400,1);
  dialogRechercheT->setModal(true);

  //Bouton
  BrechercherTaches= new QPushButton("Recherche taches");
  BannulerTachesR= new QPushButton("Annuler");

  //nom et date deubt
  QLabel *NomdateDebut=new QLabel("Date debut ");
  dateDebutTaches=new QDateEdit();

  QLabel *NomcomboBoxTaches=new QLabel("Choisir un contact ");


  //nom et date fin
  QLabel *NomdateFin=new QLabel("Date Fin ");
  dateFinTaches=new QDateEdit();


  vAligne1TachesR=new QVBoxLayout();
  vAligne2TachesR=new QVBoxLayout();
  hAligneTachesR=new QHBoxLayout();

  vAligne1TachesR->addWidget(NomcomboBoxTaches);
  vAligne1TachesR->addWidget(NomdateDebut);
  vAligne1TachesR->addWidget(NomdateFin);
  vAligne1TachesR->addWidget(BannulerTachesR);
  hAligneTachesR->addLayout(vAligne1TachesR);

  vAligne2TachesR->addWidget(comboTachesRecherche);
  vAligne2TachesR->addWidget(dateDebutTaches);
  vAligne2TachesR->addWidget(dateFinTaches);
  vAligne2TachesR->addWidget(BrechercherTaches);
  hAligneTachesR->addLayout(vAligne2TachesR);


  dialogRechercheT->setLayout(hAligneTachesR);

  dialogRechercheT->show();

  connect(BrechercherTaches,SIGNAL(clicked()),this,SLOT(RechercheTodoCont()));
  connect(BannulerTachesR,SIGNAL(clicked()),this,SLOT(BoutonAnnulerRechercherT()));
}

void Fenetre::BoutonAnnulerRechercherT()
{
  dialogRechercheT->close();
}

void Fenetre::RechercheTodoCont()
{
  ui->plainTextEditTodo->clear();
  comboTachesRecherche->clear();
  QString date1="";
  QString date2="";
  QString sep="-";
  QString t=comboTachesRecherche->currentText();
  int  c=t.toInt();

  if(t!=NULL)
  {

      QString tr=dateDebutTaches->text();
      date1=(((date1.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));
      tr=dateFinTaches->text();
      date2=(((date2.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));
      std::list<Todo> lt;
      lt.clear();
      emit sigRechercheTodoCont(c , date1 , date2 , lt);
      QString texte;
      QString Tach;
      Tach+="idTodo    | ";
      Tach+="idIntera  | ";
      Tach+=" ContenuTodo | ";
      Tach+="  dateTodo\n\n";
      ui->plainTextEditTodo->insertPlainText(Tach);
      for(auto &p:lt)
      {
                texte+=QString::number(p.getIdTodo())+ "\t";
                texte+=QString::number(p.getIdInteractionTodo())+"\t";
                texte+=QString::fromStdString(p.getDateTodo().fromDateString())+ "\t";
                texte+=QString::fromStdString(p.getContenuTodo())+"\n";

      }

      ui->plainTextEditTodo->insertPlainText(texte); /*!< insertion de l'affichage sur le textEdit dedié .*/

       }

   else
       {
            QMessageBox::warning(this,"Interaction entre deux dates ",
            "Impossible de faire la récherche sans voir la liste des contacts");
       }

    dialogRechercheT->close();
}

void Fenetre::on_actionInteraction_entre_deux_Dates_triggered()
{
    dialogIdeuxDates =new QDialog(this);
    dialogIdeuxDates->setWindowTitle(tr("Intéraction entre deux Dates "));
    dialogIdeuxDates->resize(400,10);
    dialogIdeuxDates->setModal(true);

    //Bouton
    BrechercheIdate=new QPushButton("Rechercher");
    BannulerIdate=new QPushButton("Annuler");

    //nom et date deubt
    QLabel *NomdateDebut=new QLabel("Date debut ");
    dateDebutI=new QDateEdit();

    //nom et date fin vAligne1
    QLabel *NomdateFin=new QLabel("Date Fin ",this);
    dateFinI=new QDateEdit();

    vAligne1Id=new QVBoxLayout(this);
    vAligne2Id=new QVBoxLayout(this);
    hAligneId=new QHBoxLayout();
    // NomR
    vAligne1Id->addWidget(NomdateDebut);
    vAligne1Id->addWidget(NomdateFin);
    vAligne1Id->addWidget(BannulerIdate);
    hAligneId->addLayout(vAligne1Id);

    vAligne2Id->addWidget(dateDebutI);
    vAligne2Id->addWidget(dateFinI);
    vAligne2Id->addWidget(BrechercheIdate);
    hAligneId->addLayout(vAligne2Id);
    dialogIdeuxDates->setLayout(hAligneId);

    dialogIdeuxDates->show();

    connect(BrechercheIdate,SIGNAL(clicked()),this,SLOT(RechercherInteractionEntreDeuxDates()));
    connect(BannulerIdate,SIGNAL(clicked()),this,SLOT(AnnulerInteractionEntreDeuxDates()));
}

void Fenetre::AnnulerInteractionEntreDeuxDates()
{
    dialogIdeuxDates->close();
}

void Fenetre::RechercherInteractionEntreDeuxDates()
{
    std::list<Interaction> li;
    ui->textEditInteraction->clear();//Pour raffraichir l'affichage sur la base de donnée
    QString date1="";
    QString date2="";
    QString sep="-";

    QString tr=dateDebutI->text();
    date1=(((date1.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

    tr=dateFinI->text();
    date2=(((date2.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

    sigRechercheInteraction(date1,date2,li);

    QString texte;
    QString inter;
    inter+="idInteract |   ";
    inter+="idContact  |   ";
    inter+="dateInter  |\t  ";
    inter+=" Contenu \n\n";
    ui->textEditInteraction->insertPlainText(inter);
    for(auto &p:li)
    {
            texte+=QString::number(p.getIdInteractionInter())+ "\t";
            texte+=QString::number(p.getIdContactInter())+"\t";
            texte+=QString::fromStdString(p.getRDV().fromDateString())+ "\t";
            texte+=QString::fromStdString(p.getContenu())+"\n";
    }
    ui->textEditInteraction->insertPlainText(texte);/*!< insertion de l'affichage sur le textEdit dedié .*/
    dialogIdeuxDates->close();

}



void Fenetre::FindContact()
{
    std::list<Interaction> li;
    ui->textEditInteraction->clear();

    QString date1="";
    QString date2="";
    QString sep="-";
    QString tr=date1RC->text();
    date1=(((date1.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));

    tr=date2RC->text();
    date2=(((date2.append(tr.mid(6,4)).append(sep)).append(tr.mid(3,2)).append(sep)).append(tr.mid(0,2)));
    QString t=comboRecherche->currentText();
    int  c=t.toInt();

    sigRechercheInteractionCont(c ,date1 ,date2 ,li);
    comboRecherche->clear();
    QString texte;
    QString inter;
    inter+="idInteract |   ";
    inter+="idContact  |   ";
    inter+="dateInter  |\t  ";
    inter+=" Contenu \n\n";
    ui->textEditInteraction->insertPlainText(inter);
    for(auto &p:li)
    {
            texte+=QString::number(p.getIdInteractionInter())+ "  |  ";
            texte+=QString::number(p.getIdContactInter())+"  |  ";
            texte+=QString::fromStdString(p.getRDV().fromDateString())+ "  |  ";
            texte+=QString::fromStdString(p.getContenu())+"\n";
    }
    ui->textEditInteraction->insertPlainText(texte);
    dialogRC->close();
}

void Fenetre::CancelContact()
{
    dialogRC->close();
}

void Fenetre::RemplirSupIntersc(const QString  & valeur )
{
    std::list<Contact> lp;
    lp.clear();
    emit sigGetContactList(lp);
    int val=valeur.toInt();
    for(auto &p:lp)
    {
            if(p.getIdContact()==val)
            {
                interactiontextsc->setText(QString::fromStdString(p.getNom())+"  "+QString::fromStdString(p.getPrenom()));

            }
    }
}

void Fenetre::on_actionInter_contact_triggered()
{


    dialogRC=new QDialog(this);
    dialogRC->setWindowTitle(tr("Rechercher interaction contact entre deux dates "));
    dialogRC->setModal(true);


    //nom
    QLabel *NContact=new QLabel("Indice contact");
    //label date debut
    QLabel *debutRC=new QLabel("Date début");
        //label date fin
        QLabel *finRC=new QLabel("Date de fin ");

    //champs de texte
    date1RC= new QDateEdit();
    date2RC= new QDateEdit();

    /****Dimension****/
    vAligneRRC=new QVBoxLayout();
    vAligneR2RC=new QVBoxLayout();
    hAlignHRC=new QHBoxLayout();

    //Bouton
    BRechercherRC= new QPushButton("Rechercher");
    BannulerRC= new QPushButton("Annuler");

    intertextsc=new QLabel("NOM/PRENOM");/*!< décalration du QLabel pour le contact entre 2 date de son interaction */
   interactiontextsc=new QLineEdit();/*!< décalration du QLabel pour le contact à son nom */

    vAligneRRC->addWidget(NContact);
    vAligneRRC->addWidget(intertextsc);

    vAligneRRC->addWidget(debutRC);
    vAligneRRC->addWidget(finRC);
    vAligneRRC->addWidget(BannulerRC);
    hAlignHRC->addLayout(vAligneRRC);


    vAligneR2RC->addWidget(comboRecherche);
    vAligneR2RC->addWidget(interactiontextsc);

    vAligneR2RC->addWidget(date1RC);
    vAligneR2RC->addWidget(date2RC);
    vAligneR2RC->addWidget(BRechercherRC);
    hAlignHRC->addLayout(vAligneR2RC);

    dialogRC->setLayout(hAlignHRC);

    dialogRC->show();

    connect(BRechercherRC,SIGNAL(clicked()),this,SLOT(FindContact()));
    connect(BannulerRC,SIGNAL(clicked()),this,SLOT(CancelContact()));
    connect(comboRecherche,SIGNAL(currentTextChanged(const QString  & )),this,SLOT(RemplirSupIntersc(const QString  & )));

}



void Fenetre::on_actionJson_Contact_Interaction_triggered()
{

    std::list<Contact> lp;
    BD.ListContact(lp);

    std::list<Interaction> inter;
    inBDD.ListeInteractionALL(inter);

    QJsonArray table;  // Création d'une table commune

    // Export des contacts
    int retContacts = QMessageBox::information(0, "Exporter en Json", "Voulez-vous exporter les contacts en fichier Json", QMessageBox::Cancel | QMessageBox::Ok);

    if (retContacts == QMessageBox::Ok)
    {
        for (const auto &p : lp)
        {
                QJsonObject obj;
                obj.insert("Type", "Contact");
                obj.insert("Nom", QString::fromStdString(p.getNom()));
                obj.insert("Prenom", QString::fromStdString(p.getPrenom()));
                obj.insert("Entreprise", QString::fromStdString(p.getEntreprise()));
                obj.insert("Telephone", QString::fromStdString(p.getTel()));
                obj.insert("Mail", QString::fromStdString(p.getMail()));
                obj.insert("Photo", QString::fromStdString(p.getPhoto()));
                obj.insert("Date de création", QString::fromStdString(p.getDateDecreation().fromDateString()));
                    table.append(obj);
        }
    }

    // Export des interactions
    int retInteractions = QMessageBox::information(0, "Exporter en Json", "Voulez-vous exporter les interactions en fichier Json", QMessageBox::Cancel | QMessageBox::Ok);

    if (retInteractions == QMessageBox::Ok)
    {
        for (const auto &p : inter)
        {
                QJsonObject obj;
                obj.insert("Type", "Interaction");
                obj.insert("Date de création", QString::fromStdString(p.getRDV().fromDateString()));
                    obj.insert("Contenu", QString::fromStdString(p.getContenu()));
                table.append(obj);
        }
    }

    // Export de la table complète
    QJsonDocument document(table);
    QByteArray bytes = document.toJson();

    QFile file("/tmp/export.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << bytes;
}


void Fenetre::ListeTodos()
{


    std::list<Todo> li;
    li.clear();
    emit sigListeALLContact(li);
    QCoreApplication::processEvents();
    qDebug() << "ListeTodos called";
    qDebug() << "Signal sigListeALLContact emitted with " << li.size() << " elements";

    ui->plainTextEditTodo->clear();
    QString texte;
    QString daTeInverse;//variable qui inverse la valeur
    int position;
    QString Tach;
    //Tach+="idTodo   | ";
    Tach+="idIntera   | ";
    Tach+="ContenuTodo| ";
    Tach+="  dateTodo\n\n";
    ui->plainTextEditTodo->insertPlainText(Tach);
    for(auto &p:li)
    {
        position=p.getContenuTodo().find("à faire maintenant");/*!< verifier si la tache est urgente ou pas avec la fonction find */
            daTeInverse=QString::fromStdString(p.getDateTodo().fromDateString());
            texte+=QString::number(p.getIdTodo())+ "\t";
            texte+=QString::number(p.getIdInteractionTodo())+"\t";

        if(position>0)
         {
            texte+=" @todo "+QString::fromStdString(p.getContenuTodo())+"\n"; /*!< pour pouvoir faire le tag avec @todo*/
    }
    else{
        //recuperer la  date du todo en chaine de caractere
        QString date="";
        QString sep="/";
        date=(((date.append(daTeInverse.mid(8,2)).append(sep)).append(daTeInverse.mid(5,2)).append(sep)).append(daTeInverse.mid(0,4)));/*!< Inversion de la date de jj/mm/aaaa vers aaaa-mm-jj afin de pouvoir l'insérer dans la base */
             texte+=" @todo "+QString::fromStdString(p.getContenuTodo())+" @date "+date+"\n";/*!< pour pouvoir faire le tag avec @date*/

    }

}
ui->plainTextEditTodo->insertPlainText(texte); /*!< insertion de l'affichage sur le textEdit dedié .*/

  qDebug() << "ListeTodos completed";
}
void Fenetre::TotalContact(int & tot)
{
QString texte="Le nombre total de contact est : "+QString::number(tot)+"\n";
ui->LNombrecontact->setText(texte);

}


void Fenetre::onListeALLContact(std::list<Todo> li)
{

qDebug() << "Slot onListeALLContact received with " << li.size() << " elements";
// Handle the list here or trigger further processing
// ...
}


