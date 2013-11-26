#ifndef TRAINING_TEXT_MAP_H
#define TRAINING_TEXT_MAP_H

#include <QString>
#include <QMap>
#include <QList>
#include <QStringList>

class TrainingTextMap
{
    QString languageName;
    QMap <QString, int> TTMap;

public:
    QList<int> nGramCount;
    int matchedNGram, freq;

    TrainingTextMap();

    void createTTMap(QString trainingText);

    void setLanguageName(QString name){
        languageName = name;
    }

    QString getLanguageName(){
        return languageName;
    }

    QString getKey(int value){
        return TTMap.key(value, "@");
    }

    int getValue(QString key){
        return TTMap.value(key, -1);
    }

    QStringList getKeys(){
        return TTMap.keys();
    }

    QString extractMaxNGram(int freq);

    void add(QString key, int value){
        TTMap[key] = value;
    }
};

#endif // TRAINING_TEXT_MAP_H
