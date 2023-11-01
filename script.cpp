#include "script.h"

Script::Script(QObject *parent, int id, const QString &en, const QString &ja)
    : QObject{parent} {
  m_id = id;
  m_en = en;
  m_ja = ja;
}

Script::Script(const Script &o) : m_id(o.m_id), m_en(o.m_en), m_ja(o.m_ja) {}

Script &Script::operator=(const Script &o) {
  if (this != &o) {
    m_id = o.m_id;
    m_en = o.m_en;
    m_ja = o.m_ja;
  }
  return *this;
}

QString Script::en() const { return m_en; }

void Script::setEn(const QString &newEn) { m_en = newEn; }

QString Script::ja() const { return m_ja; }

void Script::setJa(const QString &newJa) { m_ja = newJa; }

int Script::id() const { return m_id; }

void Script::setId(int newId) { m_id = newId; }
