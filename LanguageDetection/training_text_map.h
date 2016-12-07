#ifndef TRAINING_TEXT_MAP_H
#define TRAINING_TEXT_MAP_H

#include <QString>
#include <QMap>
#include <QList>
#include <QStringList>
#include <QDebug>
#include <QPair>
#include <QtMath>

class training_text_map
{
private:
    QMap<QString, QPair<long, double>> trainingMap;
    long size;
    QString languageName;
    double calculateFrequency(int occurence, int total);
public:
    training_text_map();
    training_text_map(QString trainingText);
    training_text_map(QString trainingText, QString language);

    long getOccurence(QString nGram) {
        if (trainingMap.contains(nGram)) {
            return trainingMap[nGram].first;
        }
        return -1;
    }

    double getFrequency(QString nGram) {
        if (trainingMap.contains(nGram)) {
            return trainingMap[nGram].second;
        }
        return 1000;
    }

    QList<QString> getUniqueNGrams() {
        return trainingMap.keys();
    }

    QString getLanguageName() {
        return languageName;
    }

    void setlanguageName(QString language) {
        languageName = language;
    }

    long getSize() const;
    void setSize(long value);
    void refreshTrainingMap(QString inputString);
};

#endif // TRAINING_TEXT_MAP_H
