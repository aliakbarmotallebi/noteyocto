#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    const QString defaultWindowTitle = "Untitled document";

private:
    Ui::MainWindow *ui;
    QString currentFile;

    bool fileNeedsToBeSaved = true;

    inline QString getFileNameFromPath(QString filePath);

public slots:
    void actionNew();
    void actionSave();
    void actionOpen();
    void textChanged();
};

#endif // MAINWINDOW_H
