////////////////////////////////////////////////////////////////////////////
// seed-encryptor                                                         //
// Copyright (C) 2022 Ashintosh                                           //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <https://www.gnu.org/licenses/>. //
////////////////////////////////////////////////////////////////////////////

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include <vector>
#include <fstream>

#include "aboutwindow.h"
#include "./ui_mainwindow.h"
#include "seedstringtools.h"
#include "bip39.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnObfuscate_clicked();
    void on_btnDeobfuscate_clicked();
    void on_actionAbout_triggered();
    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
