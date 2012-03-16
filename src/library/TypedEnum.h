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
 * along with Epic Framework.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TYPEDENUM_H_
#define TYPEDENUM_H_

#include <QString>
#include <QStringList>
#include <QHash>

template<typename Enum>
class TypedEnum : public Enum
{
    public:

        TypedEnum()
        : Enum(), mEnumValue(static_cast<typename Enum::Type>(0))
        {
        }

        TypedEnum(typename Enum::Type value)
        : Enum(), mEnumValue(value)
        {
        }

        TypedEnum(const TypedEnum<Enum>& value)
        : mEnumValue(value.mEnumValue)
        {
        }

        ~TypedEnum()
        {
        }

        TypedEnum<Enum>& operator=(const TypedEnum<Enum>& value)
        {
            mEnumValue = value.mEnumValue;

            return *this;
        }

        TypedEnum<Enum>& operator=(typename Enum::Type value)
        {
            mEnumValue = value;

            return *this;
        }

        bool operator==(const TypedEnum<Enum>& other)
        {
            return mEnumValue == other.mEnumValue;
        }

        bool operator==(typename Enum::Type value)
        {
            return mEnumValue == value;
        }

        bool operator!=(const TypedEnum<Enum>& other)
        {
            return mEnumValue != other.mEnumValue;
        }

        bool operator!=(typename Enum::Type value)
        {
            return mEnumValue != value;
        }

        QString toString() const
        {
            return mStringHash.value(static_cast<unsigned int>(mEnumValue));
        }

        unsigned int toUInt() const
        {
            return static_cast<unsigned int>(mEnumValue);
        }

        static TypedEnum<Enum> fromString(const QString& str)
        {
            typename Enum::Type v = static_cast<typename Enum::Type>(mStringHash.key(str));

            return TypedEnum<Enum>(v);
        }

        static TypedEnum<Enum> fromUInt(unsigned int value)
        {
            return TypedEnum<Enum>(static_cast<typename Enum::Type>(value));
        }

        static QStringList stringValues()
        {
            return mStringHash.values();
        }

    private:
        typename Enum::Type mEnumValue;
        static QHash<unsigned int, QString> mStringHash;
};

template<typename Enum> QHash<unsigned int, QString> TypedEnum<Enum>::mStringHash = Enum::toStringHash();

#endif /* TYPEDENUM_H_ */
