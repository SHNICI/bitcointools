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
    void load();
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* manager;
    Ui::BitTools *ui;
};


#endif // BITTOOLS_H
