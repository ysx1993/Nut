/**************************************************************************
**
** This file is part of Nut project.
** https://github.com/HamedMasafi/Nut
**
** Nut is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Nut is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Nut.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#include "sqlitegenerator.h"
#include "../table.h"
#include "../tablemodel.h"

NUT_BEGIN_NAMESPACE

SqliteGenerator::SqliteGenerator(Database *parent) : SqlGeneratorBase(parent)
{

}

QString SqliteGenerator::fieldType(FieldModel *field)
{
    QString ret = field->name + " ";
    QString dbType;
    QString primaryKeyPerfix;
    if (field->isPrimaryKey)
        primaryKeyPerfix = " PRIMARY KEY";

    switch (field->type) {
    case QMetaType::Bool:           return "BOOLEAN";
    case QMetaType::QByteArray:     return "BLOB";
    case QMetaType::QDate:          return "DATE";
    case QMetaType::QDateTime:      return "DATETIME";
    case QMetaType::QTime:          return "TIME";
    case QMetaType::Double:         return "DOUBLE";
    case QMetaType::Float:          return "FLOAT";

    case QMetaType::SChar:
    case QMetaType::Char:           return "TINYINT" + primaryKeyPerfix;
    case QMetaType::UChar:          return "TINYINT UNSIGNED" + primaryKeyPerfix;
    case QMetaType::Short:          return "SMALLINT" + primaryKeyPerfix;
    case QMetaType::UShort:         return "SMALLINT UNSIGNED" + primaryKeyPerfix;
    case QMetaType::Int:            return "INT" + primaryKeyPerfix;
    case QMetaType::UInt:           return "INT UNSIGNED" + primaryKeyPerfix;
    case QMetaType::Long:           return "MEDIUMINT" + primaryKeyPerfix;
    case QMetaType::ULong:          return "MEDIUMINT UNSIGNED" + primaryKeyPerfix;
    case QMetaType::LongLong:       return "BIGINT" + primaryKeyPerfix;
    case QMetaType::ULongLong:      return "BIGINT UNSIGNED" + primaryKeyPerfix;

    case QMetaType::QChar:          return "NCHAR(1)";

    case QMetaType::QUrl:
    case QMetaType::QJsonArray:
    case QMetaType::QJsonValue:
    case QMetaType::QJsonObject:
    case QMetaType::QJsonDocument:
    case QMetaType::QUuid:          return "text";

//        if (field->isAutoIncrement)
//            dbType.append(" PRIMARY KEY AUTOINCREMENT");

    case QMetaType::QString:
        if(field->length)
            return QString("VARCHAR(%1)").arg(field->length);
        else
            return "TEXT";
    default:
        qWarning("The type (%s) does not supported",
                 QMetaType::typeName(field->type));
        return QString();
    }
}

void SqliteGenerator::appendSkipTake(QString &sql, int skip, int take)
{
    if (take != -1 && skip != -1)
        sql.append(QString(" LIMIT %1 OFFSET %2")
                       .arg(take)
                       .arg(skip));
}

NUT_END_NAMESPACE
