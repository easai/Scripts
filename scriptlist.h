#ifndef SCRIPTLIST_H
#define SCRIPTLIST_H

#include "script.h"
#include <QObject>
#include <QSqlDatabase>

class ScriptList : public QObject
{
    Q_OBJECT
public:
    explicit ScriptList(QObject *parent = nullptr);

    int retrieve(QSqlDatabase *db);
    QList<Script> list() const;
    void updateItem(QSqlDatabase *db, const QString& exp, const QString& field, int id);

signals:
private:
    QList<Script> m_list;
};

#endif // SCRIPTLIST_H
