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
    findLabel = new QLabel(tr("Find What:"));

    lineEdit = new QLineEdit;

    findNextBtn = new QPushButton(tr("&Find next"));
    caseSensitiveCheckBox = new QCheckBox(tr("&Case Sensitive"));
    wholeWordsCheckBox = new QCheckBox(tr("&Whole Words"));

    queryText = "";


    horizontalLayout = new QHBoxLayout();
    optionsLayout = new QHBoxLayout();
    verticalLayout = new QVBoxLayout();


    verticalLayout->addLayout(horizontalLayout);
    verticalLayout->addLayout(optionsLayout);


    horizontalLayout->addWidget(findLabel);
    horizontalLayout->addWidget(lineEdit);
    horizontalLayout->addWidget(findNextBtn);

    optionsLayout->setSizeConstraint(QLayout::SetMaximumSize);
    optionsLayout->addWidget(caseSensitiveCheckBox);
    optionsLayout->addWidget(wholeWordsCheckBox);

    setLayout(verticalLayout);
    setWindowTitle(tr("Find"));

    connect(findNextBtn, SIGNAL(clicked()), this, SLOT(on_findNextButton_clicked()));


}

FindDialog::~FindDialog()
{
    delete findLabel;
    delete lineEdit;
    delete findNextBtn;
    delete caseSensitiveCheckBox;
    delete wholeWordsCheckBox;
    delete horizontalLayout;
    delete verticalLayout;
    delete optionsLayout;
}

void FindDialog::on_findNextButton_clicked()
{

    bool caseSensitive = caseSensitiveCheckBox->isChecked();
    bool wholeWords = wholeWordsCheckBox->isChecked();

    bool findNext = false;

    QString query = lineEdit->text();

    if(query.isEmpty()){
        QMessageBox::information(this, tr("Empty Field"), tr("Please enter a query."));
        return;
    }
    if(query ==  queryText){
        findNext = true;
    }

    queryText = query;

    emit(queryTextReady(queryText, findNext, caseSensitive, wholeWords));
}
