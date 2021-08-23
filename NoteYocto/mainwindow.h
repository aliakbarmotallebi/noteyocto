#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "finddialog.h"

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
    FindDialog *findDialog;


private:
    QString getFileNameFromPath(QString filePath);
    QFont font;
    int tabStopWidth;
    Ui::MainWindow *ui;
    QString currentFilePath;
    bool fileNeedsToBeSaved = true;
    int positionOfLastFindMatch;


public slots:
    void actionSave_and_actionSaveAs();
    void on_textEdit_textChanged();
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionFind_triggered();
    void on_actionReplace_triggered();
    void on_actionGoTo_triggered();
    void on_actionSeleteAll_triggered();
    void on_actionExit_triggered();
    void on_actionPrint_triggered();
    void on_findQueryText_ready(QString queryText, bool findNext,
                                bool caseSensitive, bool wholeWords);

};

#endif // MAINWINDOW_H
