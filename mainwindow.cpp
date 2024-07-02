/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QFileDialog>
#include <cmath>

double vol_value_1_current = 0;
double vol_value_2_current = 0;
QVector<double> buffer_serial(25000);
int receiverCount = 0;
int RepeatTimes = 0;
int step = 0;
int numStep = 0;
int current_step = 0;
int start_vol_cv = 0;
int end_vol_cv = 0;
int gap_cv_meansure = 0;
QTimer responseTimer;
QTimer Timer_check_config;
QTimer Timer_check_qc;

void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
QCPCurve *curveMagnitude = NULL;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _serialPort(nullptr)
{
    setMouseTracking(true); // Bật theo dõi chuột
    QFont font = QApplication::font();
    font.setPointSize(8);
    QApplication::setFont(font);
    ui->setupUi(this);
    m_client = new QMqttClient(this);
    m_client->setHostname("iotbro.hopto.org");
    m_client->setUsername("admin");
    m_client->setPassword("iotiotiot");

    m_client->setPort(1883);
    connect(m_client, &QMqttClient::connected, this, &MainWindow::onConnected);
    connect(m_client, &QMqttClient::errorChanged, this, &MainWindow::onError);
    connect(m_client, &QMqttClient::messageReceived, this, &onMessageReceived);
    m_client->connectToHost();
    loadPort();

    ui->char_line_eis->addGraph();
    ui->char_line_eis->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->char_line_eis->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->char_line_eis->graph(0)->setName("Magnitude");
    ui->char_line_eis->graph(0)->setPen(QPen(QColor(255, 0, 0)));
    ui->char_line_eis->legend->setIconSize(10, 10);
    QObject::connect(ui->char_line_eis, &QCustomPlot::legendClick, this, &MainWindow::handleLegendClick);
    ui->char_line_eis->addGraph();
    ui->char_line_eis->yAxis2->setVisible(true);
    ui->char_line_eis->yAxis2->setTickLabels(true);
    ui->char_line_eis->graph(1)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->char_line_eis->graph(1)->setLineStyle(QCPGraph::lsLine);
    ui->char_line_eis->graph(1)->setName("Phase");
    ui->char_line_eis->graph(1)->setPen(QPen(QColor(0, 0, 255)));
    ui->char_line_eis->graph(1)->setValueAxis(ui->char_line_eis->yAxis2);
    // Thiết lập tiêu đề cho đồ thị
    ui->char_line_eis->plotLayout()->insertRow(0); // Thêm một hàng mới vào đầu layout
    QCPTextElement *title_eis = new QCPTextElement(ui->char_line_eis, "Electrochemical Impedance Spectroscopy", QFont("sans", 10, QFont::Bold));
    ui->char_line_eis->plotLayout()->addElement(0, 0, title_eis); // Thêm tiêu đề vào hàng mới
    ui->char_line_eis->legend->setVisible(true);
    ui->char_line_eis->legend->setFont(QFont("Helvetica", 9));
    ui->char_line_eis->legend->setTextColor(QColor(0, 0, 0));
    ui->char_line_eis->xAxis->setLabel("Times (ms)");
    ui->char_line_eis->yAxis->setLabel("Magnitude (Ohm)");
    ui->char_line_eis->yAxis->setLabelColor(QColor(255, 0, 0));
    ui->char_line_eis->yAxis2->setLabel("Phase (Degree)");
    ui->char_line_eis->yAxis2->setLabelColor(QColor(0, 0, 255));
    ui->char_line_eis->xAxis->setRange(-1, 50);
    ui->char_line_eis->yAxis->setRange(-1, 50);
    ui->char_line_eis->yAxis2->setRange(-1, 100);
    ui->char_line_eis->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    timer_init(10, SLOT(timerTick()));

    // Khởi tạo QCPCurve mới cho 'Magnitude'
    curveMagnitude = new QCPCurve(ui->char_line_cv->xAxis, ui->char_line_cv->yAxis);
    curveMagnitude->setScatterStyle(QCPScatterStyle::ssCircle);
    curveMagnitude->setLineStyle(QCPCurve::lsLine);
    curveMagnitude->setName("Magnitude");
    curveMagnitude->setPen(QPen(QColor(255, 0, 0)));

    // Thiết lập tiêu đề cho đồ thị
    ui->char_line_cv->plotLayout()->insertRow(0);
    QCPTextElement *title_cv = new QCPTextElement(ui->char_line_cv, "Cylic Voltammetry", QFont("sans", 10, QFont::Bold));
    ui->char_line_cv->plotLayout()->addElement(0, 0, title_cv);

    // Thiết lập các nhãn và phạm vi cho trục
    ui->char_line_cv->xAxis->setLabel("Voltage (mV)");
    ui->char_line_cv->yAxis->setLabel("Current (uA)");
    ui->char_line_cv->yAxis->setLabelColor(QColor(255, 0, 0));
    ui->char_line_cv->xAxis->setRange(-1, 50);
    ui->char_line_cv->yAxis->setRange(-1, 50);
    ui->char_line_cv->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    qDebug() << "X:" << x << "Y:" << y;
}


void MainWindow::handleLegendClick(QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event) {
    auto plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    if (plItem) {
        QCPGraph* graph = qobject_cast<QCPGraph*>(plItem->plottable());
        graph->setVisible(!graph->visible());
        ui->char_line_eis->replot(); // Cần replot để cập nhật giao diện
    }
}
void MainWindow::onMessageReceived(const QByteArray &message, const QMqttTopicName &topic) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message);
    qDebug()<< message;
    if (message == "OK") {
        ui->status_mqtt->setText((QString)"Connected");
        QMessageBox::information(this, QLatin1String("Device"), QLatin1String("Device is ready"));
        // ui->comboBoxListDevice->addItem("mem2");
        ui->comboBoxListDevice->addItem("mem1");

    }

    if (message == "DONE_CV") {
        // tranform_cv();      //Thinh

    }

    if (message == "VOL") {
        QMessageBox::information(this, QLatin1String("Control"), QLatin1String("Control Vol Success!"));
    }
    responseTimer.stop();

    if (!jsonDoc.isNull()) {
        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            QString cmdValue = jsonObj["cmd"].toString();
            QString object = jsonObj["object"].toString();
            if (cmdValue == "data"){
                if (object == "vol") {
                    QJsonObject attributeObject = jsonObj["attribute"].toObject();
                    vol_value_1_current = attributeObject["vol1"].toDouble();
                    vol_value_2_current = attributeObject["vol2"].toDouble();
                    update_vol_current_value(vol_value_1_current, vol_value_2_current);
                }
                else if (object == "eis") {
                    QJsonObject attributeObject = jsonObj["attribute"].toObject();
                    double freq_value = attributeObject["freq"].toDouble();
                    double mangitude = attributeObject["magnitude"].toDouble();
                    double phase_value = attributeObject["phase"].toDouble();
                    if (qIsInf(mangitude)) {
                        // Gán giá trị mặc định là 100 nếu magnitude là infinity
                        mangitude = 60000000;
                    }

                    qDebug() << "Before ADD Data" <<":Fred :" << freq_value << ";" << mangitude << ";" <<phase_value ;
                    eis_add_data(freq_value, mangitude, phase_value);
                    plot_chart_eis();
                }
                else if (object == "cv") {
                    gap_cv_meansure = 200;
                    QJsonObject attributeObject = jsonObj["attribute"].toObject();
                    double indexVol = attributeObject["index"].toDouble();
                    double data_value = attributeObject["data"].toDouble();
                    if (receiverCount <= 100){
                        cv_add_data(start_vol_cv + step*receiverCount , data_value);     // thinh
                        plot_chart_cv();

                    }
                    else if (receiverCount >=2){
                        chart_buffer_cv_current[0] = data_value*25000;
                        chart_buffer_cv_current[1] = data_value*25000;
                        cv_add_data(end_vol_cv - step*(receiverCount - 100) , data_value);
                        plot_chart_cv();
                    }
                    receiverCount++;
                    // cv_add_data(indexVol , data_value);
                    // tranform_cv();




                }
            }
            // qDebug()<<"Value of key: "<< keyValue;
            // Xử lý giá trị nhận được
        }
    }
}

void MainWindow::update_vol_current_value(double _vol1, double _vol2)
{
    ui->value_voltage1_display->setText(QString::number((_vol1), 'f', 2) + "V");
    ui->value_voltage2_display->setText(QString::number((_vol2), 'f', 2) + "V");
}

MainWindow::~MainWindow()
{
    delete ui;
    if (_serialPort != nullptr){
        _serialPort->close();
        delete _serialPort;
    }
}


void MainWindow::loadPort(void){
    foreach (auto &port, QSerialPortInfo::availablePorts()) {
        qDebug()<<port.portName();
        qDebug()<<"description com:"<< port.description();
        if (port.description().contains("Standard") != 1)
            ui->cmbPort->addItem(port.portName());

    }
}

void MainWindow::resetPort(void){
    foreach (auto &port, QSerialPortInfo::availablePorts()) {
        qDebug()<<port.portName();
        ui->cmbPort->clear();

    }
}

void MainWindow::onError(void){
    qDebug()<<"Connect Mqtt Error !";
    m_client = new QMqttClient(this);
    m_client->setHostname("513booyoungct4.ddns.net");
    m_client->setUsername("admin");
    m_client->setPassword("admin13589");
    m_client->setPort(1883);
    connect(m_client, &QMqttClient::connected, this, &MainWindow::onConnected);
    connect(m_client, &QMqttClient::errorChanged, this, &MainWindow::onError);
    connect(m_client, &QMqttClient::messageReceived, this, &onMessageReceived);
    m_client->connectToHost();
}

void MainWindow::onConnected(void){
    qDebug()<<"Connected Mqtt!";
    QMessageBox::information(this, QLatin1String("Connected"), QLatin1String("MQTT is Connected!"));
    auto subscription = m_client->subscribe((QString)"mems_server", 2);
    if (!subscription) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }
}




void MainWindow::on_btnPortInfo_clicked()
{
    resetPort();
    loadPort();
}


void MainWindow::plot_chart_cv()
{
    // ui->char_line_cv->graph(0)->setData(chart_buffer_cv_voltage, chart_buffer_cv_current);
    curveMagnitude->data()->clear();

    curveMagnitude->addData(chart_buffer_cv_voltage, chart_buffer_cv_current);
    // ->setAdaptiveSampling(true);
    // curveMagnitude->addData(chart_buffer_cv_voltage, chart_buffer_cv_current);
    if (chart_buffer_cv_voltage.last() > (double)(ui->char_line_cv->xAxis->range().upper) || chart_buffer_cv_current.last() > (double)(ui->char_line_cv->yAxis->range().upper) ||
        chart_buffer_cv_voltage.last() < (double)(ui->char_line_cv->xAxis->range().lower) || chart_buffer_cv_current.last() < (double)(ui->char_line_cv->yAxis->range().lower))
        ui->char_line_cv->rescaleAxes();
    ui->char_line_cv->rescaleAxes();
    ui->char_line_cv->replot();
    ui->char_line_cv->update();
}

void MainWindow::plot_chart_eis()
{
    ui->char_line_eis->graph(0)->setData(chart_buffer_eis_fred, chart_buffer_eis_mangitude);
    ui->char_line_eis->graph(0)->setPen(QPen(Qt::red));
    ui->char_line_eis->graph(1)->setData(chart_buffer_eis_fred, chart_buffer_eis_phase);
    ui->char_line_eis->graph(1)->setPen(QPen(Qt::blue));
    if (chart_buffer_eis_fred.last() > (double)(ui->char_line_eis->xAxis->range().upper) || chart_buffer_eis_phase.last() > (double)(ui->char_line_eis->yAxis->range().upper) ||
        chart_buffer_eis_fred.last() < (double)(ui->char_line_eis->xAxis->range().lower) || chart_buffer_eis_phase.last() < (double)(ui->char_line_eis->yAxis->range().lower) ||
        chart_buffer_eis_phase.last() > (double)(ui->char_line_eis->yAxis2->range().upper) || chart_buffer_eis_fred.last() < (double)(ui->char_line_eis->yAxis2->range().lower))
    {
        ui->char_line_eis->rescaleAxes();
    }
    ui->char_line_eis->replot();
    ui->char_line_eis->update();
}


void MainWindow::cv_add_data(double _voltage, double _current)
{
    chart_buffer_cv_voltage.append(_voltage);
    chart_buffer_cv_current.append(_current*25000);
}

void MainWindow::eis_add_data(double _freq, double _mangitude, double _phase)
{
    chart_buffer_eis_fred.append(_freq);
    chart_buffer_eis_mangitude.append(_mangitude);
    chart_buffer_eis_phase.append(_phase);
}

void MainWindow::on_pushButton_2_clicked()
{

    _serialPort = new QSerialPort(this);
    _serialPort->setPortName(ui->cmbPort->currentText());
    _serialPort->setBaudRate(QSerialPort::Baud115200);
    _serialPort->setDataBits(QSerialPort::Data8);
    _serialPort->setParity(QSerialPort::NoParity);
    _serialPort->setStopBits(QSerialPort::OneStop);
    if (_serialPort->open(QIODevice::ReadWrite)){
        QMessageBox::information(this, "Result", "Port opened successfully");
        connect(_serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
        ui->status_com->setText("Connected");
    } else {
        QMessageBox::critical(this, "Port Error", "Unable to open ");
    }

}

void MainWindow::readData(){
    if (!_serialPort->isOpen()){
        QMessageBox::critical(this, "Port Error", "Port is not Opened");
        return;
    }
}

void MainWindow::setClientPort(int p)
{
    m_client->setPort(p);
}



void MainWindow::on_meansure_Btn_clicked()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        QMessageBox::critical(this, "Mqtt is not connected", "Please check your connect!");
        return;
    }
    // m_client->publish((QString)"state", "READ_CV");

    QJsonObject jsonObject;
    jsonObject["cmd"] = "control";
    if (ui->tabWidget->currentIndex() == 0){
        buffer_serial.fill(0);
        receiverCount = 0;
        RepeatTimes = ui->spin_box_repeat_time->value();
        step = ui->spin_box_step->value();
        start_vol_cv = ui->spin_box_start_voltage->value();
        end_vol_cv = ui->spin_box_end_voltage->value();
        numStep = ((-start_vol_cv + end_vol_cv)/step + 1)*2;
        gap_cv_meansure = (-start_vol_cv + end_vol_cv)/step;
        jsonObject["object"] = "cv";
        QJsonObject attributeObject;
        attributeObject["start_voltage"] = ui->spin_box_start_voltage->value();
        attributeObject["end_voltage"] = ui->spin_box_end_voltage->value();
        attributeObject["repeat_times"] = ui->spin_box_repeat_time->value();
        attributeObject["log_en"] = 0;
        attributeObject["step"] = numStep;
        jsonObject["attribute"] = attributeObject;

    }
    else if (ui->tabWidget->currentIndex() == 1){
        jsonObject["object"] = "eis";
        QJsonObject attributeObject;
        attributeObject["start_freq"] = ui->spin_box_start_freq->value();
        attributeObject["stop_freq"] = ui->spin_box_end_freq->value();
        attributeObject["sweep_point"] = ui->spin_box_sweep_point->value();
        attributeObject["repeat_times"] = ui->spin_box_repeat_times_eis->value();
        attributeObject["log_en"] = 0;
        jsonObject["attribute"] = attributeObject;
    }
    QJsonDocument doc(jsonObject);
    QByteArray payload = doc.toJson(QJsonDocument::Compact);
    m_client->publish((QString)"mems_esp", payload);
}




void MainWindow::on_btn_send_control_vol_clicked()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        QMessageBox::critical(this, "Mqtt is not connected", "Please check your connect!");
        return;
    }
    QJsonObject jsonObject;
    jsonObject["cmd"] = "control";
    jsonObject["object"] = "vol";
    QJsonObject attributeObject;
    attributeObject["vol1"] = ui->box_value_vol1->currentText().toDouble();
    attributeObject["vol2"] = ui->box_value_vol2->currentText().toDouble();
    jsonObject["attribute"] = attributeObject;
    QJsonDocument doc(jsonObject);
    QByteArray payload = doc.toJson(QJsonDocument::Compact);
    m_client->publish((QString)"mems_esp", payload);
}


void MainWindow::onTimeout() {
    qDebug()<< "Cảnh báo: Không nhận được phản hồi sau 5 giây!";
    ui->status_mqtt->setText((QString)"Disconnected");
    QMessageBox::information(this, QLatin1String("Device"), QLatin1String("Device is not ready!"));
}

void MainWindow::on_btn_checkmqtt_clicked()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        QMessageBox::critical(this, QLatin1String("MQTT is not connected"), QLatin1String("Please check your internet!"));
        return;
    }
    const QString topicName = "mems_esp";
    QMqttTopicName topic(topicName);
    m_client->publish(topic, "check");
    responseTimer.setSingleShot(true);
    responseTimer.start(5000); // 5
    connect(&responseTimer, &QTimer::timeout, this, &MainWindow::onTimeout);
    ui->status_mqtt->setText((QString)"Waitting");

}

void MainWindow::on_box_value_vol1_currentIndexChanged(int index)
{



}


void MainWindow::on_btn_clear_chart_clicked()
{
    chart_buffer_cv_current.clear();
    chart_buffer_cv_voltage.clear();
    chart_buffer_eis_fred.clear();
    chart_buffer_eis_mangitude.clear();
    chart_buffer_eis_phase.clear();
    // ui->char_line_eis->clearData();
    for (int i = 0; i < ui->char_line_eis->graphCount(); ++i) {
        QCPGraph *graph = ui->char_line_eis->graph(i);
        graph->data()->clear(); // Clear data points
    }
    ui->char_line_eis->replot();
    ui->char_line_cv->replot();

}

void MainWindow::on_plot_data_clicked()
{
    // cv_add_data(ui->box_value_X->value(), ui->box_value_Y->value());
    eis_add_data(10, 12, 13);
    eis_add_data(13, 14, 15);
    ui->char_line_eis->graph(0)->setData(chart_buffer_eis_fred, chart_buffer_eis_mangitude);
    ui->char_line_eis->rescaleAxes();
    ui->char_line_eis->replot();
    plot_chart_eis();
}

void MainWindow::on_pushButton_6_clicked()
{
    curveMagnitude->data()->clear();
    ui->char_line_eis->replot();
    ui->char_line_cv->replot();
    // ui->char_line_cv->update();

    chart_buffer_cv_current.clear();
    chart_buffer_cv_voltage.clear();
    chart_buffer_eis_fred.clear();
    chart_buffer_eis_mangitude.clear();
    chart_buffer_eis_phase.clear();
    // ui->char_line_eis->clearData();
    for (int i = 0; i < ui->char_line_eis->graphCount(); ++i) {
        QCPGraph *graph = ui->char_line_eis->graph(i);
        graph->data()->clear(); // Clear data points
    }
    ui->char_line_eis->replot();
    ui->char_line_cv->replot();
}



void MainWindow::onTimeoutDialogReaddyConfig() {
    qDebug()<< "Cảnh báo: Không nhận được phản hồi sau 5 giây!";
    QMessageBox::information(this, QLatin1String("Device"), QLatin1String("Config success!"));
}
void MainWindow::on_sync_btn_4_clicked()
{
    Timer_check_config.setSingleShot(true);
    Timer_check_config.start(2000); // 5
    connect(&Timer_check_config, &QTimer::timeout, this, &MainWindow::onTimeoutDialogReaddyConfig);
}

void MainWindow::onTimeoutWriteLog() {
    qDebug()<< "Cảnh báo: Không nhận được phản hồi sau 5 giây!";
    ui->LogCheckDevice->setText((QString)"Device is OK!");
}

void MainWindow::on_sync_btn_7_clicked()
{
    Timer_check_qc.setSingleShot(true);
    Timer_check_qc.start(3000); // 5
    connect(&Timer_check_qc, &QTimer::timeout, this, &MainWindow::onTimeoutWriteLog);
}


void MainWindow::on_pushButton_3_clicked()
{

    ui->status_com->setText("Disconnected");

}


void MainWindow::on_pushButton_7_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Chọn tệp", "", "All Files (*)");

    // Kiểm tra nếu người dùng đã chọn một tệp
    if (!filePath.isEmpty()) {
        qDebug() << "Đường dẫn tệp đã chọn:" << filePath;
        // Lưu đường dẫn tệp vào một biến thành viên
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Could not open file";
        }
        bool isFirstLine = true;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (isFirstLine) {
                isFirstLine = false;
                continue;
            }

            QStringList lineData = line.split(","); // Phân tách dữ liệu bằng dấu tab (\t)
            if (lineData.size() == 2) {
                bool ok1, ok2;
                double x = lineData[0].toDouble(&ok1);
                double y = lineData[1].toDouble(&ok2);
                if (ok1 && ok2) {
                    chart_buffer_cv_voltage.append(x);
                    chart_buffer_cv_current.append(y);
                } else {
                    qDebug() << "Invalid data format in line:" << line;
                }
                plot_chart_cv();
            }
            if (lineData.size() == 3){

                bool ok1, ok2, ok3;
                double x = lineData[0].toDouble(&ok1);
                double y = lineData[1].toDouble(&ok2);
                double z = lineData[2].toDouble(&ok3);
                if (ok1 && ok2 && ok3) {
                    chart_buffer_eis_fred.append(x);
                    chart_buffer_eis_mangitude.append(y);
                    chart_buffer_eis_phase.append(z);
                } else {
                    qDebug() << "Invalid data format in line:" << line;
                }
                plot_chart_eis();
            }
            else {
                qDebug() << "Invalid line format:" << line;
            }
        }

    }
}


void MainWindow::on_pushButton_8_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save CSV File", "", "CSV files (*.csv)");

    // Kiểm tra nếu người dùng đã chọn tên tệp
    if (!fileName.isEmpty()) {
        QFile file(fileName);

        // Mở tệp để ghi
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            if (ui->tabWidget->currentIndex() == 1){
                // Ghi tiêu đề
                stream << "fred,mangitude,phase\n";

                // Xác định số lượng hàng (phần tử) lớn nhất trong các vector
                int maxRows = qMax(chart_buffer_eis_fred.size(), qMax(chart_buffer_eis_mangitude.size(), chart_buffer_eis_phase.size()));

                // Ghi dữ liệu từ các vector vào tệp CSV
                for (int i = 0; i < maxRows; ++i) {
                    if (i < chart_buffer_eis_fred.size())
                        stream << chart_buffer_eis_fred[i];
                    stream << ",";
                    if (i < chart_buffer_eis_mangitude.size())
                        stream << chart_buffer_eis_mangitude[i];
                    stream << ",";
                    if (i < chart_buffer_eis_phase.size())
                        stream << chart_buffer_eis_phase[i];
                    stream << "\n";
                }
            }
            else {
                stream << "vol,current\n";

                // Xác định số lượng hàng (phần tử) lớn nhất trong các vector
                int maxRows = qMax(chart_buffer_cv_voltage.size(), chart_buffer_cv_current.size());

                // Ghi dữ liệu từ các vector vào tệp CSV
                for (int i = 0; i < maxRows; ++i) {
                    if (i < chart_buffer_cv_voltage.size())
                        stream << chart_buffer_cv_voltage[i];
                    stream << ",";
                    if (i < chart_buffer_cv_current.size())
                        stream << chart_buffer_cv_current[i];
                    stream << "\n";
                }
            }

            file.close();
            qDebug() << "File saved:" << fileName;
        } else {
            qWarning() << "Could not open file for writing";
        }

    }
}

