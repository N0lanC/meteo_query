//
// Created by nolcordier on 11/03/2021.
//

#include "presenter.h"
#include "jute.h"

using namespace std;
presenter::presenter(QApplication *application) {
    f=new fenetre; // on créer l'objet f de type fenetre
    dureemax = 10; // on definie la variable a 10, c'est le nombre maximm de trame "analyser" et mis dans un tableau avant la reinitialisation
    manager = new QNetworkAccessManager(this); // un instancie l'objet manager de type QNetworkaccessmanager avec comme parent cette classe


    timerConnection = new QTimer();// création timer
    connect(timerConnection,&QTimer::timeout, this,&presenter::TestConnection); // on connecte le timer et la fonction testconnection, des que le timer est terminé il lance la fonction test connection
    timerConnection->start(4000); // on start le timer pour 4000 msec
    f->show(); // on appel la methode show pour affiché la fenetre

    f->setWindowTitle("Station Météo"); // changement du nom de la fenetre
    f->setStyleSheet("background-color: black;"); // Changement couleur du fond

}



void presenter::TestConnection() const {
    connect(manager, &QNetworkAccessManager::finished,this, &presenter::ReplyFinished); // quand l'objet manager recoit la reponse a sa requete il appel la fonction replyfinished avec comme attribut la reponse de la requete
    manager->get(QNetworkRequest(QUrl("http://192.168.104.172/meteo/lastrow.php"))); // envoie la requete
}

void presenter::ReplyFinished(QNetworkReply *reply) {
    answer = reply->readAll(); // answer prend la valeur de la trame reply
    readData(); // appel de la fonction readData
}

void presenter::readData() {
    QString data;
    data.append(answer);//ajoute les données provenant de la requete
    int end = data.lastIndexOf("\r\n") + 2;//la position de le dernière mesure
    QStringList cmds = QString(data.mid(0, end)).split("\r\n", QString::SkipEmptyParts); //décompose les différentes ligne et stock dans une QStringList      SkipEmptyParts-> on passe les cases vides
    for (QString cmd : cmds) { //parcours la QstringList et affiche le contenu
            jute::jValue v = jute::parser::parse(answer.toStdString()); // parser : analyse et découpe de la trame par clés et on ajoute ces jetons dans le vecteur v
            temp = v["temperature"].as_double(); // conversion de Qstring è double
            alt = v["altitude"].as_int();
            press = v["pression"].as_double();


            f->getMAltNeedle()->setCurrentValue(alt); // set la valeur de l'aiguille
            f->getMAltGauge()->repaint(); // met a jour la position de l'aiguille
            f->getMDegNeedle()->setCurrentValue(temp);
            f->getMDegGauge()->repaint();
            f->getMPressNeedle()->setCurrentValue(press);
            f->getMPressGauge()->repaint();
    }
    calcul();
}

void presenter::calcultendancetemp() {
    tendancetemperature.push_back(temp); //ajout des valeurs dans le vector
    indexTemp.push_back(tendancetemperature.size()); // ajout de la taille du vector tendance dans le vector index
    sumindexTemp = std::accumulate(indexTemp.begin(), indexTemp.end(), 0); // somme du vector
    sumdataTemp = std::accumulate(tendancetemperature.begin(), tendancetemperature.end(), 0);// somme du vector
    produitdataTemp = temp * tendancetemperature.size()+1; // multiplication de la valeur par la taille du vector (+1 car sinon il prendre la "case" d'avant)
    produitTemp.push_back(produitdataTemp); // ajout du resultat precedent dans le vector
    sumproduitTemp = std::accumulate(produitTemp.begin(),produitTemp.end(),0); // somme du vector
    carreTemp = pow(tendancetemperature.size(), 2.0); // calcul du carré de la taille du vector
    powerTemp.push_back(carreTemp); // ajout du resultat precedent dans le vector
    sumcarreTemp = std::accumulate(powerTemp.begin(),powerTemp.end(),0); // somme du vector


    //pour le calcul nous avons diviser en 4 parties
    double hautgauche = tendancetemperature.size()*sumproduitTemp;
    double hautdroit = sumindexTemp*sumdataTemp;
    double haut = hautgauche - hautdroit;

    double basgauche = tendancetemperature.size()*sumcarreTemp;
    double basdroit = pow(sumindexTemp,2);
    double bas = basgauche - basdroit;

    totalTemp = haut / bas; // resultat final
    //qDebug() << "Temperature :" << totalTemp;

    if (totalTemp > 0) { // si la tendance est positive
        f->getLabArrowTendanceDeg()->setText("↑");
        f->getLabArrowTendanceDeg()->setColor(Qt::green);
    } else if (totalTemp < 0) { // si la tendance est negative
        f->getLabArrowTendanceDeg()->setText("↓");
        f->getLabArrowTendanceDeg()->setColor(Qt::red);
    } else if (totalTemp == 0) { // si la tendance est a zero
        f->getLabArrowTendanceDeg()->setText("=");
        f->getLabArrowTendanceDeg()->setColor(Qt::white);
    }
    f->getTDegNeedle()->setCurrentValue(totalTemp); // met a jour la valeur/position de l'aiguille

    if(tendancetemperature.size()>dureemax-1) { //si la taille du vector est superieur a la valeur donné dans la fenetre parametre on remet tout a zero
        tendancetemperature.erase(tendancetemperature.begin(),tendancetemperature.end()); //effacer les données de la trame dans le tableau tendancetemp
        indexTemp.erase(indexTemp.begin(),indexTemp.end()); //efface les données du vecteur index
        sumindexTemp =0;
        sumdataTemp = 0;
        produitdataTemp =0;
        produitTemp.erase(produitTemp.begin(),produitTemp.end());   //effacer les donnees vecteur temp
        sumproduitTemp =0;
        carreTemp =0;
        powerTemp.erase(powerTemp.begin(),powerTemp.end()); //effacer les donnees vecteur pow
        sumcarreTemp=0;

    }
}

void presenter::calcultendancealt() {
    tendancealtitude.push_back(alt); //ajout des valeurs dans le vector
    indexAlt.push_back(tendancealtitude.size()); // ajout de la taille du vector tendance dans le vector index
    sumindexAlt = std::accumulate(indexAlt.begin(), indexAlt.end(), 0); // somme du vector
    sumdataAlt = std::accumulate(tendancealtitude.begin(), tendancealtitude.end(), 0);
    produitdataAlt = alt * tendancealtitude.size()+1;
    produitAlt.push_back(produitdataAlt);
    sumproduitAlt = std::accumulate(produitAlt.begin(),produitAlt.end(),0);
    carreAlt = pow(tendancealtitude.size(), 2.0);
    powerAlt.push_back(carreAlt);
    sumcarreAlt = std::accumulate(powerAlt.begin(),powerAlt.end(),0);


    double hautgauche = tendancealtitude.size()*sumproduitAlt;
    double hautdroit = sumindexAlt*sumdataAlt;
    double haut = hautgauche - hautdroit;

    double basgauche = tendancealtitude.size()*sumcarreAlt;
    double basdroit = pow(sumindexAlt,2);
    double bas = basgauche - basdroit;

    totalAlt = haut / bas;
    //qDebug() << "Altitude :" << totalAlt;


    if (totalAlt > 0) {
        f->getLabArrowTendanceAlt()->setText("↑");
        f->getLabArrowTendanceAlt()->setColor(Qt::green);
    } else if (totalAlt < 0) {
        f->getLabArrowTendanceAlt()->setText("↓");
        f->getLabArrowTendanceAlt()->setColor(Qt::red);
    }
    else if (totalAlt == 0) {
        f->getLabArrowTendanceAlt()->setText("=");
        f->getLabArrowTendanceAlt()->setColor(Qt::white);
    }
    f->getTAltNeedle()->setCurrentValue(totalAlt);

    if(tendancealtitude.size()>dureemax-1) { // si la taille du vecteur tendance alt est supérieur à dmax-1 alors ...
        tendancealtitude.erase(tendancealtitude.begin(),tendancealtitude.end()); // supprime donnés de vector index 0 à index final
        indexAlt.erase(indexAlt.begin(),indexAlt.end());
        sumindexAlt =0;
        sumdataAlt = 0;
        produitdataAlt =0;
        produitAlt.erase(produitAlt.begin(),produitAlt.end());
        sumproduitAlt =0;
        carreAlt =0;
        powerAlt.erase(powerAlt.begin(),powerAlt.end());
        sumcarreAlt=0;
    }
}


void presenter::calcultendancePress() {
    tendancepressure.push_back(press);
    indexPress.push_back(tendancepressure.size());
    sumindexPress = std::accumulate(indexPress.begin(), indexPress.end(), 0);
    sumdataPress = std::accumulate(tendancepressure.begin(), tendancepressure.end(), 0);
    produitdataPress = press * tendancepressure.size()+1;
    produitPress.push_back(produitdataPress);
    sumproduitPress = std::accumulate(produitPress.begin(),produitPress.end(),0);
    carrePress = pow(tendancepressure.size(), 2.0);
    powerPress.push_back(carrePress);
    sumcarrePress = std::accumulate(powerPress.begin(),powerPress.end(),0);

    double hautgauche = tendancepressure.size()*sumproduitPress;
    double hautdroit = sumindexPress*sumdataPress;
    double haut = hautgauche - hautdroit;

    double basgauche = tendancepressure.size()*sumcarrePress;
    double basdroit = pow(sumindexPress,2);
    double bas = basgauche - basdroit;

    totalPress = haut / bas;
    //qDebug() << "Pression :" << totalPress;

    if (totalPress > 0) {
        f->getLabArrowTendancePress()->setText("↑");
        f->getLabArrowTendancePress()->setColor(Qt::green);
    } else if (totalPress < 0) {
        f->getLabArrowTendancePress()->setText("↓");
        f->getLabArrowTendancePress()->setColor(Qt::red);
    }else if (totalPress == 0) {
        f->getLabArrowTendancePress()->setText("=");
        f->getLabArrowTendancePress()->setColor(Qt::white);
    }
    f->getTPressNeedle()->setCurrentValue(totalPress);


    if(tendancepressure.size()>dureemax-1) {
        tendancepressure.erase(tendancepressure.begin(), tendancepressure.end());
        indexPress.erase(indexPress.begin(),indexPress.end());
        sumindexPress =0;
        sumdataPress = 0;
        produitdataPress =0;
        produitPress.erase(produitPress.begin(),produitPress.end());
        sumproduitPress =0;
        carrePress =0;
        powerPress.erase(powerPress.begin(),powerPress.end());
        sumcarrePress=0;
    }
}

void presenter::calcul() { // calcul des tendances
    calcultendancetemp();
    calcultendancealt();
    calcultendancePress();
}





