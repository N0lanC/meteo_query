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
    QTimer *timerValue;

public:
    explicit presenter(QApplication* application);
    void TestConnection() const;
    void ReplyFinished(QNetworkReply *reply);
    void timer();

    QNetworkAccessManager *manager;
    QString answer;

public slots: //ici choix de slots car appelé quand signal est émis via les connect
    void readData();


};


#endif //METEO_QUERY_PRESENTER_H
