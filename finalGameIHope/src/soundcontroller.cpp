#include "include/soundcontroller.h"
#include <QDebug>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QFile>


SoundController::SoundController(QObject *parent) {
    player = new QMediaPlayer();
    //audioOutput = new QAudioOutput(this);
    audioOutput = new QAudioOutput(parent);
    player->setAudioOutput(audioOutput);
}

void SoundController::playSound(const QString &filePath) {
    player->setSource(QUrl(filePath));
    player->play();
}

void SoundController::setVolume(int volume) {
    audioOutput->setVolume(volume / 100.0);
}

QMediaPlayer *SoundController::getMediaPlayer(){
    return player;
}
