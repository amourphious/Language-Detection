#ifndef LANGUAGESCOREMODEL_H
#define LANGUAGESCOREMODEL_H

#include "training_text_map.h"


class LanguageScoreModel
{
private:
    double score;
    long matchedNGrams;
    training_text_map languageMap;
public:
    LanguageScoreModel();
    LanguageScoreModel(training_text_map ttmap);
    LanguageScoreModel(QString trainingText, QString languageName);
    void init();
    double getScore() const;
    void setScore(double value);
    long getMatchedNGrams() const;
    void setMatchedNGrams(long value);
    training_text_map getLanguageMap() const;
    void setLanguageMap(const training_text_map &value);

    void updateScore(QString nGram, int weight);
};

#endif // LANGUAGESCOREMODEL_H
