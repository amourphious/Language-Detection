#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include "training_text_map.h"
#include "language_score_model.h"
#include "language_detector.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    LanguageDetector ld("hello hello");
    QString l = ld.detectLanguage("helo my name is");
    l = ld.detectLanguage("Hola mi");
    return a.exec();
}
