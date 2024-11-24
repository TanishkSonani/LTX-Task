#include "mainwindow.h"
#include "FlightData.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStandardItem>
#include <QStandardItemModel>

std::vector<FlightData> parseCSV(const QString& filePath)
{
    std::vector<FlightData> flightDataList;
    QFile CSVFile(filePath);

    if(!CSVFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open file:" << filePath;
        return flightDataList;
    }

    QTextStream Stream(&CSVFile);

    QString header = Stream.readLine(); //skipped header line
    // qDebug() << "Header:" << header;

    while (!Stream.atEnd())
    {
        QString line = Stream.readLine();
        QStringList columns;
        if(line.contains(","))
            columns = line.split(",");
        else
        {
            qDebug() << "Invalid line format: " << line;
            continue;
        }

        // qDebug() << "Number of columns:" << columns.size();
        // qDebug() << "Raw line:" << line;

        if (columns.size() == 8)
        {
            for(QString& col : columns)
            {
                col = col.trimmed();
            }

            try
            {
                QString time         = columns[0];
                double  latitude     = columns[1].toDouble();
                double  longitude    = columns[2].toDouble();
                int     course       = columns[3].toInt();
                int     kts          = columns[4].isEmpty() ? 0 : columns[4].toInt();
                int     mph          = columns[5].isEmpty() ? 0 : columns[5].toInt();
                int     altitudeFeet = columns[6].toInt();
                QString facility     = columns[7];

                QTime parsedTime = QTime::fromString(time, "h:mm:ss AP");
                if(!parsedTime.isValid())
                {
                    qDebug() << "Time kharab chal rha hai" << time;
                    continue;
                }

                // qDebug() << "Pased values:";
                // qDebug() << "Time:"     << time
                //          << "Lat:"      << latitude
                //          << "Long:"     << longitude
                //          << "Course:"   << course
                //          << "Kts:"      << kts
                //          << "Mph:"      << mph
                //          << "Alt:"      << altitudeFeet
                //          << "Facility:" << facility;

                flightDataList.emplace_back
                    (
                        parsedTime.toString("hh:mm:ss AP"), latitude, longitude, course,
                        kts, mph, altitudeFeet, facility
                        );
            }
            catch (const std::exception & e)
            {
                qDebug() << "Invalid number of columns:" << columns.size();
                qDebug() << "Line" << line;
            }
        }
    }
    CSVFile.close();
    qDebug() << "Total records parsed:" << flightDataList.size();
    return flightDataList;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle("Flight Data Viewer");
    setGeometry(100,100,800,100);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    LoadButton = new QPushButton("Load", this);
    LoadButton -> setMinimumSize(50,50);

    SortButton = new QPushButton("Sort", this);
    SortButton -> setMinimumSize(50,50);

    JsonButton = new QPushButton("JSON", this);
    JsonButton -> setMinimumSize(50,50);

    DBButton   = new QPushButton("Database", this);
    DBButton -> setMinimumSize(50,50);

    buttonLayout -> addWidget(LoadButton);
    buttonLayout -> addWidget(SortButton);
    buttonLayout -> addWidget(JsonButton);
    buttonLayout -> addWidget(DBButton);

    mainLayout -> addLayout(buttonLayout);

    dataView = new QTableView(this);
    mainLayout -> addWidget(dataView);

    JsonLabel = new QLabel(this);
    JsonLabel->setAlignment(Qt::AlignCenter);
    JsonLabel->setStyleSheet("font-weight: bold; color: green;");
    mainLayout->addWidget(JsonLabel);

    setCentralWidget(centralWidget);

    connect(LoadButton, &QPushButton::clicked, this, &MainWindow::LoadData);
    connect(SortButton, &QPushButton::clicked, this, &MainWindow::SortData);
    connect(JsonButton, &QPushButton::clicked, this, &MainWindow::GenJson);
    connect(DBButton,   &QPushButton::clicked, this, &MainWindow::LoadDB);

    QString buildDir = QDir::currentPath(); //cwd
    // qDebug() << buildDir;

    QDir dir(buildDir);
    dir.cdUp(); //build dir
    dir.cdUp(); //project dir
    QString projectDir = dir.absolutePath();
    QString filePath =  QDir(projectDir).filePath("data/NZ5_flightdatar.csv");
    // qDebug() << filePath;

    data = parseCSV(filePath);

    // for(const auto row: data)
    // {
    //     qDebug()  << "Time: "         << row.Time.toString("hh:mm:ss").toStdString() << " ,"
    //               << "Latitude: "     << row.Latitude                                << " ,"
    //               << "Longitude: "    << row.Longitude                               << " ,"
    //               << "Course: "       << row.Course                                  << " ,"
    //               << "Kts: "          << row.kts                                     << " ,"
    //               << "Mph: "          << row.mph                                     << " ,"
    //               << "AltitudeFeet: " << row.AltitudeFeet                            << " ,"
    //               << "Facility: "     << row.ReportingFacility.toStdString()         << '\n';
    // }

    sortedData = data;
    std::sort(sortedData.begin(), sortedData.end(), [](const FlightData& a, const FlightData& b) {
        return a.Time < b.Time;
    });

}

MainWindow::~MainWindow() {}

void MainWindow::LoadData()
{
    JsonLabel->clear();
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(8);

    model->setHorizontalHeaderLabels({"Time", "Latitude", "Longitude", "Course", "Kts", "Mph", "Altitude", "Facility"});

    for (const auto& flight : data)
    {
        QList<QStandardItem*> row;
        row.append(new QStandardItem(flight.Time.toString("h:mm:ss AP")));
        row.append(new QStandardItem(QString::number(flight.Latitude)));
        row.append(new QStandardItem(QString::number(flight.Longitude)));
        row.append(new QStandardItem(QString::number(flight.Course)));
        row.append(new QStandardItem(QString::number(flight.kts)));
        row.append(new QStandardItem(QString::number(flight.mph)));
        row.append(new QStandardItem(QString::number(flight.AltitudeFeet)));
        row.append(new QStandardItem(flight.ReportingFacility));
        model->appendRow(row);
    }

    dataView->setModel(model);

    dataView->resizeColumnsToContents();

    // QSize tableSize = dataView->viewport()->size();
    // static int tableWidge  = tableSize.width();
    // static int tableHeight = tableSize.height();
    // qDebug() << "Width:" << tableWidge << " Height:" << tableHeight;
    setGeometry(100, 100, 850, 550);
}

void MainWindow::SortData()
{
    JsonLabel->clear();
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(8);

    model->setHorizontalHeaderLabels({"Time", "Latitude", "Longitude", "Course", "Kts", "Mph", "Altitude", "Facility"});

    for (const auto& flight : sortedData)
    {
        QList<QStandardItem*> row;
        row.append(new QStandardItem(flight.Time.toString("h:mm:ss AP")));
        row.append(new QStandardItem(QString::number(flight.Latitude)));
        row.append(new QStandardItem(QString::number(flight.Longitude)));
        row.append(new QStandardItem(QString::number(flight.Course)));
        row.append(new QStandardItem(QString::number(flight.kts)));
        row.append(new QStandardItem(QString::number(flight.mph)));
        row.append(new QStandardItem(QString::number(flight.AltitudeFeet)));
        row.append(new QStandardItem(flight.ReportingFacility));
        model->appendRow(row);
    }

    dataView->setModel(model);

    dataView->resizeColumnsToContents();

    // QSize tableSize = dataView->viewport()->size();
    // static int tableWidge  = tableSize.width();
    // static int tableHeight = tableSize.height();
    setGeometry(100, 100, 850, 550);
}

void MainWindow::GenJson()
{
    QJsonArray jsonArray;
    int count = 0;

    for(const auto& flight: sortedData)
    {
        QJsonObject flightObject;
        flightObject["RowNo"]     = ++count;
        flightObject["Time"]      = flight.Time.toString("h:mm:ss AP");
        flightObject["Latitude"]  = flight.Latitude;
        flightObject["Longitude"] = flight.Longitude;
        flightObject["Course"]    = flight.Course;
        flightObject["Kts"]       = flight.kts;
        flightObject["Mph"]       = flight.mph;
        flightObject["Altitude"]  = flight.AltitudeFeet;
        flightObject["Facility"]  = flight.ReportingFacility;

        jsonArray.append(flightObject);
    }

    QJsonDocument jsonDoc(jsonArray);  //array to JsonDoc
    QString jsonString = jsonDoc.toJson(QJsonDocument::Indented); //string of JsonDoc

    QString buildDir = QDir::currentPath(); //cwd
    // qDebug() << buildDir;
    QDir dir(buildDir);
    dir.cdUp(); //build dir
    dir.cdUp(); //project dir
    QString projectDir = dir.absolutePath();
    QString JsonPath = projectDir + "/data/GeneratedJson/FlightData.json";
    // qDebug() << JsonPath;
    QFile jsonFile(JsonPath); //JsonFile save

    if (jsonFile.exists())
    {
        JsonLabel->setText("File already exists: " + JsonPath);
        JsonLabel->setStyleSheet("font-weight: bold; color: orange;");
        return;
    }

    if (jsonFile.open(QIODevice::WriteOnly))
    {
        jsonFile.write(jsonString.toUtf8());
        jsonFile.close();
        // qDebug() << "JSON File Saved!!";
        JsonLabel ->setText("Json file saved succesfully at " + JsonPath);
        JsonLabel ->setStyleSheet("font-weight: bold; color:green;");
    }
    else
    {
        // qDebug() << "Failed to save JSON file.";
        JsonLabel -> setText("Failed to save JSON file");
        JsonLabel -> setStyleSheet("font-weight:bold; color:red;");
    }
}

void MainWindow::LoadDB()
{
    qDebug() << "Load Database button clicked!";
}
