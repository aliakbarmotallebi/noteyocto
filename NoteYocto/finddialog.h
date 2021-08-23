#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();
    inline QString getQueryText(){ return queryText;}
     void clearLineEdit() { lineEdit->clear(); }

signals:
    void queryTextReady(QString queryText, bool findNext,
                        bool caseSensitive, bool wholeWords);

public slots:
    void on_findButton_clicked();
    void on_findNextButton_clicked();

private:
    QLabel *findLabel;
    QPushButton *findBtn;
    QPushButton *findNextBtn;
    QLineEdit *lineEdit;
    QCheckBox *caseSensitiveCheckBox;
    QCheckBox *wholeWordsCheckBox;
    QString queryText;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *optionsLayout;
    QVBoxLayout *verticalLayout;
};

#endif // FINDDIALOG_H
