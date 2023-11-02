#ifndef SCRIPT_H
#define SCRIPT_H

#include <QObject>

class Script : public QObject {
  Q_OBJECT
public:
  explicit Script(QObject *parent = nullptr, int id = 0, const QString &en = "",
                  const QString &ja = "", const QString &commentary="");
  Script(const Script &);
  Script &operator=(const Script &);

  QString en() const;
  void setEn(const QString &newEn);

  QString ja() const;
  void setJa(const QString &newJa);

  int id() const;
  void setId(int newId);

  QString commentary() const;
  void setCommentary(const QString &newCommentary);

signals:
private:
  int m_id;
  QString m_en;
  QString m_ja;
  QString m_commentary;
};

#endif // SCRIPT_H
