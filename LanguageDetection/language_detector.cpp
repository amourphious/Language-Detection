#include "language_detector.h"
#include <QDir>


LanguageDetector::LanguageDetector()
{
    init();
}

QMap<QString, LanguageScoreModel> *LanguageDetector::languageLeague = new QMap<QString, LanguageScoreModel>();

LanguageDetector::LanguageDetector(QString input) {
    init();
    processInput(input);
}

void LanguageDetector::processInput(QString inputStr) {
    input = new LanguageScoreModel(inputStr, "unknown");
    inputWeightMap = new QMap<int, QString>();
    QList<QString> keys = input->getLanguageMap().getUniqueNGrams();
    for (int i = 0; i < keys.size(); i++) {
        inputWeightMap->insertMulti(input->getLanguageMap().getOccurence(keys[i]), keys[i]);
    }
}

QList<int> LanguageDetector::getKeys() {
    return this->inputWeightMap->keys();
}

void LanguageDetector::init() {
    QDir kdir;
    QString langdataDir = kdir.currentPath();
    qDebug()<<"here"<<langdataDir;

    if(!langdataDir.isEmpty()){
        QString langdataPath = langdataDir + "/langdata";
        QDir langDir;
        langDir.setPath(langdataPath);
        QStringList langList = langDir.entryList();

        qDebug()<< langList;
        QString content;
        languageScoreMap = new QMap<QString, double>();
        for (int i = 2; i < langList.size(); i++){
            if (languageLeague->contains(langList[i])) {
                languageScoreMap->insert(langList[i], -1);
                LanguageScoreModel lsm = languageLeague->value(langList[i]);
                lsm.init();
                languageLeague->insert(langList[i], lsm);
            } else {
                QFile langFile(langDir.filePath(langList[i]));
                if(langFile.open(QIODevice::ReadOnly | QIODevice::Text)){
                    content = langFile.readAll();
                    LanguageScoreModel newLanguage(content, langList[i]);
                    LanguageDetector::languageLeague->insert(langList[i], newLanguage);
                    languageScoreMap->insert(langList[i], -1);
                }
                else{
                    qDebug()<<"unable to open File: "<<langList[i];
                }
            }
        }
    }
    else
        qDebug()<<"no langdata found";
}

void LanguageDetector::updateScore(QString language, QString ngram, int weight) {
    LanguageScoreModel lsm = languageLeague->value(language);
    lsm.updateScore(ngram, weight);
    languageLeague->insert(language, lsm);
    languageScoreMap->insert(language, languageLeague->value(language).getScore());
}

QList<QString> LanguageDetector::removeNonProbableLanguages(QList<QString> languageList, int margin) {
    QString mostProbableLanguage = languageList.at(0);
    for(int i = 0; i < languageList.size(); i++) {
        QString language = languageList.at(i);
        if(languageScoreMap->value(language) < languageScoreMap->value(mostProbableLanguage)) {
            mostProbableLanguage = language;
        }
    }
    QList<QString> reducedlanguageList;
    for(int i = 0; i < languageList.size(); i++) {
        QString language = languageList.at(i);
        if(languageScoreMap->value(language) <= languageScoreMap->value(mostProbableLanguage) + margin*1000) {
            reducedlanguageList.append(language);
        }
    }
    return reducedlanguageList;
}

QString LanguageDetector::detectLanguage(QString inputStr){
    processInput(inputStr);
    init();
    int weight = 1;
    QList<int> occurenceList = inputWeightMap->uniqueKeys();
    QList<QString> languageList = languageScoreMap->keys();
    for(int i = occurenceList.size() - 1; i > -1; i--)  {
        QList<QString> sameWeightNGramList = inputWeightMap->values(occurenceList.at(i));

        for(int j = 0; j < sameWeightNGramList.size(); j++) {
            QString nGram = sameWeightNGramList[j];
            for(int k = 0; k < languageList.size(); k++) {
                QString language = languageList.at(k);
                updateScore(language, nGram, weight);
            }
            languageList = removeNonProbableLanguages(languageList, 3);
            if(languageList.size() == 1) {
                return languageList.at(0);
            }
        }
        weight++;
    }
    languageList = removeNonProbableLanguages(languageList, 0);
    return languageList.at(0);
}
