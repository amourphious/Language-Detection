#include <QCoreApplication>

#include "training_text_map.h"
#include <iostream>
#include <stdio.h>
#include <QDir>
#include <QFile>
#include <QDebug>

QString findLang(TrainingTextMap input, QList<TrainingTextMap> trainingData, QString str, int margin = 3){

    int startSize = trainingData.size();
    /*qDebug()<<trainingData.size()<<":"<<input.nGramCount.size();
    for(int i = 0 ; i < trainingData.size(); i++)
        qDebug()<<trainingData[i].getLanguageName();
*/
    if(trainingData.size() != 1){

        if(input.nGramCount.size() == 0 && trainingData.size() > 1){
            TrainingTextMap tempInput;
            tempInput.createTTMap(str);
            QStringList keys = tempInput.getKeys();
            float maxFreq = 0.000;
            for(int i = 0; i < keys.size() && trainingData.size() > 1; i++){
                QString key = keys.at(i);
                qDebug()<<key;
                for(int j = 0; j < trainingData.size(); j++){
                    qDebug()<<key<<" "<<trainingData[j].getLanguageName()<<" - "<<trainingData[j].getValue(key);
                    if(maxFreq < trainingData[j].getValue(key)){
                        maxFreq = trainingData[j].getValue(key);
                        qDebug()<<maxFreq<<" : "<<trainingData[j].getLanguageName();
                    }
                }
                for(int k = 0; k < trainingData.size(); k++){
                    qDebug()<<trainingData[k].getLanguageName();
                    if(trainingData[k].getValue(key) < maxFreq ){
                        qDebug()<<"removing: "<<trainingData[k].getLanguageName();
                        trainingData.removeAt(k);
                        k--;
                    }
                }
                for(int x = 0 ; x < trainingData.size(); x++)
                    qDebug()<<trainingData[i].getLanguageName();

            }
            if(trainingData.size() == 1)
                return trainingData[0].getLanguageName();
            else
                return "unknown";
        }
        else{

            if ( trainingData.size() != 0 ){
                int freq = input.nGramCount.at(0);
                QString key = input.extractMaxNGram(freq);
                //qDebug()<<key;

                if(key == "@"){
                    input.nGramCount.removeAt(0);
                    return findLang(input, trainingData, str, margin);
                }
                else{
                    int maxMatch = 0;
                    for(int i = 0; i < trainingData.size(); i++){
                        TrainingTextMap tmp = trainingData.at(i);
                        int fr = tmp.getValue(key);
                        if(fr != -1)
                            trainingData[i].matchedNGram++;
                        if(maxMatch < trainingData.at(i).matchedNGram)
                            maxMatch = trainingData.at(i).matchedNGram;
                    }
                    for(int i = 0; i < trainingData.size(); i++){
                        if(trainingData.at(i).matchedNGram + margin < maxMatch){
                            trainingData.removeAt(i);
                            i--;
                        }
                    }
                    if(startSize == trainingData.size() && margin > 0){
                        margin--;
                        input.add(key, freq);
                    }
                    return findLang(input, trainingData, str, margin);
                }
            }
            else
                return "unknown";
        }
    }
    else
        return trainingData[0].getLanguageName();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QDir langdata;
    QString path = langdata.currentPath();
    qDebug()<<path;
    langdata.setPath(path + "/langdata");
    QStringList l = langdata.entryList();
    qDebug()<< l;
    QList<TrainingTextMap> trainingData;
    QString content;
    for( int i = 2; i < l.size(); i++ ){
        TrainingTextMap temp;
        QFile currentLang(langdata.filePath(l.at(i)));
        temp.setLanguageName(l.at(i));
        if (!currentLang.open(QIODevice::ReadOnly | QIODevice::Text))
                 return 1;
        else{
            content = currentLang.readAll();
            content.replace("\n"," ");
            temp.createTTMap(content);
            trainingData << temp;
        }
    }
    char str[10000];
    while(gets(str)){
        if (str[0] == '@')
            break;
        TrainingTextMap input;
        input.createTTMap(str);
        for(int i = 0; i < trainingData.size(); i++){
            trainingData[i].matchedNGram = 0;
        }
        QString lng = findLang(input, trainingData, str);
        qDebug()<<"detected Language: "<<lng;
        qDebug()<<"Press @ to exit";
    }
    return a.exec();
}
