#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

QString GetRandomString(int randomStringLength, bool upperCase = true, bool lowerCase = true, bool numbers = true)
{
#if 0
    return "<random>";
#else
    QString sNumbers("0123456789");
    QString sUppercase("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    QString sLowercase("abcdefghijklmnopqrstuvwxyz");

    QString possibleCharacters("");

    if (upperCase)
    {
        possibleCharacters += sUppercase;
    }
    if (lowerCase)
    {
        possibleCharacters += sLowercase;
    }
    if (numbers)
    {
        possibleCharacters += sNumbers;
    }

    QString randomString;
    for(int i=0; i<randomStringLength; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
#endif
}




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(onTimer()));
    mTimer->start(1000);

    qsrand(123);
}

void MainWindow::onTimer()
{
    static int i = 0;

    for (int k = 0; k < ui->spinBox->value(); k++)
    {
        NLog::it().msg(QString("[%1]. tick - random data :" + GetRandomString(64)).arg(++i));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    NLog::it().init();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{    
    NLog::it().shutdown();
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}
