/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2025 Chris Rizzitello <sithlord48@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include <QSettings>

#include <QDir>

#include "common/constants.h"

class Settings : public QObject
{
  Q_OBJECT
public:
#if defined(Q_OS_WIN)
  inline const static auto UserDir = QStringLiteral("%1/AppData/Local/%2").arg(QDir::homePath(), kAppName);
  inline const static auto SystemDir = QStringLiteral("C:/ProgramData/%1").arg(kAppName);
#elif defined(Q_OS_MAC)
  inline const static auto UserDir = QStringLiteral("%1/Library/%2").arg(QDir::homePath(), kAppName);
  inline const static auto SystemDir = QStringLiteral("/Library/%1").arg(kAppName);
#else
  inline const static auto UserDir = QStringLiteral("%1/.config/%2").arg(QDir::homePath(), kAppName);
  inline const static auto SystemDir = QStringLiteral("/etc/%1").arg(kAppName);
#endif
  inline const static auto UserSettingFile = QStringLiteral("%1/%2.conf").arg(UserDir, kAppName);
  inline const static auto SystemSettingFile = QStringLiteral("%1/%2.conf").arg(SystemDir, kAppName);

  struct Client
  {
    inline static const auto Binary = QStringLiteral("client/binary");
    inline static const auto InvertScrollDirection = QStringLiteral("client/invertscolldirection");
    inline static const auto LanguageSync = QStringLiteral("client/languageSync");
    inline static const auto RemoteHost = QStringLiteral("client/remotehost");
  };
  struct Core
  {
    inline static const auto Interface = QStringLiteral("core/interface");
    inline static const auto LastVersion = QStringLiteral("core/lastVersion");
    inline static const auto Port = QStringLiteral("core/port");
    inline static const auto PreventSleep = QStringLiteral("core/preventSleep");
    inline static const auto Scope = QStringLiteral("core/loadFromSystemScope");
    inline static const auto StartedBefore = QStringLiteral("core/startedBefore");
  };
  struct Gui
  {
    inline static const auto Autohide = QStringLiteral("gui/autoHide");
    inline static const auto AutoUpdateCheck = QStringLiteral("gui/enableUpdateCheck");
    inline static const auto CloseReminder = QStringLiteral("gui/closeReminder");
    inline static const auto CloseToTray = QStringLiteral("gui/closeToTray");
    inline static const auto LogExpanded = QStringLiteral("gui/logExpanded");
    inline static const auto SymbolicTrayIcon = QStringLiteral("gui/symbolicTrayIcon");
    inline static const auto WindowGeometry = QStringLiteral("gui/windowGeometry");
  };
  struct Log
  {
    inline static const auto Level = QStringLiteral("log/level");
    inline static const auto ToFile = QStringLiteral("log/toFile");
  };
  struct Security
  {
    inline static const auto CheckPeers = QStringLiteral("security/checkpeerfingerprints");
    inline static const auto Certificate = QStringLiteral("security/certificate");
    inline static const auto KeySize = QStringLiteral("security/keySize");
    inline static const auto TlsEnabled = QStringLiteral("security/tlsEnabled");
  };
  struct Server
  {
    inline static const auto Binary = QStringLiteral("server/binary");
    inline static const auto ExternalConfig = QStringLiteral("server/externalConfig");
    inline static const auto ExternalConfigFile = QStringLiteral("server/externalConfigFile");
  };

  static Settings *instance();
  static void setSettingFile(const QString &settingsFile = QString());
  static void setValue(const QString &key = QString(), const QVariant &value = QVariant());
  static QVariant value(const QString &key = QString());
  static void restoreDefaultSettings();
  static QVariant defaultValue(const QString &key);
  static bool isWritable();
  static bool isSystemScope();
  static void setScope(bool systemScope);
  static const QString settingsFile();
  static const QString settingsPath();
  static const QString logLevelText();

signals:
  void scopeChanged(bool isSystemScope);
  void writableChanged(bool canWrite);
  void settingsChanged(const QString key);

private:
  explicit Settings(QObject *parent = nullptr);
  Settings *operator=(Settings &other) = delete;
  Settings(const Settings &other) = delete;
  ~Settings() = default;
  static bool isPortableSettings();
  void cleanSettings();
  void initSettings();

  QSettings *m_settings = nullptr;
  QString m_portableSettingsFile = QStringLiteral("%1.conf").arg(kAppName);
  // clang-format off
  inline static const QStringList m_logLevels = {
     QStringLiteral("INFO")
    , QStringLiteral("DEBUG")
    , QStringLiteral("DEBUG1")
    , QStringLiteral("DEBUG2")
  };

  inline static const QStringList m_validKeys = {
      Client::Binary
    , Client::InvertScrollDirection
    , Client::LanguageSync
    , Client::RemoteHost
    , Core::Interface
    , Core::LastVersion
    , Core::Port
    , Core::PreventSleep
    , Core::Scope
    , Core::StartedBefore
    , Log::Level
    , Log::ToFile
    , Gui::Autohide
    , Gui::AutoUpdateCheck
    , Gui::CloseReminder
    , Gui::CloseToTray
    , Gui::LogExpanded
    , Gui::SymbolicTrayIcon
    , Gui::WindowGeometry
    , Security::Certificate
    , Security::CheckPeers
    , Security::KeySize
    , Security::TlsEnabled
    , Server::Binary
    , Server::ExternalConfig
    , Server::ExternalConfigFile
  };
  // clang-format on
};
