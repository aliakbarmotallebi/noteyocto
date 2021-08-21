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
    ui->textEdit->setTabStopWidth(tabStopWidth * metrics.width(' '));
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

QMessageBox::StandardButton  MainWindow::promptYesOrNo(QString title, QString prompt)
{
    return QMessageBox::question(this, title, prompt, QMessageBox::Yes | QMessageBox::No);
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

        QMessageBox::StandardButton userSelection;
        userSelection = promptYesOrNo("", "Do you want to save the changes to " + getFileNameFromPath(currentFilePath) + "?");

        if(userSelection == QMessageBox::Yes)
        {
            actionSave();
        }
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


void MainWindow::textChanged() { fileNeedsToBeSaved = true; }
