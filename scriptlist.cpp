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
  QString sql = "SELECT id, en, ja, parent_id, commentary FROM `scripts`";
  if (!query.exec(sql)) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  } else {
    m_list.clear();
    while (query.next()) {
      int cnt = 0;
      int id = query.value(cnt).toInt();
      QString en = query.value(++cnt).toString();
      QString ja = query.value(++cnt).toString();
      int parent_id = query.value(++cnt).toInt();
      QString commentary = query.value(++cnt).toString();
      Script script(this, id, en, ja, commentary);
      m_list.append(script);
    }
  }
  db->close();
  return m_list.size();
}

QList<Script> ScriptList::list() const { return m_list; }

void ScriptList::updateItem(QSqlDatabase *db, const QString &exp,
                            const QString &field, int id) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return;
  }
  QSqlQuery query(*db);
  QString sql = "UPDATE `scripts` SET `" + field + "`=:exp WHERE id=:id ";
  query.prepare(sql);
  query.bindValue(":id", id);
  query.bindValue(":exp", exp);
  if (!query.exec()) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  }
  db->close();
}

void ScriptList::createItem(QSqlDatabase *db, const QString &exp,
                            const QString &field) {
  if (!db->open()) {
    qInfo() << db->lastError().text();
    return;
  }
  QSqlQuery query(*db);
  QString sql = "INSERT INTO`scripts` (" + field + ") VALUES (:exp)";
  query.prepare(sql);
  query.bindValue(":exp", exp);
  if (!query.exec()) {
    qInfo() << db->lastError().text();
    qInfo() << query.lastError().text();
  }
  db->close();
}

void ScriptList::sort() {
  std::sort(m_list.begin(), m_list.end(), comparetaor);
}

bool ScriptList::comparetaor(Script a, Script b) { return a.en() < b.en(); }
