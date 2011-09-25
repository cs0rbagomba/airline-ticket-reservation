#include "filedatabase.h"

FileDataBase::FileDataBase(const QString filePath) :
    m_filePath(filePath),
    m_fileIsLoaded(false),
    m_domDoc("AirLine_Seat_Allocation"),
    m_watcher()
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

    // remove node it exists
    /// @note smartness needed: can I modify existing ones?
    int found(-1);
    for (unsigned int i = 0; i < nodes.length(); i++) {
        QDomElement e = nodes.item(i).toElement();
        if(!e.isNull() && e.attribute("id") == id) {
            found = i;
        }
    }
    if (found != -1) {
        docElem.removeChild(nodes.item(found));
    }

    // add node
    QDomElement cn = m_domDoc.createElement("seat");
    cn.setAttribute( "id", id);
    cn.setAttribute( "taken", taken);
    docElem.appendChild(cn);

    // write back DomDocument to file
    QFile file(m_filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        emit notification("Couldn't open file to write.");
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

        // listen to modifications
        m_watcher.addPath(m_filePath);

        connect(&m_watcher, SIGNAL(fileChanged(const QString&)),
                this, SLOT(fileModified(const QString&)));
    }

    if (m_seats.find(id) != m_seats.end()) {
        taken = m_seats[id];
        return true;
    }

    /// @note Or return writeData(id,taken) ?
    return false;
}

void FileDataBase::fileModified(const QString& path)
{
    Q_UNUSED(path)

    loadData(true);
}

bool FileDataBase::loadData(const bool calculateDiff)
{
    QFile file(m_filePath);

    // open file
    if (!file.exists()) {
        if (!initFile()) {
            return false;
        }
    }

    if (!file.open(QIODevice::ReadOnly)) {
        emit notification("Couldn't read file.");
        return false;
    }

    // load DomDoc
    if (!m_domDoc.setContent(&file)) {
        emit notification("Couldn't parse XML file.");
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

            QString id(e.attribute("id"));
            bool taken(e.attribute("taken") == "1" ? true : false);

            if (calculateDiff) {
                if (m_seats.find(id) == m_seats.end() || m_seats[id] != taken) {

                    // value has to be set before emitting the signal
                    m_seats[id] = taken;
                    emit dataChanged(id);
                }
            } else {
                m_seats[id] = taken;
            }
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
        emit notification("Couldn't create new file.");
        return false;
    }
    QTextStream ts( &file );
    ts << m_domDoc.toString();
    file.close();

    return true;
}
