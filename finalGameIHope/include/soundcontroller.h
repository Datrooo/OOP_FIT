#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <QMediaPlayer>
#include <QAudioOutput>

class SoundController : public QObject {
    Q_OBJECT
public:
    SoundController(QObject *parent = nullptr);
    ~SoundController();
    void playSound(const QString &filePath);
    void setVolume(int volume);
    QMediaPlayer * getMediaPlayer();


private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
};



#endif // SOUNDCONTROLLER_H
