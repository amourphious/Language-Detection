#include "language_score_model.h"

double LanguageScoreModel::getScore() const
{
    return score;
}

void LanguageScoreModel::setScore(double value)
{
    score = value;
}

long LanguageScoreModel::getMatchedNGrams() const
{
    return matchedNGrams;
}

void LanguageScoreModel::setMatchedNGrams(long value)
{
    matchedNGrams = value;
}

training_text_map LanguageScoreModel::getLanguageMap() const
{
    return languageMap;
}

void LanguageScoreModel::setLanguageMap(const training_text_map &value)
{
    languageMap = value;
}

LanguageScoreModel::LanguageScoreModel()
{
    languageMap = training_text_map();
    init();
}

LanguageScoreModel::LanguageScoreModel(training_text_map ttmap) {
    languageMap = ttmap;
    init();
}

LanguageScoreModel::LanguageScoreModel(QString trainingText, QString languageName) {
    languageMap = training_text_map(trainingText, languageName);
    init();
}

void LanguageScoreModel::updateScore(QString nGram, int weight) {
    if(languageMap.getOccurence(nGram) > 0) {
        matchedNGrams++;
    }
    if(score == -1) {
        score = 0;
    }
    score = score + (weight*languageMap.getFrequency(nGram));
}

void LanguageScoreModel::init() {
    score = -1;
    matchedNGrams = 0;
}
