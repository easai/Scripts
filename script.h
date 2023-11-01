#ifndef SCRIPT_H
#define SCRIPT_H

#include <QObject>

class Script : public QObject {
  Q_OBJECT
public:
  explicit Script(QObject *parent = nullptr, const QString& en="", const QString& ja="");
  Script(const Script &);
  Script &operator=(const Script &);

  QString en() const;
  void setEn(const QString &newEn);

  QString ja() const;
  void setJa(const QString &newJa);

signals:
private:
  QString m_en;
  QString m_ja;
};

#endif // SCRIPT_H
