#include "paint2.h"
#include "paint2Plugin.h"

#include <QtCore/QtPlugin>

paint2Plugin::paint2Plugin(QObject *parent)
    : QObject(parent)
{
    initialized = false;
}

void paint2Plugin::initialize(QDesignerFormEditorInterface * /*core*/)
{
    if (initialized)
        return;

    initialized = true;
}

bool paint2Plugin::isInitialized() const
{
    return initialized;
}

QWidget *paint2Plugin::createWidget(QWidget *parent)
{
    return new paint2(parent);
}

QString paint2Plugin::name() const
{
    return "paint2";
}

QString paint2Plugin::group() const
{
    return "My Plugins";
}

QIcon paint2Plugin::icon() const
{
    return QIcon();
}

QString paint2Plugin::toolTip() const
{
    return QString();
}

QString paint2Plugin::whatsThis() const
{
    return QString();
}

bool paint2Plugin::isContainer() const
{
    return false;
}

QString paint2Plugin::domXml() const
{
    return "<widget class=\"paint2\" name=\"paint2\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>100</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QString paint2Plugin::includeFile() const
{
    return "paint2.h";
}
