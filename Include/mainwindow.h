#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "FlightData.h"
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <Qlabel>
#include <QtCore>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

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
    std::vector<FlightData> sortedData;
    QTableView  *dataView;
    QPushButton *LoadButton;
    QPushButton *SortButton;
    QPushButton *JsonButton;
    QPushButton *DBButton;
    QLabel      *StatusLabel;
    QSqlDatabase DB_Con;
};
#endif // MAINWINDOW_H
