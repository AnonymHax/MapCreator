#include "SYSTEM/Public.h"
#include "SYSTEM/Interface.h"
#include <QApplication>
#include <QSplashScreen>
#include <QMessageBox>
#include "SYSTEM/MainWindow.h"

 int main(int argc, char **argv)
{
    QApplication App(argc, argv);

    QSplashScreen loadScreen (QPixmap ("://icons/splashscreen.png"));
    loadScreen.show();

    if (!FONT.loadFromFile(DEFAULT_FONT_PATH))
        qDebug()<<"Chargement police de defaut echoué";

    if (!BLUR_SHADER.loadFromFile(BLUR_SHADER_PATH,sf::Shader::Fragment))
        qDebug()<<"Chargement shader_blur echoué";
    BLUR_SHADER.setParameter("texture",sf::Shader::CurrentTexture);
    BLUR_SHADER.setParameter("offset",0.005*LIGHT_SMOOTH);

    MainWindow mainWindow;
    mainWindow.show();
    loadScreen.finish(&mainWindow);


    /*QString path = QFileDialog::getOpenFileName(new QWidget());
    QFile a (path);
     a.open(QIODevice::ReadWrite);
     QByteArray b;
     b = qCompress(a.readAll());
     a.close();
     QFile c (path+"o");
     c.open(QIODevice::WriteOnly);
     c.write( b);
     c.close();*/

    return App.exec();
}
