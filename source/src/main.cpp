#include <iostream>
#include <QApplication>
int main(int argc, char** argv){
    QApplication a(argc, argv);
    QString ss = "sdfdsfsd";
    std::cout << ss.toStdString() << std::endl;
    a.exec();
    return 0;
}