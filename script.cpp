#include "script.h"

Script::Script(QObject *parent, int id, const QString &en, const QString &ja, const QString &commentary)
    : QObject{parent} {
  m_id = id;
  m_en = en;
  m_ja = ja;
  m_commentary=commentary;
}

Script::Script(const Script &o) : m_id(o.m_id), m_en(o.m_en), m_ja(o.m_ja), m_commentary(o.m_commentary) {}

Script &Script::operator=(const Script &o) {
  if (this != &o) {
    m_id = o.m_id;
    m_en = o.m_en;
    m_ja = o.m_ja;
    m_commentary=o.m_commentary;
  }
  return *this;
}

QString Script::en() const { return m_en; }

void Script::setEn(const QString &newEn) { m_en = newEn; }

QString Script::ja() const { return m_ja; }

void Script::setJa(const QString &newJa) { m_ja = newJa; }

int Script::id() const { return m_id; }

void Script::setId(int newId) { m_id = newId; }

QString Script::commentary() const { return m_commentary; }

void Script::setCommentary(const QString &newCommentary) {
  m_commentary = newCommentary;
}
