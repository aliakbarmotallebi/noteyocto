#include "finddialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent)
{
    QLabel *findLabel = new QLabel(tr("Find What:"));

    lineEdit = new QLineEdit;

    findBtn = new QPushButton(tr("&Find"));

    queryText = "";

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(findLabel);
    layout->addWidget(lineEdit);
    layout->addWidget(findBtn);

    setLayout(layout);
    setWindowTitle(tr("Find"));

    connect(findBtn, SIGNAL(clicked()), this, SLOT(on_findButton_clicked()));

}

void FindDialog::on_findButton_clicked()
{
    QString query = lineEdit->text();

    if(query.isEmpty()){
        QMessageBox::information(this, tr("Empty Field"), tr("Please enter a query."));
        return;
    }

    queryText = query;

    emit(queryTextReady(queryText));
}
