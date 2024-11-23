#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FlightData.h"
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QtCore>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void LoadData();
    void SortData();
    void GenJson();
    void LoadDB();

private:
    std::vector<FlightData> data;
    QTableView  *dataView;
    QPushButton *LoadButton;
    QPushButton *SortButton;
    QPushButton *JsonButton;
    QPushButton *DBButton;
};
#endif // MAINWINDOW_H
