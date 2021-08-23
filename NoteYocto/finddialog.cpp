#include "finddialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent)
{
    QLabel *findLabel = new QLabel(tr("Find What:"));

    lineEdit = new QLineEdit;

    findBtn = new QPushButton(tr("&Find"));
    findNextBtn = new QPushButton(tr("&Find next"));

    queryText = "";

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(findLabel);
    layout->addWidget(lineEdit);
    layout->addWidget(findBtn);
    layout->addWidget(findNextBtn);

    setLayout(layout);
    setWindowTitle(tr("Find"));

    connect(findBtn, SIGNAL(clicked()), this, SLOT(on_findButton_clicked()));
    connect(findNextBtn, SIGNAL(clicked()), this, SLOT(on_findNextButton_clicked()));


}

void FindDialog::on_findButton_clicked()
{
    QString query = lineEdit->text();

    if(query.isEmpty()){
        QMessageBox::information(this, tr("Empty Field"), tr("Please enter a query."));
        return;
    }

    queryText = query;

    emit(queryTextReady(queryText, false));
}

void FindDialog::on_findNextButton_clicked()
{
    QString query = lineEdit->text();

    if(query.isEmpty()){
        QMessageBox::information(this, tr("Empty Field"), tr("Please enter a query."));
        return;
    }

    queryText = query;

    emit(queryTextReady(queryText, true));
}
