#ifndef EDITORCORE_H
#define EDITORCORE_H

#include <QPlainTextEdit>

#include "linenumarea.h"

class EditorCore :public QPlainTextEdit
{
    Q_OBJECT
public:
    EditorCore(QWidget *parent = nullptr);

    void lineNumAreaPaintEvent(QPaintEvent *event);

    int lineNumAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumAreaWidth(int newBlockCount);
    void highLightCurrentLine();
    void updateLineNunArea(const QRect &rect, int dy);

private:
    LineNumArea *lineNumArea;
};

#endif // EDITORCORE_H
