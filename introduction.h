#pragma once
#include <QDialog>

namespace Ui {
    class Introduction;
}

class Introduction : public QDialog
{
    Q_OBJECT

public:
    explicit Introduction(QWidget* parent = nullptr);
    ~Introduction();

private:
    Ui::Introduction* ui;
};

