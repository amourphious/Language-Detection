#include <QCoreApplication>

#include "training_text_map.h"
#include "languagedectector.h"
#include <iostream>
#include <stdio.h>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QTextStream>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    LanguageDetector ld;
    //ins.close();
    char str[10000];
    while(gets(str)){
        if (str[0] == '@')
            break;
        QString lng = ld.detectLanguage(str);
        qDebug()<<"detected Language: "<<lng;
        qDebug()<<"Press @ to exit";
    }
    return a.exec();
}
