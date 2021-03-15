//
// Created by nolcordier on 11/03/2021.
//

#include "presenter.h"
#include "jute.h"

using namespace std;
presenter::presenter(QApplication *application) {
    f=new fenetre;
    f->show();

    manager = new QNetworkAccessManager(application);

    timerValue = new QTimer(); // création timer
    connect(timerValue,&QTimer::timeout, this,&presenter::TestConnection); // quand le timer est fini on lance la fonction readData
    timerValue->start(5000);

}

void presenter::TestConnection() const {
    connect(manager, &QNetworkAccessManager::finished,this, &presenter::ReplyFinished);
    manager->get(QNetworkRequest(QUrl("http://192.168.104.172/meteo/lastrow.php")));
}

void presenter::ReplyFinished(QNetworkReply *reply) {
    answer = reply->readAll();
    readData();
}

void presenter::readData() {
    QString rxBytes;
    rxBytes.append(answer);//lit les données provenant du port série
    int end = rxBytes.lastIndexOf("\r\n") + 2;//la position de le dernière mesure
    QStringList cmds = QString(rxBytes.mid(0, end)).split("\r\n", QString::SkipEmptyParts); //décompose les différentes la ligne et stock dans une QStringLis
    for (QString cmd : cmds) { //parcours la QstringList et affiche le contenu
            jute::jValue v = jute::parser::parse(answer.toStdString());
            f->getAltvalue()->setText(QString::number(v["altitude"].as_int()));
            f->getPressvalue()->setText(QString::number(v["pression"].as_int()));
            f->getTempvalue()->setText(QString::number(v["temperature"].as_double()));
    }
}


