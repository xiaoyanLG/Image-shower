#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->contain, SIGNAL(imagePath(QString)),
            this, SLOT(imageChange(QString)));

    connect(ui->contain, SIGNAL(loadedImage(QImage, QString)),
            this, SLOT(showImageInfo(QImage, QString)));

    ui->contain->setType(ui->comboBox->currentIndex());
    ui->show->setBorder(ui->checkBox->isChecked());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::imageChange(const QString &image)
{
    ui->imagepath->setText(image);
    ui->statusBar->showMessage(image);
}

void MainWindow::showImageInfo(const QImage &image, const QString &path)
{
    ui->show->imageChanged(image);
    ui->textEdit->append(QString("path: \t%1\nwidth: \t%2\nheight: \t%3\nformat: \t%4\n")
                         .arg(path)
                         .arg(image.width())
                         .arg(image.height())
                         .arg(image.format()));
}

void MainWindow::on_pushButton_3_clicked() // 打开文件
{
    QString image = QFileDialog::getOpenFileName(this);
    if (!image.isEmpty())
    {
        ui->imagepath->setText(image);
        ui->contain->loadImage(image,
                               ui->width->text().toInt(),
                               ui->height->text().toInt());
    }
}

void MainWindow::on_comboBox_activated(int index) // 图片格式改变
{
    ui->contain->setType(index + 1);
}

void MainWindow::on_pushButton_4_clicked() // 加载图片
{
    ui->contain->loadImage(ui->imagepath->text(),
                           ui->width->text().toInt(),
                           ui->height->text().toInt());
}

void MainWindow::on_pushButton_clicked() // 放大
{
    ui->show->zoomIn();
}

void MainWindow::on_pushButton_2_clicked()  // 缩小
{
    ui->show->zoomOut();
}

void MainWindow::on_checkBox_clicked(bool checked) // 是否显示边框
{
    ui->show->setBorder(checked);
}
