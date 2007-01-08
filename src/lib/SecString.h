/***************************************************************************
 *   Copyright (C) 2005 by Tarek Saidi                                     *
 *   tarek@linux                                                           *
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
#ifndef _SECSTRING_H_
#define _SECSTRING_H_

#include <QByteArray>
#include <qstring.h>
#include <qglobal.h>
#include "crypto/arcfour.h"

class SecString{
public:
 SecString();
 ~SecString();
 void setString(QString& str, bool DelSrc=false);
 void lock();
 void unlock();
 const QString& string();
 operator QString();
 int length();

 static void overwrite(unsigned char* str,int len);
 static void overwrite(QString& str);
 static void generateSessionKey();

private:
 bool locked;
 static CArcFour RC4;
 QByteArray crypt;
 QString plain;

};


#endif
