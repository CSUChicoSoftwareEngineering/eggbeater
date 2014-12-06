#ifndef SELECTCIPHER_H
#define SELECTCIPHER_H

#include <QDialog>
#include <QPushButton>
#include <QRadioButton>
#include <QString>

namespace Ui {
class selectCipher;
}

class selectCipher : public QDialog
{
    Q_OBJECT

public:
    explicit selectCipher(QWidget *parent = 0);
    ~selectCipher();
    QString getCipherMode();
    void resetRadioButtons();

private slots:
    void on_CFB_Button_clicked();
    void on_OFB_Button_clicked();
    void on_GCM_Button_clicked();
    void on_OK_Button_clicked();

private:
    Ui::selectCipher *ui;
    QString cipherMode;
};

#endif // SELECTCIPHER_H