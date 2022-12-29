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

void MarkDownCore::fontDesign(){
    qDebug() << "设置字体样式" << Qt::endl;
}

void MarkDownCore::setFontBold(){
    qDebug() << "设置字体粗体" << Qt::endl;

}

void MarkDownCore::setFontItalic(){
    qDebug() << "设置字体斜体" << Qt::endl;

}

void MarkDownCore::setFontUnderLine(){
    qDebug() << "设置字体下划线" << Qt::endl;

}

void MarkDownCore::setFontLeftAlign(){
    qDebug() << "设置字体左对齐" << Qt::endl;

}

void MarkDownCore::setFontCenterAlign(){
    qDebug() << "设置字体中对齐" << Qt::endl;

}

void MarkDownCore::setFontRightAlign(){
    qDebug() << "设置字体右对齐" << Qt::endl;
}
