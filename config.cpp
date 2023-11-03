#include "config.h"

#include <QSettings>

Config::Config(QObject *parent) : QObject{parent} {}

Config::Config(const Config &o) : m_geometry(o.m_geometry) {}

Config &Config::operator=(const Config &o) {
  if (this != &o) {
    m_geometry = o.m_geometry;
  }
  return *this;
}
void Config::load() {
  QSettings settings(AUTHOR, APPNAME);
  settings.beginGroup(GENERAL);
  m_geometry = settings.value(GEOM).toByteArray();
  settings.endGroup();
}

void Config::save() {
  QSettings settings(AUTHOR, APPNAME);
  settings.beginGroup(GENERAL);
  settings.setValue(GEOM, m_geometry);
  settings.endGroup();
}

QByteArray Config::geometry() const { return m_geometry; }

void Config::setGeometry(const QByteArray &newGeometry) {
  m_geometry = newGeometry;
}
