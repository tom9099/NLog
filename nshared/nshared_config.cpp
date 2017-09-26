#include "nshared_config.h"

#include <QMutexLocker>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>

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

    if (!f.open(QFile::ReadOnly | QFile::Text))
        return;

    QString text = in.readAll();    
    std::string std_string{text.toStdString()};

    doc.parse<0>((char *)std_string.c_str());

    qDebug() << doc.first_node()->name() << "\n";
    rapidxml::xml_node<> *node = doc.first_node("cfg");

    for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
    {
        QString key{""};
        QString value{""};

        for (rapidxml::xml_attribute<> *attr = child->first_attribute(); attr; attr = attr->next_attribute())
        {
            qDebug() << "Node " <<  child->name() << " has attribute " << attr->name() << " " << "with value " << attr->value() << "\n";

            if (QString::compare(attr->name(), "key") == 0)
            {
                key = attr->value();
            }

            if (QString::compare(attr->name(), "value") == 0)
            {
                value = attr->value();
            }
        }

        if (key.length())
        {
            mProperties[key] = value;
        }
    }
}

NConfig& NConfig::it()
{
    static NConfig instance;
    return instance;
}


int NConfig::getInt32(const QString &name, int defaultValue)
{
    auto it = mProperties.find(name);
    if (it != mProperties.end())
    {
        return it->toInt();
    }
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
