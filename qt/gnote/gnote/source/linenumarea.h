#ifndef LINENUMAREA_H
#define LINENUMAREA_H
#include <QWidget>


class EditorCore;

class LineNumArea:public QWidget
{
public:
    LineNumArea(EditorCore *editor);

    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    EditorCore * editorCore;
};

#endif // LINENUMAREA_H
