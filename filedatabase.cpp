#include "filedatabase.h"

FileDataBase::FileDataBase(const QString filePath) :
    m_filePath(filePath),
    m_fileIsLoaded(false),
    m_domDoc("AirLine_Seat_Allocation"),
    m_watcher(QStringList(filePath))
{

}

FileDataBase::~FileDataBase()
{

}


bool FileDataBase::writeData(const QString id, const bool taken)
{
    // first read? lazy file loading
    if (!m_fileIsLoaded) {
        if (!loadData()) {
            return false;
        }
    }

    // update internal DB
    m_seats[id] = taken;

    // update DomDocument
    QDomElement docElem = m_domDoc.documentElement();
    QDomNodeList nodes = docElem.childNodes();
    bool found(false);
    for (unsigned int i = 0; i < nodes.length(); i++) {
        QDomElement e = nodes.item(i).toElement();
        if(!e.isNull() && e.attribute("id") == id) {
            e.attribute("taken") = taken;
            found = true;
        }
    }

    if (!found) {
        QDomElement cn = m_domDoc.createElement("seat");
        cn.setAttribute( "id", id);
        cn.setAttribute( "taken", taken);
        docElem.appendChild(cn);
    }

    // write back DomDocument to file
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        // emit notification(tr("Couldn't open file to write."));
        return false;
    }
    QTextStream ts( &file );
    ts << m_domDoc.toString();
    file.close();

    return true;
}

bool FileDataBase::readData(const QString id, bool &taken)
{
    // first read? lazy file loading
    if (!m_fileIsLoaded) {
        if (!loadData()) {
            return false;
        }
    }

    if (m_seats.find(id) != m_seats.end()) {
        taken = m_seats[id];
        return true;
    }

    return false;
}

void FileDataBase::fileModified()
{

}

bool FileDataBase::loadData()
{
    QFile file(m_filePath);

    // open file
    if (!file.exists()) {
        initFile();
    }

    if (!file.open(QIODevice::ReadOnly)) {
        // emit notification("Couldn't read file.");
        return false;
    }

    // load DomDoc
    if (!m_domDoc.setContent(&file)) {
        // emit notification("Couldn't parse XML file.");
        file.close();
        return false;
    }
    file.close();

    // load internal DB
    QDomElement docElem = m_domDoc.documentElement();
    QDomNodeList nodes = docElem.childNodes();
    for (unsigned int i = 0; i < nodes.length(); i++) {
        QDomElement e = nodes.item(i).toElement();
        if(!e.isNull()) {
            m_seats[e.attribute("id")] = e.attribute("taken")== "1" ? 1 : 0;
        }
    }

    m_fileIsLoaded = true;
    return true;
}

bool FileDataBase::initFile()
{
    // create XML doc object
    QDomElement root = m_domDoc.createElement("Seats");
    m_domDoc.appendChild(root);

    // write XML doc object to file
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        // emit notification(tr("Couldn't open file to write."));
        return false;
    }
    QTextStream ts( &file );
    ts << m_domDoc.toString();
    file.close();

    return true;
}
