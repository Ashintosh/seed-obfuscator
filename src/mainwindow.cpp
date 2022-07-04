﻿////////////////////////////////////////////////////////////////////////////
// seed-obfuscator                                                        //
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

#include <iostream>
#include <QMessageBox>
#include <vector>
#include <fstream>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "seedstringtools.h"
#include "bip39.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnObfuscate_clicked()
{
    std::string seed_phrase = ui->lnSeed->text().toStdString();
    std::string passphrase = ui->lnPassphrase->text().toStdString();
    std::string confirm_passphrase = ui->lnConfirmPassphrase->text().toStdString();

    if (passphrase.length() < 6) {
        QMessageBox::warning(this, "Warning", "Passphrase should be at least 6 characters.", QMessageBox::Ok);
        return;
    }
    if (passphrase != confirm_passphrase) {
        QMessageBox::warning(this, "Warning", "Passphrases do not match.", QMessageBox::Ok);
        return;
    }

    ui->txtResult->setText(QString::fromStdString(seedstringtools::obfuscate_seed(seed_phrase, passphrase)));

    //std::cout << seedstringtools::obfuscate_seed(seed_phrase, passphrase);
}
