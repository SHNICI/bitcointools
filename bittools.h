#ifndef BITTOOLS_H
#define BITTOOLS_H

#include <QMainWindow>

namespace Ui {
class BitTools;
}

class BitTools : public QMainWindow
{
    Q_OBJECT

public:
    explicit BitTools(QWidget *parent = 0);
    ~BitTools();

private:
    Ui::BitTools *ui;
};

#endif // BITTOOLS_H
