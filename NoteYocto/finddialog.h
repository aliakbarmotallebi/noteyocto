#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLineEdit>

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    inline QString getQueryText(){ return queryText;}
     void clearLineEdit() { lineEdit->clear(); }

signals:
    void queryTextReady(QString queryText);

public slots:
    void on_findButton_clicked();

private:
    QPushButton *findBtn;
    QLineEdit *lineEdit;
    QString queryText;
};

#endif // FINDDIALOG_H
