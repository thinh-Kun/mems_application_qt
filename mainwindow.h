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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMqttClient>
#include "QSerialPort"
#include "QSerialPortInfo"
#include "QDebug"
#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <qcustomplot.h>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void timer_init(int interval, const char *callback) {
        // Tạo và khởi động QTimer
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, callback);
        timer->start(interval); // Thiết lập thời gian chạy là 10ms
    }


public slots:
    void setClientPort(int p);
    void plot_chart_cv();
    void plot_chart_eis();
    void cv_add_data(double _voltage, double _current);
    void eis_add_data(double _freq, double _mangitude, double _phase);

private slots:

    void on_btnPortInfo_clicked();

    void on_pushButton_2_clicked();

    void readData();

    void on_meansure_Btn_clicked();


    void on_btn_send_control_vol_clicked();

    void on_btn_checkmqtt_clicked();


    void on_box_value_vol1_currentIndexChanged(int index);

    void on_btn_clear_chart_clicked();


    void on_plot_data_clicked();

    void on_pushButton_6_clicked();

    void on_sync_btn_4_clicked();

    void on_sync_btn_7_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    QMqttClient *m_client;
    QSerialPort *_serialPort;
    QVector<double> chart_buffer_eis_fred;
    QVector<double> chart_buffer_eis_mangitude;
    QVector<double> chart_buffer_eis_phase;
    QVector<double> chart_buffer_cv_voltage;
    QVector<double> chart_buffer_cv_current;
    QVector<double> bufferV;
    QVector<double> bufferC;
    void loadPort(void);
    void resetPort(void);
    void onError(void);
    void onConnected(void);
    void onTimeout(void);
    void onTimeoutDialogReaddyConfig(void);
    void onTimeoutWriteLog(void);
    void onMessageReceived(const QByteArray &message, const QMqttTopicName &topic);
    void update_vol_current_value(double _vol1, double _vol2);
    void handleLegendClick(QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event);
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
