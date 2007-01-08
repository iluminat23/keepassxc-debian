/***************************************************************************
 *   Copyright (C) 2005 by Tarek Saidi                                     *
 *   mail@tarek-saidi.de                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _IMPORT_PWMANAGER_
#define _IMPORT_PWMANAGER_
#include <qdom.h>
#include <qstring.h>
#include "PwManager.h"

class Import_PwManager{
public:
bool importFile(QString FileName, QString Password,Database* db,QString& err);
private:
 bool KeyFlag; // true=Password, false=Chipcard
 int Compression; // 0=none, 1=gzip, 2=bzip2
 unsigned char KeyHash[20];
 unsigned char DataHash[20];
 Database* database;

 bool parseXmlContent(char* content);
 bool xml_parseEntryAttributes(QDomElement* EntryTag,CGroup* parent);
};

#endif
