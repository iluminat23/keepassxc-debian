/*
 *  Copyright (C) 2018 KeePassXC Team <team@keepassxc.org>
 *  Copyright (C) 2018 Sami Vänttinen <sami.vanttinen@protonmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEEPASSXC_DATABASESETTINGSWIDGETBROWSER_H
#define KEEPASSXC_DATABASESETTINGSWIDGETBROWSER_H

#include "DatabaseSettingsWidget.h"

#include "browser/BrowserService.h"
#include "core/CustomData.h"
#include "gui/DatabaseTabWidget.h"

#include <QItemSelection>
#include <QPointer>
#include <QScopedPointer>
#include <QStandardItemModel>

class Database;
namespace Ui
{
    class DatabaseSettingsWidgetBrowser;
}

class DatabaseSettingsWidgetBrowser : public DatabaseSettingsWidget
{
    Q_OBJECT

public:
    explicit DatabaseSettingsWidgetBrowser(QWidget* parent = nullptr);
    Q_DISABLE_COPY(DatabaseSettingsWidgetBrowser);
    ~DatabaseSettingsWidgetBrowser() override;

    CustomData* customData() const;
    inline bool hasAdvancedMode() const override
    {
        return false;
    }

public slots:
    void initialize() override;
    void uninitialize() override;
    bool save() override;

private slots:
    void removeSelectedKey();
    void toggleRemoveButton(const QItemSelection& selected);
    void updateSharedKeyList();
    void removeSharedEncryptionKeys();
    void removeStoredPermissions();
    void convertAttributesToCustomData();

private:
    void updateModel();
    void settingsWarning();

protected:
    void showEvent(QShowEvent* event) override;

    const QScopedPointer<Ui::DatabaseSettingsWidgetBrowser> m_ui;

private:
    QPointer<CustomData> m_customData;
    QPointer<QStandardItemModel> m_customDataModel;
    BrowserService m_browserService;
};

#endif // KEEPASSXC_DATABASESETTINGSWIDGETBROWSER_H
