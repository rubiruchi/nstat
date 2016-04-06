#! /usr/bin/env python3.4

import sys
import os

CONTROLLER_DIR_NAME = 'distribution-karaf-0.3.2-Lithium-SR2'

def change_persistent():
    """Takes as command line argument the new interval of statistics period we
    want to set in the configuration file of the controller and writes it in
    this file.
    """

    string_to_find = '#persistent=true'
    string_to_replace = 'persistent=false'
    filedata = ''
    input_file = os.path.sep.join([os.path.dirname(os.path.realpath(__file__)),
        CONTROLLER_DIR_NAME, 'etc', 'org.opendaylight.controller.cluster.datastore.cfg'])
    with open(input_file, 'rb') as f:
        filedata = f.read().decode('utf-8')
    if filedata == '':
        print('[change_persistent] Fail to read file')
        sys.exit(1)
    filedata = filedata.replace(string_to_find, string_to_replace)
    try:
        f = open(input_file, 'wb')
        f.write(filedata.encode('utf-8'))
        f.close()
    except:
        print('[change_persistent] Fail to write file')
        sys.exit(1)

if __name__ == '__main__':
    change_persistent()