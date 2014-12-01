#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QTime>
#include <QTimer>
#include <QStandardPaths>
#include <QProgressDialog>
#include <QMessageBox>
#include "filedialog.h"
#include "InvokeCLI.h"

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = 0);
    ~SecDialog();

    QTimer *countDown;
    int startMillionseconds;

    QStringList fileNames;
    QString folderName;
    EggBeater::InvokeCLI* invoke;

protected slots:
    void clock_time();

private slots:
    void on_refresh_button_clicked();
    void on_choose_input_files_clicked();
    void on_choose_output_folder_clicked();
    void on_encrypt_clicked();
    void on_decrypt_clicked();

private:
    Ui::SecDialog *ui;
    FileDialog *file_dlg;
    EggBeater::InvokeCLI *invoke;
};

#endif // SECDIALOG_H
