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
    ui->textEdit->setText("");
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



void MainWindow::on_actionNew_triggered()
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

void MainWindow::on_actionOpen_triggered()
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
void MainWindow::on_actionUndo_triggered(){ ui->textEdit->undo(); }
void MainWindow::on_actionRedo_triggered(){ ui->textEdit->redo(); }
void MainWindow::on_actionCut_triggered(){ ui->textEdit->cut(); }
void MainWindow::on_actionCopy_triggered(){ ui->textEdit->copy(); }
void MainWindow::on_actionPaste_triggered(){ ui->textEdit->paste(); }
void MainWindow::on_actionFind_triggered(){ ui->textEdit->find(""); }
void MainWindow::on_actionFindNext_triggered(){}
void MainWindow::on_actionReplace_triggered(){}
void MainWindow::on_actionGoTo_triggered(){}
void MainWindow::on_actionSeleteAll_triggered(){}

void MainWindow::on_textEdit_textChanged() {

    fileNeedsToBeSaved = true;

    QString newWindowTitle = getFileNameFromPath(currentFilePath).append(" [Unsaved changes]");
    setWindowTitle(newWindowTitle);
}

void MainWindow::on_actionExit_triggered()
{
    if(fileNeedsToBeSaved)
    {
        allowUserToSave();
    }

    QApplication::quit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(! fileNeedsToBeSaved)
      {
         event->accept();
         return;
      }

    event->ignore();
    allowUserToSave();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Document");

    QPrintDialog printDialog(&printer, this);

    if(printDialog.exec() != QPrintDialog::Rejected)
       {
           ui->textEdit->print(&printer);
       }
}
