/* 
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *  
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of version 2 of the GNU General Public License as published by 
 * the Free Software Foundation.
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License along with this program; 
 * If not, see <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>.
 * 
 * To contact us about this file by physical or electronic mail, 
 * you may find current contact information at https://www.uniontech.com/.
 */

#include "util.h"
#include <fstream>

void split(const string& s, vector<string>& tokens, const string& delimiters)
{
    string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos) {
        tokens.push_back(s.substr(lastPos, pos - lastPos));//use emplace_back after C++11
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
}

void getRepoInfo(Snapshot& snap) {
    string repo = snap.repo;
    string dfCmd = "df " + repo + " | awk 'END {print}'";
    SystemCmd cmd(dfCmd);
    if (cmd.retcode()) {
        for (auto out : cmd.stderr()) {
            cerr << out << endl;
        }
        return;
    }
    string result = cmd.stdout().front();
    vector<string> tmp;
    split(result, tmp);
    if (tmp.size() < 6) {
        return;
    }
    snap.repoDevice = tmp[0];
    snap.repoMount = tmp[5];
}

Snapshot setSnap(const string& repo, const string& snapshotID, backupType type) {
    Snapshot snap;
    snap.repo = repo;
    snap.snapshotID = snapshotID;
    snap.time = time(0);
    snap.type = type;
    getRepoInfo(snap);
    return snap;
}

Log setLog(const string& repo, const string& snapshotID, operationType type, bool status, string comment) {
    Log log;
    log.operationTime = time(0);
    log.opType = type;
    log.repo = repo;
    log.snaps.push_back(snapshotID);
    log.status = status;
    log.comment = comment;
    return log;
}

bool createFile(string fileName) {
    ofstream file;
    file.open(fileName);
    if (!file.is_open()) {
        return false;
    }
    return true;
}