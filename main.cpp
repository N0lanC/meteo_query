#include <iostream>
#include "presenter.h"


int main(int argc, char *argv[]) {
    auto *app = new QApplication(argc, argv);
    auto myObject = new presenter(app);
    //myObject->TestConnection();

    return QApplication::exec();
}