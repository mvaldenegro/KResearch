/*
 * Copyright (C) 2011-2012 Matias Valdenegro <matias.valdenegro@gmail.com>
 * This file is part of KResearch.
 *
 * kesearch is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * kresearch is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KResearch.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "DocumentType.h"

inline uint qHash(DocumentType type)
{
    return qHash((uint) type);
}

static QHash<DocumentType, QString> toStringHash()
{
    QHash<DocumentType, QString> ret;

    ret.insert(DocumentType::Unknown                 , QString("Unknown"));
    ret.insert(DocumentType::Unpublished             , QString("Unpublished"));
    ret.insert(DocumentType::Article                 , QString("Article"));
    ret.insert(DocumentType::ConferenceArticle       , QString("Conference Article"));
    ret.insert(DocumentType::Book                    , QString("Book"));
    ret.insert(DocumentType::Booklet                 , QString("Booklet"));
    ret.insert(DocumentType::BookChapter             , QString("Book Chapter"));
    ret.insert(DocumentType::BookPart                , QString("Book part"));
    ret.insert(DocumentType::BachelorThesis          , QString("Bachelor Thesis"));
    ret.insert(DocumentType::MasterThesis            , QString("Master Thesis"));
    ret.insert(DocumentType::DoctoralThesis          , QString("Doctoral Thesis"));
    ret.insert(DocumentType::TechnicalReport         , QString("Technical Report"));
    ret.insert(DocumentType::TechnicalDocumentation  , QString("Technical Documentation"));
    ret.insert(DocumentType::OtherDocument           , QString("Other document type"));

    return ret;
}

static QHash<DocumentType, QString> documentTypeConversionHash = toStringHash();

QStringList documentTypeStringValues()
{
    return documentTypeConversionHash.values();
}

QString documentTypeToString(const DocumentType& type)
{
    if(documentTypeConversionHash.contains(type)) {
        return documentTypeConversionHash[type];
    }

    return QString();
}

DocumentType stringToDocumentType(const QString& str)
{
    if(documentTypeConversionHash.values().contains(str)) {
        return documentTypeConversionHash.key(str);
    }

    return DocumentType::Unknown;
}
