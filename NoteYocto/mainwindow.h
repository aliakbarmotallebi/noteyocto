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
    void allowUserToSave();
    void setFont(QString family, QFont::StyleHint styleHint, bool fixedPitch, int pointSize);
    void closeEvent(QCloseEvent *event);
    void setTabStopWidth(int width);
    const QString defaultWindowTitle = "Untitled document";


private:
    QString getFileNameFromPath(QString filePath);
    QFont font;
    int tabStopWidth;
    Ui::MainWindow *ui;
    QString currentFilePath;
    bool fileNeedsToBeSaved = true;


public slots:
    void actionSave_and_actionSaveAs();
    void textChanged();
    void actionNew();
    void actionOpen();
    void actionUndo();
    void actionRedo();
    void actionCut();
    void actionCopy();
    void actionPaste();
    void actionFind();
    void actionFindNext();
    void actionReplace();
    void actionGoTo();
    void actionSeleteAll();
    void actionExit();
    void actionPrint();

};

#endif // MAINWINDOW_H
