#include "training_text_map.h"

#include <QStringList>

TrainingTextMap::TrainingTextMap()
{
    matchedNGram = 0;
}

QString punctuation = ",.?<>:;\"'!@#$%^&()-_\t\r";

void TrainingTextMap::createTTMap(QString trainingText){
    for(int i = 0; i < punctuation.size(); i++)
        trainingText.remove(punctuation.at(i));

    QStringList tokens = trainingText.split(' ');

    for(int i = 0; i < tokens.size(); i++){
        QString temp = tokens.at(i);
        temp = temp.simplified();
        if( TTMap.value(temp, -1) == -1 ){
            //qDebug() << "adding key" << temp;
            TTMap[temp] = 1;
            //qDebug() << nGramFreqMap.value(temp);
        }
        else{
            TTMap[temp] = TTMap.value(temp)+ 1;
        }
    }

    QList <int> temp = TTMap.values();
    for(int i = 0 ;i < temp.size(); i++ ){

        if( !nGramCount.contains(temp.at(i)) )
            nGramCount << temp.at(i);
    }

    for(int i = 0; i < nGramCount.size(); i++){
        for(int j = i; j < nGramCount.size(); j++){
            if(nGramCount.at(i) < nGramCount.at(j)){
                int a = nGramCount.at(i), b = nGramCount.at(j);
                int tempn = a;
                nGramCount[i] = b;
                nGramCount[j] = tempn;
            }
        }
    }
}


QString TrainingTextMap::extractMaxNGram(int freq){
    QString ans = getKey(freq);
    if(ans != "@")
        TTMap.remove(ans);
    return ans;
}
