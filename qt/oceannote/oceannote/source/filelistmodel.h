#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QObject>
#include <QFileDialog>

class FileListModel : public QObject
{
    Q_OBJECT
public:
    explicit FileListModel(QObject *parent = nullptr);

public slots:
    void saveFile();
    void ceateFile();
    void saveAsFile();
    void openFile();
    void openFolder();
    void openNewWindow();

private:
    QString showFileDialog(QFileDialog::AcceptMode _mode,QFileDialog::FileMode _type);

signals:

};

#endif // FILELISTMODEL_H
