#include "central.h"

void MainWindow::onglets(void){



    QWidget *zoneCentrale = new QWidget;


        QLineEdit *nom = new QLineEdit;
        QLineEdit *prenom = new QLineEdit;

        QFormLayout *layout = new QFormLayout;
        layout->addRow("Votre nom", nom);
        layout->addRow("Votre prénom", prenom);

        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addLayout(layout);

        QLineEdit *age = new QLineEdit;

        QFormLayout *layout1 = new QFormLayout;
        layout1->addRow("Votre âge", age);

        vbox->addLayout(layout1);

        QVBoxLayout *layoutPrincipal = new QVBoxLayout;

        layoutPrincipal->addLayout(vbox);









        QTabWidget *onglets = new QTabWidget(this);
//        onglets->setGeometry(100, 100, 440, 460);

        // 2 : Créer les pages, en utilisant un widget parent pour contenir chacune des pages
        QWidget *page1 = new QWidget;
        QWidget *page2 = new QWidget;
        QLabel *page3 = new QLabel; // Comme un QLabel est aussi un QWidget (il en hérite), on peut aussi s'en servir de page

        // 3 : Créer le contenu des pages de widgets

            // Page 1
            QLineEdit *lineEdit = new QLineEdit("Entrez votre nom");
            QPushButton *bouton1 = new QPushButton("Cliquez ici");
            QPushButton *bouton2 = new QPushButton("Ou là…");

            QVBoxLayout *vbox1 = new QVBoxLayout;
            vbox1->addWidget(lineEdit);
            vbox1->addWidget(bouton1);
            vbox1->addWidget(bouton2);

            page1->setLayout(vbox1);

            // Page 2
            QProgressBar *progress = new QProgressBar;
            progress->setValue(50);
            QSlider *slider = new QSlider(Qt::Horizontal);
            QPushButton *bouton3 = new QPushButton("Valider");

            QVBoxLayout *vbox2 = new QVBoxLayout;
            vbox2->addWidget(progress);
            vbox2->addWidget(slider);
            vbox2->addWidget(bouton3);

            page2->setLayout(vbox2);

            // Page 3 (je ne vais afficher qu'une image ici, pas besoin de layout)

            //page3->setPixmap(QPixmap("icone.png"));
            //page3->setAlignment(Qt::AlignCenter);

        // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
        onglets->addTab(page1, "Coordonnées");
        onglets->addTab(page2, "Progression");
        onglets->addTab(page3, "Image");




        layoutPrincipal->addWidget(onglets);



        zoneCentrale->setLayout(layoutPrincipal);
        setCentralWidget(zoneCentrale);


}
