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
    void setFont(QString family, QFont::StyleHint styleHint, bool fixedPitch, int pointSize);
    void setTabStopWidth(int width);
    const QString defaultWindowTitle = "Untitled document";


private:
    QString getFileNameFromPath(QString filePath);
    QFont font;
    int tabStopWidth;
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
