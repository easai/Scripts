#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

#define AUTHOR "easai"
#define APPNAME "Numbers"
#define GENERAL "General"
#define GEOM "Geometry"

class Config : public QObject {
  Q_OBJECT
public:
  explicit Config(QObject *parent = nullptr);
  Config(const Config &);
  Config &operator=(const Config &);

  void load();
  void save();

  QByteArray geometry() const;
  void setGeometry(const QByteArray &newGeometry);

  signals:
private:
  QByteArray m_geometry;
};

#endif // CONFIG_H
