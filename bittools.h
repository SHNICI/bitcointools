#ifndef BITTOOLS_H
#define BITTOOLS_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

namespace Ui {
class BitTools;
}

class BitTools : public QMainWindow
{
    Q_OBJECT

public:
    explicit BitTools(QWidget *parent = 0);
    ~BitTools();

public slots:
    void load(float amount=0);
    void replyFinished(QNetworkReply* reply, float amount=0);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QNetworkAccessManager* manager;
    Ui::BitTools *ui;
};


#endif // BITTOOLS_H
