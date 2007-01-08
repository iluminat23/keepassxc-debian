/***************************************************************************
 *   Copyright (C) 2005-2006 by Tarek Saidi                                *
 *   tarek.saidi@arcor.de                                                  *
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

#ifndef _PW_MANAGER_H_
#define _PW_MANAGER_H_
 #define DB_HEADER_SIZE 		124
 #define PWM_DBSIG_1			0x9AA2D903
 #define PWM_DBSIG_2			0xB54BFB65
 #define PWM_DBVER_DW  	 		0x00030002
 #define PWM_FLAG_SHA2			1
 #define PWM_FLAG_RIJNDAEL		2
 #define PWM_FLAG_ARCFOUR		4
 #define PWM_FLAG_TWOFISH		8
 #define PWM_STD_KEYENCROUNDS 	6000

#include <qcolor.h>
#include <qobject.h>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QStringList>
#include <QPixmap>
#include "lib/SecString.h"
#include "Database.h"


class PwDatabase:public Database{
 Q_OBJECT
public:
 PwDatabase();
 bool openDatabase(QString filename, QString& err);
 bool saveDatabase();
 bool closeDatabase();
 void newDatabase();
 bool CalcMasterKeyByPassword(QString& password);
 bool CalcMasterKeyByFile(QString filename);
 bool CalcMasterKeyByFileAndPw(QString filename, QString& password);
 bool createKeyFile(const QString& filename);

 CGroup&   group(unsigned long index);
 void	   setGroup(unsigned long index,CGroup& group);
 int	   numGroups();
 CGroup*   addGroup(CGroup* parent);
 void      deleteGroup(CGroup* pGroup);
 void      deleteGroup(unsigned long ID);
 void	   moveGroup(CGroup* group, CGroup* DstGroup, int pos=-1);
 void	   moveGroupDirectly(CGroup* group, CGroup* DstGroup); //inserts group directly behind DstGroup on the same level
 int	   getGroupIndex(CGroup* group);
 int       getGroupIndex(unsigned long ID);
 int	   getNumberOfChilds(CGroup* pGroup);
 QList<int> getChildIds(CGroup* pGroup);

 CEntry&   entry(unsigned long index);
 CEntry*   getEntry(const KpxUuid& uuid);
 void	   setEntry(unsigned long index,CEntry& Entry);
 int	   numEntries();
 CEntry*   cloneEntry(CEntry* pEntry);
 void      deleteEntry(CEntry* pEntry);
 void      moveEntry(CEntry* pEntry,CGroup* pDstGroup);
 CEntry*   addEntry();
 CEntry*   addEntry(CEntry* NewEntry);
 void 	   merge(Database* db2);
 bool	   isParentGroup(CGroup* Group,CGroup* PotenialParent);

 QString   getError();  //get first error
 QString   getErrors(); //get all errors in a \n seperated String
 QPixmap&  icon(int index);
 int	   numIcons();
 void	   addIcon(const QPixmap& icon);
 void	   removeIcon(int Id);
 void	   replaceIcon(int Id,const QPixmap& icon);

 QList<CGroup>Groups;
 QList<CEntry>Entries;
private:
 bool IsMetaStream(CEntry& Entry);
 bool parseMetaStream(const CEntry& Entry);
 bool parseCustomIconsMetaStream(const QByteArray& data);
 	bool parseCustomIconsMetaStreamV1(const QByteArray& data);
 void createCustomIconsMetaStream(CEntry* dst);
 void transformKey(quint8* src,quint8* dst,quint8* seed,int rounds);
 bool readHeader(char* raw);
 bool isGroupIdInUse(quint32 GroupID);
 bool isEntrySidInUse(quint32 sID);
 quint32 getNewGroupId();
 quint32 getNewEntrySid();
 bool convHexToBinaryKey(char* HexKey, char* dst);
 QStringList Errors;
 QList<QPixmap> CustomIcons;
 QList<CEntry> UnkownMetaStreams;

signals:
void iconsModified();

};



 void memcpyFromLEnd32(quint32* dst,const char* src);
 void memcpyFromLEnd16(quint16* dst,const char* src);
 void memcpyToLEnd32(char* src,const quint32* dst);
 void memcpyToLEnd16(char* src,const quint16* dst);
 QDateTime dateFromPackedStruct5(const unsigned char* pBytes);
 void dateToPackedStruct5(const QDateTime& datetime, unsigned char* dst);

 bool testDatabase();

#endif
