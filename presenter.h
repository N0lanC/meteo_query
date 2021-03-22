//
// Created by nolcordier on 11/03/2021.
//

#ifndef METEO_QUERY_PRESENTER_H
#define METEO_QUERY_PRESENTER_H

#include <QtCore/QObject>
#include "fenetre.h"
#include <QtNetwork>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QApplication>
#include <QtWidgets/QMessageBox>

class presenter: public QObject {
    Q_OBJECT;
private:
    fenetre *f;
    QTimer *timerConnection;

    double temp;
    int alt;
    int press;

    int dureemax;
    int timerefresh;

    // FONCTION CALCUL TENDANCE °C
    QVector<double> tendancetemperature;
    QVector<double> indexTemp;
    QVector<double> produitTemp;
    QVector<double> powerTemp;
    double sumproduitTemp;
    double sumcarreTemp;
    int sumindexTemp;
    double sumdataTemp;
    int produitdataTemp;
    int carreTemp;
    double totalTemp;

    // FONCTION CALCUL TENDANCE ALT
    QVector<double> tendancealtitude;
    QVector<double> indexAlt;
    QVector<double> produitAlt;
    QVector<double> powerAlt;
    double sumproduitAlt;
    double sumcarreAlt;
    int sumindexAlt;
    double sumdataAlt;
    int produitdataAlt;
    int carreAlt;
    double totalAlt;

    // FONCTION CALCUL TENDANCE PRESS
    QVector<double> tendancepressure;
    QVector<double> indexPress;
    QVector<double> produitPress;
    QVector<double> powerPress;
    double sumproduitPress;
    double sumcarrePress;
    int sumindexPress;
    double sumdataPress;
    int produitdataPress;
    int carrePress;
    double totalPress;

public:
    explicit presenter(QApplication* application);
    void TestConnection() const;
    void ReplyFinished(QNetworkReply *reply);

    void calcultendancetemp();
    void calcultendancealt();
    void calcultendancePress();

    void calcul();


    QNetworkAccessManager *manager;
    QString answer;

public slots: //ici choix de slots car appelé quand signal est émis via les connect
    void readData();


};


#endif //METEO_QUERY_PRESENTER_H
