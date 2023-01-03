#include "markdowncore.h"
#include <QDebug>

MarkDownCore::MarkDownCore(QObject *parent)
    : QObject{parent}
{

}

QString MarkDownCore::markdown(){
    return _textIn;
}

void MarkDownCore::markdownIn(const QString &_text){
    if(_text == _textIn){
        return;
    }
    _textIn= _text;
    qDebug() << "有新的文本输入,内容是："<< _textIn << Qt::endl;
    emit hasMarkdownIn();
}
