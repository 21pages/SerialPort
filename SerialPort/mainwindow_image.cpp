#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>



void MainWindow::Image_Init()
{
    //设定初始文件路径
    QString file_full = QCoreApplication::applicationFilePath();    //获取路径信息
    QFileInfo fi = QFileInfo(file_full);                            //建立文件信息对象
    file_path = fi.absolutePath();                                  //提取路径信息
    //显示文件路径
    ui->lineEdit_filepath->setText(file_path);
    //设定文件保存标志的初始值
    image_save_flag = 0;
    //保存图片用的计数变量清零
    image_counter=0;

    QString tmp;
    tmp.setNum(image_counter);
    ui->lineEdit_imagenunmber->setText(tmp);

    //初始化图像数组
    for(int i=0;i<Img_Size;i++)
    {
        imageByteArray[i] = i/45;
    }
    //显示imageByteArray中存储的图像
    DisplayImage();


    //测试用定时器
    QTimer *testTimer = new QTimer(this);    //创建定时器
    connect( testTimer,SIGNAL(timeout()), this, SLOT(testFunction()) ); //将定时器超时信号与槽(功能函数)联系起来
    testTimer->start(10); //开始运行定时器，定时时间间隔为1000ms

}

//测试用函数
void MainWindow::testFunction()
{
    for(int i=0;i<Img_Size;i++)
    {
        imageByteArray[i]++;
    }
    DisplayImage();
}

//按钮相应函数
void MainWindow::on_openimage_clicked()
{
    DisplayImage();
}

//将数组中的图像显示在屏幕上
void MainWindow::DisplayImage()
{
    //DisImage变换大小并存入imgScaled
    imgScaled = QImage(imageByteArray, Img_Width, Img_Height, QImage::Format_RGB888).scaled(ui->label_image->size(),Qt::KeepAspectRatio);
    ui->label_image->setPixmap(QPixmap::fromImage(imgScaled)); //显示变换大小后的QImage对象

    if(image_save_flag)
    {
        image_counter++;    //先加一，从第一张图开始数

        //生成文件名
        QString strtmp;
        strtmp.setNum(image_counter);
        QString filename = file_path + "/" + strtmp + ".JPG";

        //更新图片编号
        QString tmp;
        tmp.setNum(image_counter);
        ui->lineEdit_imagenunmber->setText(tmp);

        //保存图片
        QPixmap imgtmp = QPixmap::fromImage(imgScaled);
        imgtmp.save(filename,"bmp",100);
    }
}

//选择路径按钮
void MainWindow::on_pathchangeButton_clicked()
{
    QString file_path_tmp = QFileDialog::getExistingDirectory(this,"请选择数据保存文件夹","./");
    if(file_path_tmp.isEmpty())
    {
        return;
    }
    else
    {
        file_path = file_path_tmp;
        ui->lineEdit_filepath->setText(file_path);
    }
}

//保存图像复选框
void MainWindow::on_checkBox_imagesave_stateChanged(int arg1)
{
    image_save_flag = arg1;
}



//    //获取文件路径
//    QString filename;
//    filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
//    if(filename.isEmpty())
//    {
//         return;
//    }

//    //打开图片
//    QImage* img=new QImage;
//    if(! ( img->load(filename) ) ) //加载图像到QImage对象
//    {
//        QMessageBox::information(this,tr("打开图像失败"),tr("打开图像失败!"));
//        delete img;
//        return;
//    }
