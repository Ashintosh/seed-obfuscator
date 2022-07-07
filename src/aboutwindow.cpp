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

#include "aboutwindow.h"


aboutwindow::aboutwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aboutwindow)
{
    ui->setupUi(this);
    ui->lblVersion_Val->setText(QString::fromStdString("Version: " + seedobfuscator::get_version_str()));
}

aboutwindow::~aboutwindow()
{
    delete ui;
}

void aboutwindow::on_btnCheckUpdate_clicked()
{
    std::string latest_version = curl::url_to_str("https://raw.githubusercontent.com/Ashintosh/seed-obfuscator/main/VERSION");
    latest_version.erase(std::remove_if(latest_version.begin(), latest_version.end(), ::isspace), latest_version.end());

    if (latest_version == "null") {
        QMessageBox::warning(this, "Error", "Could not connect to repository.", QMessageBox::Ok);
        return;
    } else if (latest_version == seedobfuscator::get_version_str()) {
        QMessageBox::information(this, "Update", "You are running the latest release.", QMessageBox::Ok);
        return;
    } else {
        int result = QMessageBox::information(this, "Update", "Update available!\nWould you like to get the latest release?", QMessageBox::Yes|QMessageBox::No);
        if (result == QMessageBox::Yes) {
            QString link = "https://github.com/Ashintosh/seed-obfuscator/releases/tag/v" + QString::fromStdString(latest_version);
            QDesktopServices::openUrl(QUrl(link));
        }
        return;
    }
}

