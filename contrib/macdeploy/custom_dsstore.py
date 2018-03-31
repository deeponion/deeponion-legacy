#!/usr/bin/env python
# Copyright (c) 2013-2015 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.
from __future__ import division,print_function,unicode_literals
import biplist
from ds_store import DSStore
from mac_alias import Alias
import sys

output_file = sys.argv[1]
package_name_ns = sys.argv[2]

ds = DSStore.open(output_file, 'w+')
ds['.']['bwsp'] = {
    'ShowStatusBar': False,
    'WindowBounds': b'{{300, 280}, {500, 343}}',
    'ContainerShowSidebar': False,
    'SidebarWidth': 0,
    'ShowTabView': False,
    'PreviewPaneVisibility': False,
    'ShowToolbar': False,
    'ShowSidebar': False,
    'ShowPathbar': True
}

icvp = {
    'gridOffsetX': 0.0,
    'textSize': 12.0,
    'viewOptionsVersion': 1,
    'backgroundColorBlue': 1.0,
    'iconSize': 96.0,
    'backgroundColorGreen': 1.0,
    'arrangeBy': 'none',
    'showIconPreview': True,
    'gridSpacing': 100.0,
    'gridOffsetY': 0.0,
    'showItemInfo': False,
    'labelOnBottom': True,
    'backgroundType': 2,
    'backgroundColorRed': 1.0
}
alias = Alias.from_bytes(icvp['backgroundImageAlias'])
alias.volume.name = package_name_ns
alias.volume.posix_path = '/Volumes/' + package_name_ns
alias.volume.disk_image_alias.target.filename = package_name_ns + '.temp.dmg'
alias.volume.disk_image_alias.target.carbon_path = 'Macintosh HD:Users:\x00deeponionuser:\x00Documents:\x00deeponion:\x00deeponion:\x00' + package_name_ns + '.temp.dmg'
alias.volume.disk_image_alias.target.posix_path = 'Users/deeponionuser/Documents/deeponion/deeponion/' + package_name_ns + '.temp.dmg'
ds['.']['icvp'] = icvp

ds['.']['vSrn'] = ('long', 1)

ds['Applications']['Iloc'] = (370, 156)
ds['DeepOnion-Qt.app']['Iloc'] = (128, 156)

ds.flush()
ds.close()