// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The SKT developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "bitcoinunits.h"

#include <QStringList>

BitcoinUnits::BitcoinUnits(QObject *parent):
        QAbstractListModel(parent),
        unitlist(availableUnits())
{
}

QList<BitcoinUnits::Unit> BitcoinUnits::availableUnits()
{
    QList<BitcoinUnits::Unit> unitlist;
    unitlist.append(BSD);
    unitlist.append(mBSD);
    unitlist.append(uBSD);
    unitlist.append(limes);
    return unitlist;
}

bool BitcoinUnits::valid(int unit)
{
    switch(unit)
    {
    case BSD:
    case mBSD:
    case uBSD:
    case limes:
        return true;
    default:
        return false;
    }
}

QString BitcoinUnits::name(int unit)
{
    if(!TestNet() && !RegTest())
    {
        switch(unit)
        {
            case BSD: return QString("BSD");
            case mBSD: return QString("mBSD");
            case uBSD: return QString::fromUtf8("μBSD");
            case limes: return QString::fromUtf8("limes");
            default: return QString("???");
        }
    }
    else
    {
        switch(unit)
        {
            case BSD: return QString("tBSD");
            case mBSD: return QString("mtBSD");
            case uBSD: return QString::fromUtf8("μtBSD");
            case limes: return QString::fromUtf8("tlimes");
            default: return QString("???");
        }
    }
}

QString BitcoinUnits::description(int unit)
{
    if(!TestNet() && !RegTest())
    {
        switch(unit)
        {
            case BSD: return QString("SKT");
            case mBSD: return QString("Milli-SKT (1 / 1,000)");
            case uBSD: return QString("Micro-SKT (1 / 1,000,000)");
            case limes: return QString("Ten Nano-SKT (1 / 100,000,000)");
            default: return QString("???");
        }
    }
    else
    {
        switch(unit)
        {
            case BSD: return QString("TestSKTs");
            case mBSD: return QString("Milli-TestSKT (1 / 1,000)");
            case uBSD: return QString("Micro-TestSKT (1 / 1,000,000)");
            case limes: return QString("Ten Nano-TestSKT (1 / 100,000,000)");
            default: return QString("???");
        }
    }
}

qint64 BitcoinUnits::factor(int unit)
{
    switch(unit)
    {
    case BSD:  return 100000000;
    case mBSD: return 100000;
    case uBSD: return 100;
    case limes: return 1;
    default:   return 100000000;
    }
}

qint64 BitcoinUnits::maxAmount(int unit)
{
    switch(unit)
    {
    case BSD:  return Q_INT64_C(525000000); //sktdev 04-2015
    case mBSD: return Q_INT64_C(525000000000);   //sktdev 04-2015
    case uBSD: return Q_INT64_C(525000000000000); //sktdev 04-2015
    case limes: return Q_INT64_C(52500000000000000);    //sktdev 04-2015
    default:   return 0;
    }
}

int BitcoinUnits::amountDigits(int unit)
{
    switch(unit)
    {
    case BSD: return 8; // 21,000,000 (# digits, without commas)
    case mBSD: return 11; // 21,000,000,000
    case uBSD: return 14; // 21,000,000,000,000
    case limes: return 16; // 2,100,000,000,000,000
    default: return 0;
    }
}

int BitcoinUnits::decimals(int unit)
{
    switch(unit)
    {
    case BSD: return 8;
    case mBSD: return 5;
    case uBSD: return 2;
    case limes: return 0;
    default: return 0;
    }
}

QString BitcoinUnits::format(int unit, qint64 n, bool fPlus)
{
    // Note: not using straight sprintf here because we do NOT want
    // localized number formatting.
    if(!valid(unit))
        return QString(); // Refuse to format invalid unit
    qint64 coin = factor(unit);
    int num_decimals = decimals(unit);
    qint64 n_abs = (n > 0 ? n : -n);
    qint64 quotient = n_abs / coin;
    qint64 remainder = n_abs % coin;
    QString quotient_str = QString::number(quotient);
    QString remainder_str = QString::number(remainder).rightJustified(num_decimals, '0');

    // Right-trim excess zeros after the decimal point
    int nTrim = 0;
    for (int i = remainder_str.size()-1; i>=2 && (remainder_str.at(i) == '0'); --i)
        ++nTrim;
    remainder_str.chop(nTrim);

    if (n < 0)
        quotient_str.insert(0, '-');
    else if (fPlus && n > 0)
        quotient_str.insert(0, '+');

    if (num_decimals <= 0)
        return quotient_str;

    return quotient_str + QString(".") + remainder_str;
}

QString BitcoinUnits::formatWithUnit(int unit, qint64 amount, bool plussign)
{
    return format(unit, amount, plussign) + QString(" ") + name(unit);
}

bool BitcoinUnits::parse(int unit, const QString &value, qint64 *val_out)
{
    if(!valid(unit) || value.isEmpty())
        return false; // Refuse to parse invalid unit or empty string
    int num_decimals = decimals(unit);
    QStringList parts = value.split(".");

    if(parts.size() > 2)
    {
        return false; // More than one dot
    }
    QString whole = parts[0];
    QString decimals;

    if(parts.size() > 1)
    {
        decimals = parts[1];
    }
    if(decimals.size() > num_decimals)
    {
        return false; // Exceeds max precision
    }
    bool ok = false;
    QString str = whole + decimals.leftJustified(num_decimals, '0');

    if(str.size() > 18)
    {
        return false; // Longer numbers will exceed 63 bits
    }
    qint64 retvalue = str.toLongLong(&ok);
    if(val_out)
    {
        *val_out = retvalue;
    }
    return ok;
}

int BitcoinUnits::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return unitlist.size();
}

QVariant BitcoinUnits::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row >= 0 && row < unitlist.size())
    {
        Unit unit = unitlist.at(row);
        switch(role)
        {
        case Qt::EditRole:
        case Qt::DisplayRole:
            return QVariant(name(unit));
        case Qt::ToolTipRole:
            return QVariant(description(unit));
        case UnitRole:
            return QVariant(static_cast<int>(unit));
        }
    }
    return QVariant();
}