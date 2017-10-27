#!/usr/bin/env python
# -*- coding: utf-8 -*-

def verify_file_sort(file_name, is_greater = True):
    ret = True
    previous = 0;
    current = 0;

    try:
        fp = open(file_name)
        first_line = fp.readline()
        if first_line:
            previous = int(first_line)

            line = fp.readline()
            while line:
                current = int(line)
                if (current >= previous) ^ is_greater:
                    print "previous %d, current %d and sort order %d" %(previous, current, is_greater)
                    ret = False
                    break

                line = fp.readline()
                previous = current

    except Exception, e:
        print e

    return ret

def main():
    if verify_file_sort('2.txt'):
        print "sort order ok"
    else:
        print "sort order error"

if __name__ == '__main__':
    main()
