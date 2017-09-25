#include "nshared_config.h"

#include <QMutexLocker>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "xml/rapidxml.hpp"
#include "xml/rapidxml_iterators.hpp"
#include "xml/rapidxml_print.hpp"
#include "xml/rapidxml_utils.hpp"


NConfig::NConfig()
{
    QMutexLocker                    theLock(&mCfgMutex);
    rapidxml::xml_document<>        doc;
    QFile                           f("config.xml");
    QTextStream                     in(&f);

    loadDefault();

    if (!f.open(QFile::ReadOnly | QFile::Text))
        return;

    QString text = in.readAll();
    doc.parse<0>((char *)text.toStdString().c_str());

    qDebug() << doc.first_node()->name() << "\n";
    rapidxml::xml_node<> *node = doc.first_node("cfg");

    qDebug() << "Node cfg has value " << node->value() << "\n";
    for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute())
    {
        qDebug() << "Node foobar has attribute " << attr->name() << " " << "with value " << attr->value() << "\n";
    }
}

NConfig& NConfig::it()
{
    static NConfig instance;
    return instance;
}


int NConfig::getInt32(const QString &name, int defaultValue)
{
    return defaultValue;
}

void NConfig::loadDefault()
{
    mProperties.clear();

    mProperties["port"] = "9090";
}

void NConfig::init()
{

}

void NConfig::save()
{

}
