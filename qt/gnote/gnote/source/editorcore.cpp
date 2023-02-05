#include "editorcore.h"
#include <QPainter>
#include <QTextBlock>


EditorCore::EditorCore(QWidget *parent): QPlainTextEdit(parent)
{
    lineNumArea = new LineNumArea(this);
    markDown = new Markdown();

    connect(this,&EditorCore::blockCountChanged,this,&EditorCore::updateLineNumAreaWidth);

    connect(this,&EditorCore::updateRequest,this,&EditorCore::updateLineNunArea);

    connect(this,&EditorCore::cursorPositionChanged,this,&EditorCore::highLightCurrentLine);

    updateLineNumAreaWidth(0);

    highLightCurrentLine();

}

int EditorCore::lineNumAreaWidth(){
    int digits = 1;
    int maxCount = qMax(1,blockCount());
    while (maxCount >= 10) {
        maxCount /=10;
        ++digits;
    }

    int space = 3+ fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    return space;
}

void EditorCore::updateLineNumAreaWidth(int i){
    setViewportMargins(lineNumAreaWidth(),0,0,0);
}

void EditorCore::updateLineNunArea(const QRect &rect,int dy){
    if(dy){
        lineNumArea->scroll(0,dy);
    }else {
        lineNumArea->update(0,rect.y(),lineNumArea->width(),rect.width());
    }

    if(rect.contains(viewport()->rect())){
        updateLineNumAreaWidth(0);
    }
}

void EditorCore::resizeEvent(QResizeEvent *event){
    QPlainTextEdit::resizeEvent(event);
    QRect rect = contentsRect();
    lineNumArea->setGeometry(QRect(rect.left(),rect.top(),lineNumAreaWidth(),rect.height()));
}

void EditorCore::highLightCurrentLine(){
    QList<QTextEdit::ExtraSelection> extraSelections;

    if(!isReadOnly()){
        QTextEdit::ExtraSelection selection;

//        QColor lineColor;
//        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection,true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);

    }

    setExtraSelections(extraSelections);
}


void EditorCore::lineNumAreaPaintEvent(QPaintEvent *event){
    QPainter painter(lineNumArea);
//    painter.fillRect(event->rect(),Qt::lightGray);

    QTextBlock block = firstVisibleBlock();

    int blockNum = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());


    while (block.isValid() && top <= event->rect().bottom()) {
        if(block.isVisible() && bottom >= event->rect().top()){
            QString number = QString::number(blockNum +1);
//            painter.setPen(Qt::black);
            painter.drawText(0,top,lineNumArea->width(),fontMetrics().height(),
                             Qt::AlignRight,number);
        }

        block = block.next();
        top = bottom;
        bottom = top +qRound(blockBoundingRect(block).height());
        ++blockNum;

    }
}

void EditorCore::textContent(){

}
