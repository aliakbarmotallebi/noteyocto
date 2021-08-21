#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resetEditor();
    QMessageBox::StandardButton promptYesOrNo(QString title, QString prompt);
    const QString defaultWindowTitle = "Untitled document";


private:
    QString getFileNameFromPath(QString filePath);
    Ui::MainWindow *ui;
    QString currentFile;
    bool fileNeedsToBeSaved = true;


public slots:
    void actionNew();
    void actionSave();
    void actionOpen();
    void textChanged();
};

#endif // MAINWINDOW_H
