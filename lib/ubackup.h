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

#ifndef __UBACKUP_H
#define __UBACKUP_H

#include <string>
#include <ctime>
#include <vector>

using namespace std;
namespace ubackup{

struct Error {
    int errNo;
    string error;

    Error()
    {
        errNo = 0;
        error = "";
    }
};

enum backupType {
    Full = 0,
    System,
    Data,
};

struct Snapshot {
    string snapshotID;
    time_t time;
    size_t size;
    backupType type;
    string repo;
    string repoDevice;
    string repoMount;
};

struct Repo {
    string repo;
    string device;
    string mount;
};

enum operationType {
    FullBackup = 0,
    SystemBackup,
    DataBackup,
    FullRestore,
    SystemRestore,
    DataRestore,
    RemoveSnaps,
};

struct Log {
    time_t operationTime;
//    vector<Snapshot> snaps;
    vector<string> snaps;
    operationType opType;
    bool status;
    string repo;
    string comment;
};

/**
 * BackupFull: 整机备份，忽略临时目录和用户手动排除的目录。
 * repo: 备份存储的位置
 * excludes: 用户手动输入的排除目录，函数内部校验，部分目录不能排除
 * snapshotID: 输出参数，备份完成后返回的备份ID
 * comment： 对本次备份的备注
 * 
 * */
Error BackupFull(vector<string>& excludes, string& snapshotID, string repo="", string comment="");

}
#endif /* __UBACKUP_H */