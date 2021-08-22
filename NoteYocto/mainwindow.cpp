#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resetEditor();
    setFont("Courier", QFont::Monospace, true, 10);
    setTabStopWidth(5);

    connect(ui->actionPrint, &QAction::triggered, this, &MainWindow::actionPrint);

    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::actionSave_and_actionSaveAs);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::actionSave_and_actionSaveAs);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTabStopWidth(int width)
{
    tabStopWidth = width;
    QFontMetrics metrics(font);
    ui->textEdit->setTabStopWidth((int)(tabStopWidth * metrics.width(' ')));
}

void MainWindow::setFont(QString family, QFont::StyleHint styleHint,
                       bool fixedPitch, int pointSize)
{
    font.setFamily(family);
    font.setStyleHint(styleHint);
    font.setFixedPitch(fixedPitch);
    font.setPointSize(pointSize);
    ui->textEdit->setFont(font);
}

void MainWindow::allowUserToSave()
{
    QMessageBox::StandardButton userSelection;

    userSelection = QMessageBox::question(this, "",
                          "Do you want to save the changes to " + getFileNameFromPath(currentFilePath) + "?",
                          QMessageBox::Yes | QMessageBox::No);

    if(userSelection == QMessageBox::Yes)
    {
        actionSave_and_actionSaveAs();
    }
}

void MainWindow::resetEditor()
{
    currentFilePath.clear();
    ui->textEdit->setText(QString());
    setWindowTitle(defaultWindowTitle);
    fileNeedsToBeSaved = false;
}

QString MainWindow::getFileNameFromPath(QString filePath){

    if(filePath.isEmpty()){
        return defaultWindowTitle;
    }

    int indexOfLastForwardSlash = filePath.lastIndexOf('/');
    QString fileName = filePath.mid(indexOfLastForwardSlash + 1, filePath.length() - indexOfLastForwardSlash);
    return fileName;
}

void MainWindow::actionNew()
{
    if(fileNeedsToBeSaved){
        allowUserToSave();
    }
    resetEditor();
}

void MainWindow::actionSave_and_actionSaveAs()
{
    // If user hit Save As or user hit Save but current document was never saved to disk
    bool saveAs = (sender() == ui->actionSave_As);

    if(saveAs || currentFilePath.isEmpty()){

        QString filePath = QFileDialog::getSaveFileName(this, "Save");

        if(filePath.isNull())
        {
            return;
        }
        currentFilePath = filePath;

    }

    QFile file(currentFilePath);
    if( ! file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(getFileNameFromPath(currentFilePath));

    QTextStream out(&file);

    QString content = ui->textEdit->toPlainText();
    out << content;
    file.close();

    fileNeedsToBeSaved = false;
}

void MainWindow::actionOpen()
{
    if(fileNeedsToBeSaved){
        allowUserToSave();
    }

    QString filePath = QFileDialog::getOpenFileName(this, "Open");
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(getFileNameFromPath(filePath));
    currentFilePath = filePath;

    QTextStream in(&file);
    QString content = in.readAll();

    ui->textEdit->setText(content);
    file.close();

    fileNeedsToBeSaved = false;
}

void MainWindow::actionUndo(){ ui->textEdit->undo(); }

void MainWindow::actionRedo(){ ui->textEdit->redo(); }

void MainWindow::actionCut(){ ui->textEdit->cut(); }

void MainWindow::actionCopy(){ ui->textEdit->copy(); }

void MainWindow::actionPaste(){ ui->textEdit->paste(); }

void MainWindow::actionFind(){ ui->textEdit->find(""); }

void MainWindow::actionFindNext(){}

void MainWindow::actionReplace(){}

void MainWindow::actionGoTo(){}

void MainWindow::actionSeleteAll(){}

void MainWindow::textChanged() { fileNeedsToBeSaved = true; }

void MainWindow::actionExit()
{
    if(fileNeedsToBeSaved)
    {
        allowUserToSave();
    }

    QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(fileNeedsToBeSaved)
      {
          event->ignore();
          allowUserToSave();
      }
      event->accept();
}

void MainWindow::actionPrint()
{
    QPrinter printer;
    printer.setPrinterName("Document");

    QPrintDialog printDialog(&printer, this);

    if(printDialog.exec() != QPrintDialog::Rejected)
       {
           ui->textEdit->print(&printer);
       }
}
