////////////////////////////////////////////////////////////////////////////
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

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QWidget>
#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>

#include "ui_aboutwindow.h"
#include "seedobfuscator.h"
#include "curl/curl.h"

namespace Ui {
class aboutwindow;
}

class aboutwindow : public QWidget
{
    Q_OBJECT

public:
    explicit aboutwindow(QWidget *parent = nullptr);
    ~aboutwindow();

private slots:
    void on_btnCheckUpdate_clicked();

private:
    Ui::aboutwindow *ui;
};

#endif // ABOUTWINDOW_H
