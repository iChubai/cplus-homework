#include "introduction.h"
#include "config.h"
#include "ui_introduction.h"
#include <QFontDatabase>

Introduction::Introduction(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Introduction)
{
    ui->setupUi(this);

    setWindowTitle("Game Description");
    setWindowIcon(QIcon(GAME_Icon));
    setWindowIconText("Dinosaur");
    int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/res/hk4e_zh-cn.ttf"));   //导入字体文件
    //QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    //font.setFamily(fontFamilies[0]);
    ui->label->setFont(font);
    ui->label_4->setFont(font);
    ui->label_5->setFont(font);
    ui->label_6->setFont(font);
    ui->label_7->setFont(font);
    ui->label_8->setFont(font);
    ui->label_9->setFont(font);
}

Introduction::~Introduction()
{
    delete ui;
}
