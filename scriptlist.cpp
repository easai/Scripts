#include "scriptlist.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>

ScriptList::ScriptList(QObject *parent) : QObject{parent} {}

int ScriptList::retrieve(QSqlDatabase *db) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return 0;
  }
  QSqlQuery query(*db);
  QString sql = "SELECT en,ja FROM `scripts`";
  if (!query.exec(sql)) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  } else {
    m_list.clear();
    while (query.next()) {
      QString en = query.value(0).toString();
      QString ja = query.value(1).toString();
      Script script(this, en, ja);
      m_list.append(script);
    }
  }
  db->close();
  return m_list.size();
}

QList<Script> ScriptList::list() const { return m_list; }
