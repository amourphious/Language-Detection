#include "training_text_map.h"

#include <QString>
#include <QStringList>
#include <QtMath>

long training_text_map::getSize() const
{
    return size;
}

void training_text_map::setSize(long value)
{
    size = value;
}

training_text_map::training_text_map()
{
    languageName = "";
    size = 0;
}

double training_text_map::calculateFrequency(int occurence, int total) {
    return qLn(total) - qLn(occurence);
}

training_text_map::training_text_map(QString trainingText) {
    refreshTrainingMap(trainingText);
}

training_text_map::training_text_map(QString trainingText, QString language) : training_text_map(trainingText) {
    languageName = language;
}

void training_text_map::refreshTrainingMap(QString inputString) {
    QString punctuation = ",.?<>:;\"'!@#$%^&()-_\t\r";

    for(int i = 0; i < punctuation.size(); i++)
        inputString.replace(punctuation.at(i)," ");

    inputString.replace("\n"," ");
    inputString.simplified();

    QStringList tokens = inputString.split(' ',QString::SkipEmptyParts);

    for(int i = 0; i < tokens.size(); i++){
        QString token = tokens.at(i);
        if( !trainingMap.contains(token) ){
            trainingMap[token].first = 1;
            trainingMap[token].second = calculateFrequency(trainingMap[token].first, tokens.size());
        }
        else{

            trainingMap[token].first = trainingMap[token].first + 1;
            trainingMap[token].second = calculateFrequency(trainingMap[token].first, tokens.size());
        }
    }

    size = trainingMap.size();
}
