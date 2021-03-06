#!/bin/bash
# Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
#  
# This program is free software; you can redistribute it and/or modify
# it under the terms of version 2 of the GNU General Public License as published by 
# the Free Software Foundation.
#  
# This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; 
# without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
# See the GNU General Public License for more details.
#  
# You should have received a copy of the GNU General Public License along with this program; 
# If not, see <http://www.gnu.org/licenses/old-licenses/gpl-2.0.html>.
# 
# To contact us about this file by physical or electronic mail, 
# you may find current contact information at https://www.uniontech.com/.

# called by dracut
check() {
    return 0
}

# called by dracut
depends() {
    return 0
}

# called by dracut
install() {
    # change permition 
    #[[ -x $initdir/usr/bin/ubackup_restore ]] && return
    inst /etc/ubackup/profile.d/ubackuplib.sh
    inst /usr/bin/ubackup_restore
    inst_script /etc/ubackup/service/ubackup-restore.service /usr/lib/systemd/system/ubackup-restore.service
}

