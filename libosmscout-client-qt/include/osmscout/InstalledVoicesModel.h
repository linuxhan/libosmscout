#ifndef OSMSCOUT_CLIENT_QT_INSTALLEDVOICESMODEL_H
#define OSMSCOUT_CLIENT_QT_INSTALLEDVOICESMODEL_H

/*
  OSMScout - a Qt backend for libosmscout and libosmscout-map
  Copyright (C) 2020 Lukas Karas

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/
#include <osmscout/VoiceManager.h>
#include <osmscout/Voice.h>
#include <osmscout/Settings.h>
#include <osmscout/ClientQtImportExport.h>

#include <QAbstractListModel>

namespace osmscout {

/**
 * Model providing access to currently installed voices on device
 * + entry for configuration without voice commands.
 *
 * This model suppose to be used in combo box.
 *
 * \ingroup QtAPI
 */
class OSMSCOUT_CLIENT_QT_API InstalledVoicesModel : public QAbstractListModel {
  Q_OBJECT

signals:


public slots:
  void update();
  void onVoiceChanged();

public:
  InstalledVoicesModel();

  virtual ~InstalledVoicesModel();

  enum Roles {
    NameRole = Qt::UserRole, // name
    LangRole = Qt::UserRole + 1, //
    GenderRole = Qt::UserRole + 2, // male or female (for now :-))
    ValidRole = Qt::UserRole + 3, // true if it real voice, false when placeholder for no-voice configuration
    LicenseRole = Qt::UserRole + 4,
    AuthorRole = Qt::UserRole + 5,
    DescriptionRole = Qt::UserRole + 6,
    SelectedRole = Qt::UserRole + 7 // true when this voice is selected
  };
  Q_ENUM(Roles)

  Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role) const;
  virtual QHash<int, QByteArray> roleNames() const;
  Q_INVOKABLE virtual Qt::ItemFlags flags(const QModelIndex &index) const;

private:
  QList<Voice> voices;
  VoiceManagerRef voiceManager;
  SettingsRef settings;
};
}
#endif //OSMSCOUT_CLIENT_QT_INSTALLEDVOICESMODEL_H
