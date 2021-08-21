#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(defaultWindowTitle);
}

MainWindow::~MainWindow()
{
    delete ui;
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
        QMessageBox::standardButton userSelection;
        userSelection = QMessageBox::question(this, "Text Editor",
                              "Do you want to save the changes to " + getFileNameFromPath(currentFile) + "?",
                              QMessageBox::Yes | QMessageBox::No);

        if(userSelection == QMessageBox::Yes)
        {
            actionSave();
        }
    }

    currentFile.clear();
    ui->textEdit->setText(QString());
    setWindowTitle(defaultWindowTitle);

}

void MainWindow::actionSave()
{
    QString filePath;

    if(currentFile.isEmpty()){
        filePath = QFileDialog::getSaveFileName(this, "Save");
        currentFile = filePath;
    }else{
        filePath = currentFile;
    }


    QFile file(filePath);
    if( ! file.open(QIODevice::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(getFileNameFromPath(filePath));

    QTextStream out(&file);

    QString content = ui->textEdit->toPlainText();
    out << content;
    file.close();

    fileNeedsToBeSaved = false;
}

void MainWindow::actionOpen()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open");
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    setWindowTitle(getFileNameFromPath(filePath));
    currentFile = filePath;

    QTextStream in(&file);
    QString content = in.readAll();

    ui->textEdit->setText(content);
    file.close();

    fileNeedsToBeSaved = false;
}


void MainWindow::textChanged() { fileNeedsToBeSaved = true; }
