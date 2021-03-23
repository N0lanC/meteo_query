//
// Created by nolcordier on 11/03/2021.
//

#include "fenetre.h"
#include <QtWidgets/QGridLayout>
#include <QDebug>
#include <QtWidgets/QLabel>


fenetre::fenetre() : QFrame() {





    layout= new QGridLayout;

    refreshButton = new QPushButton("Refresh");//création boutton settings
    refreshButton->setStyleSheet("background-color: rgb(206,206,206);");

    /* CRATION JAUGE TEMPERATURE */
    mDegGauge = new QcGaugeWidget();

    // Fond de la jauge
    mDegGauge->addBackground(100);
    bkgDeg = mDegGauge->addBackground(92);
    bkgDeg->clearrColors();
    bkgDeg->addColor(1,Qt::black);

    // Arc autour de l'arc de couleur
    QcArcItem *arcItemDeg = mDegGauge->addArc(55);
    arcItemDeg->setColor(Qt::white);

    // Creation des petits reperes autour de l'arc
    degreesItemDeg = mDegGauge->addDegrees(65);
    degreesItemDeg->setValueRange(-10,40);
    degreesItemDeg->setStep(10);
    degreesItemDeg->setColor(Qt::white);

    // Creation de la bande couleur
    QcColorBand *clrBandDeg = mDegGauge->addColorBand(50);
    clrBandDeg->setValueRange(0, 50);
    QList<QPair<QColor,float>> *colorsDeg = new QList<QPair<QColor,float>>;
    colorsDeg->push_back(QPair<QColor,float>(Qt::yellow,10));
    colorsDeg->push_back(QPair<QColor,float>(Qt::green,40));
    colorsDeg->push_back(QPair<QColor,float>(Qt::red,50));
    clrBandDeg->setColors(*colorsDeg);

    // Création des nombre pour les reperes autour de la jauge
    valuesDeg=mDegGauge->addValues(80);
    valuesDeg->setValueRange(-10,40);
    valuesDeg->setStep(10);
    valuesDeg->setColor(Qt::white);


    // Creation du texte (unité)
    labUnitDeg = mDegGauge->addLabel(70);
    labUnitDeg->setText("°C");
    labUnitDeg->setColor(Qt::white);

    // Creation texte valeur affiché
    labDeg = mDegGauge->addLabel(40);
    labDeg->setText("");
    labDeg->setColor(Qt::white);

    // Creation aiguille
    mDegNeedle = mDegGauge->addNeedle(60);
    mDegNeedle->setLabel(labDeg);
    mDegNeedle->setColor(Qt::white);
    mDegNeedle->setValueRange(-10, 40);
    mDegGauge->addBackground(7); // Point gris sur l'aiguille

    // CREATION JAUGE ALT

    mAltGauge = new QcGaugeWidget;

    mAltGauge->addBackground(99);
    bkgAlt = mAltGauge->addBackground(92);
    bkgAlt->clearrColors();
    bkgAlt->addColor(1,Qt::black);


    QcArcItem *arcItemAlt = mAltGauge->addArc(55);
    arcItemAlt->setColor(Qt::white);

    degreesItemAlt = mAltGauge->addDegrees(65); // Creation des petits batons
    degreesItemAlt->setValueRange(100,1000);
    degreesItemAlt->setStep(100);
    degreesItemAlt->setColor(Qt::white);

    QcColorBand *clrBandAlt = mAltGauge->addColorBand(50); // Creation de la bande couleur
    clrBandAlt->setValueRange(0, 100);
    QList<QPair<QColor,float>> *colorsAlt = new QList<QPair<QColor,float>>;
    colorsAlt->push_back(QPair<QColor,float>(Qt::blue,78)); // Configuration de la couleur sur la bande, jusqu'a 800
    colorsAlt->push_back(QPair<QColor,float>(Qt::darkBlue,100));
    clrBandAlt->setColors(*colorsAlt);

    valuesAlt=mAltGauge->addValues(80); // Création de l'objet pour les reperes autour de la jauge
    valuesAlt->setValueRange(100,1000);
    valuesAlt->setStep(100);
    valuesAlt->setColor(Qt::white);

    labUnitAlt = mAltGauge->addLabel(70);// affichage unité
    labUnitAlt->setText("m");
    labUnitAlt->setColor(Qt::white);
    labAlt = mAltGauge->addLabel(40); // Valeur affiché
    labAlt ->setText("");
    labAlt ->setColor(Qt::white);
    mAltNeedle = mAltGauge->addNeedle(60); // Creation aiguille
    mAltNeedle->setLabel(labAlt); //mettre aiguille à la valeur demandé
    mAltNeedle->setColor(Qt::white); // COnfig couleur de l'aiguille
    mAltNeedle->setValueRange(100, 1000);
    mAltGauge->addBackground(7);


     /* CREATION JAUGE PRESSION */

    mPressGauge = new QcGaugeWidget; // CREATION JAUGE

    mPressGauge->addBackground(99);
    bkgPress = mPressGauge->addBackground(92);
    bkgPress->clearrColors();
    bkgPress->addColor(1,Qt::black);


    QcArcItem *arcItemPress = mPressGauge->addArc(55);
    arcItemPress->setColor(Qt::white);

    degreesItemPress = mPressGauge->addDegrees(65); // Creation des petits batons
    degreesItemPress->setValueRange(960,1060);
    degreesItemPress->setStep(10);
    degreesItemPress->setColor(Qt::white);

    QcColorBand *clrBandPress = mPressGauge->addColorBand(50); // Creation de la bande couleur
    clrBandPress->setValueRange(0, 100);
    QList<QPair<QColor,float>> *colorsPress = new QList<QPair<QColor,float>>;
    colorsPress->push_back(QPair<QColor,float>(Qt::red,40)); // Configuration de la couleur sur la bande, jusqu'a 800
    colorsPress->push_back(QPair<QColor,float>(Qt::yellow,60));
    colorsPress->push_back(QPair<QColor,float>(Qt::green,100));
    clrBandPress->setColors(*colorsPress);

    valuesPress=mPressGauge->addValues(80); // Création de l'objet pour les reperes autour de la jauge
    valuesPress->setValueRange(960,1060);
    valuesPress->setStep(10);
    valuesPress->setColor(Qt::white);



    labUnitPress = mPressGauge->addLabel(70); // affichage unité
    labUnitPress->setText("Hpa");
    labUnitPress->setColor(Qt::white);

    labPress = mPressGauge->addLabel(40); // Valeur affiché
    labPress->setText("");
    labPress->setColor(Qt::white);
    mPressNeedle = mPressGauge->addNeedle(60); // Creation aiguille
    mPressNeedle->setLabel(labPress);
    mPressNeedle->setColor(Qt::white); // COnfig couleur de l'aiguille
    mPressNeedle->setValueRange(960, 1060);
    mPressGauge->addBackground(7);


/* CREATION JAUGE TENDANCE °C */
    tDegGauge = new QcGaugeWidget;

    tDegGauge->addBackground(99);

    bkgtDeg = tDegGauge->addBackground(92);
    bkgtDeg = tDegGauge->addBackground(92);
    bkgtDeg->clearrColors();
    bkgtDeg->addColor(1,Qt::black);

    degreesItemtDeg = tDegGauge->addDegrees(65); // Creation des petits batons
    degreesItemtDeg = tDegGauge->addDegrees(65); // Creation des petits batons
    degreesItemtDeg->setColor(Qt::white);

    QcColorBand *clrBandT = tDegGauge->addColorBand(50); // Creation de la bande couleur
    clrBandT->setValueRange(0, 100);
    QList<QPair<QColor,float>> *colorsT = new QList<QPair<QColor,float>>;
    colorsT->push_back(QPair<QColor,float>(Qt::red,50)); // Configuration de la couleur sur la bande, jusqu'a 800
    colorsT->push_back(QPair<QColor,float>(Qt::green,100));
    clrBandT->setColors(*colorsT);

    labArrowTendanceDeg = tDegGauge->addLabel(50);
    labArrowTendanceDeg->setText("↑");
    labArrowTendanceDeg->setColor(Qt::red);

    labUnitTDeg = tDegGauge->addLabel(70); // affichage unité
    labUnitTDeg->setText("Tendance °C ");
    labUnitTDeg->setColor(Qt::white);


    tDegNeedle = tDegGauge->addNeedle(60); // Creation aiguille
    tDegNeedle->setColor(Qt::white); // COnfig couleur de l'aiguille
    tDegNeedle->setValueRange(-5,5);
    tDegGauge->addBackground(7);


    /* CREATION JAUGE TENDANCE ALT */

    tAltGauge = new QcGaugeWidget;

    tAltGauge->addBackground(99);

    bkgtAlt = tAltGauge->addBackground(92);
    bkgtAlt = tAltGauge->addBackground(92);
    bkgtAlt->clearrColors();
    bkgtAlt->addColor(1,Qt::black);

    degreesItemtAlt = tAltGauge->addDegrees(65); // Creation des petits batons
    degreesItemtAlt = tAltGauge->addDegrees(65); // Creation des petits batons
    degreesItemtAlt->setColor(Qt::white);

    clrBandT = tAltGauge->addColorBand(50); // Creation de la bande couleur
    colorsT->push_back(QPair<QColor,float>(Qt::red,50)); // Configuration de la couleur sur la bande, jusqu'a 800
    colorsT->push_back(QPair<QColor,float>(Qt::green,100));
    clrBandT->setColors(*colorsT);

    labArrowTendanceAlt = tAltGauge->addLabel(50);
    labArrowTendanceAlt->setText("↑");
    labArrowTendanceAlt->setColor(Qt::red);

    labUnitTAlt = tAltGauge->addLabel(70); // affichage unité
    labUnitTAlt->setText("Tendance m");
    labUnitTAlt->setColor(Qt::white);


    tAltNeedle = tAltGauge->addNeedle(60); // Creation aiguille
    tAltNeedle->setColor(Qt::white); // COnfig couleur de l'aiguille
    tAltNeedle->setValueRange(-1,1);
    tAltGauge->addBackground(7);

    /* CREATION JAUGE TENDANCE PRESS */

    tPressGauge = new QcGaugeWidget;

    tPressGauge->addBackground(99);

    bkgtPress = tPressGauge->addBackground(92);
    bkgtPress = tPressGauge->addBackground(92);
    bkgtPress->clearrColors();
    bkgtPress->addColor(1,"Qt::black");

    degreesItemtPress = tPressGauge->addDegrees(65); // Creation des petits batons
    degreesItemtPress = tPressGauge->addDegrees(65); // Creation des petits batons
    degreesItemtPress->setColor(Qt::white);

    clrBandT = tPressGauge->addColorBand(50); // Creation de la bande couleur
    colorsT->push_back(QPair<QColor,float>(Qt::red,50)); // Configuration de la couleur sur la bande, jusqu'a 800
    colorsT->push_back(QPair<QColor,float>(Qt::green,100));
    clrBandT->setColors(*colorsT);

    labArrowTendancePress = tPressGauge->addLabel(50);
    labArrowTendancePress->setText("↑");
    labArrowTendancePress->setColor(Qt::red);

    labUnitTPress = tPressGauge->addLabel(70); // affichage unité
    labUnitTPress->setText("Tendance Hpa");
    labUnitTPress->setColor(Qt::white);


    tPressNeedle = tPressGauge->addNeedle(60); // Creation aiguille
    tPressNeedle->setColor(Qt::white); // COnfig couleur de l'aiguille
    tPressNeedle->setValueRange(-1,1);
    tPressGauge->addBackground(7);


    layout->addWidget(mDegGauge,1,0);
    layout->addWidget(mAltGauge,1,1);
    layout->addWidget(mPressGauge,1,2);
    layout->addWidget(tDegGauge, 2,0);
    layout->addWidget(tAltGauge, 2,1);
    layout->addWidget(tPressGauge, 2,2);


    setLayout(layout);

}



QcGaugeWidget *fenetre::getMDegGauge() const {
    return mDegGauge;
}

QcGaugeWidget *fenetre::getMAltGauge() const {
    return mAltGauge;
}

QcGaugeWidget *fenetre::getMPressGauge() const {
    return mPressGauge;
}

QcNeedleItem *fenetre::getMDegNeedle() const {
    return mDegNeedle;
}

QcNeedleItem *fenetre::getTDegNeedle() const {
    return tDegNeedle;
}


QcNeedleItem *fenetre::getMAltNeedle() const {
    return mAltNeedle;
}

QcNeedleItem *fenetre::getMPressNeedle() const {
    return mPressNeedle;
}

QcNeedleItem *fenetre::getTAltNeedle() const {
    return tAltNeedle;
}

QcNeedleItem *fenetre::getTPressNeedle() const {
    return tPressNeedle;
}

QcLabelItem *fenetre::getLabArrowTendanceAlt() const {
    return labArrowTendanceAlt;
}

QcLabelItem *fenetre::getLabArrowTendanceDeg() const {
    return labArrowTendanceDeg;
}

QcLabelItem *fenetre::getLabArrowTendancePress() const {
    return labArrowTendancePress;
}

