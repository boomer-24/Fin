#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        MainWindow w;
        w.show();                

        QTextCodec* codec1251 = QTextCodec::codecForName("CP1251");
        QByteArray text = argv[1];
        QString path = codec1251->toUnicode(text);
        path.replace('\\', '/');
        if (argc > 2)
            for (int i = 2; i <= argc; i++)
            {
                QByteArray text1 = argv[i];
                path.append(" ").append(codec1251->toUnicode(text1));
            }

        w.setDirPath(path);

        return a.exec();
}
