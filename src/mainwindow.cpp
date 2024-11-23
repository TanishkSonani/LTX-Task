#include "mainwindow.h"
#include <CsvParser.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QString buildDir = QDir::currentPath(); //cwd
    // qDebug() << buildDir;

    QDir dir(buildDir);
    dir.cdUp(); //build dir
    dir.cdUp(); //project dir
    QString projectDir = dir.absolutePath();
    QString filePath =  QDir(projectDir).filePath("data/NZ5_flightdatar.csv");

    // qDebug() << filePath;

    QFile CSVFile(filePath);
    if (CSVFile.open(QIODevice::ReadOnly))
    {
        QTextStream Stream(&CSVFile);
        while (Stream.atEnd() == false)
        {
            QString LineData = Stream.readLine();
            qDebug() << LineData;
        }
    }

    CSVFile.close();
}

MainWindow::~MainWindow() {}
