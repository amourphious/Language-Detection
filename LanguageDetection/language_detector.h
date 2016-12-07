#ifndef LANGUAGEDETECTOR_H
#define LANGUAGEDETECTOR_H
#include "language_score_model.h"
#include <QList>

class LanguageDetector
{
private:
    static QMap<QString, LanguageScoreModel> *languageLeague;
    LanguageScoreModel *input;
    QMap<int, QString> *inputWeightMap;
    QMap<QString, double> *languageScoreMap;
    void processInput(QString inputStr);
    void updateScore(QString language, QString ngram, int weight);
    QList<QString> removeNonProbableLanguages(QList<QString> languageList, int margin);
    void init();
public:
    LanguageDetector();
    LanguageDetector(QString input);
    QString detectLanguage(QString input);
    QList<int> getKeys();
};

#endif // LANGUAGEDETECTOR_H
