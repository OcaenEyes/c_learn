#include "linenumarea.h"
#include "editorcore.h"

LineNumArea::LineNumArea(EditorCore *editor):QWidget(editor)
{
    editorCore = editor;
}

QSize LineNumArea::sizeHint() const {
    return QSize(editorCore->lineNumAreaWidth(),0);
}

void LineNumArea::paintEvent(QPaintEvent *event){
    editorCore->lineNumAreaPaintEvent(event);
}
