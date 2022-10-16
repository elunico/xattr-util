import os
from shlex import quote as shesc
from subprocess import getstatusoutput

import dialog

term_size = os.get_terminal_size()
term_width, term_height = term_size.columns, term_size.lines


class CustomDialog:
    def __init__(self):
        self.d = dialog.Dialog()

    def __getattr__(self, item):
        fn = getattr(self.d, item)

        if not callable(fn):
            return fn

        def wrapper(*args, **kwargs):
            return fn(*args, **kwargs, width=term_width - 12, height=term_height - 16)

        return wrapper


d = CustomDialog()


def set_new_value(file, key, placeholder=''):
    b, value = d.inputbox(text='Enter value for "{}"'.format(key), init=placeholder)
    if b == d.CANCEL:
        return False

    status, output = getstatusoutput('xattr -w {} {} {}'.format(shesc(key), shesc(value), shesc(file)))
    if status:
        d.msgbox("Error on {}:\nCould not set {} to {}:\n{}".format(file, key, value, output))
        return False
    else:
        d.msgbox('Done with {}!\n{}={}'.format(file, key, value))
        return True


def main():
    root = os.getcwd()
    while True:
        dir_button, root = d.fselect(root)
        if dir_button == d.CANCEL:
            return

        while True:
            status, attr_names = getstatusoutput('xattr {}'.format(root))
            if status:
                d.msgbox('Error retrieving xattrs for {}:\n{}'.format(root, attr_names))
                return

            attr_names = attr_names.split('\n')
            attr_button, choice = d.menu(text="Choose an attribute to modify", choices=[
                ('<new>', '<new>'),
                *zip(attr_names, attr_names)
            ])

            if attr_button == d.CANCEL:
                break

            if choice == '<new>':
                b, key = d.inputbox(text="Enter attribute name")
                if b == d.CANCEL:
                    break
                if not set_new_value(root, key):
                    break
            else:
                status, output = getstatusoutput('xattr -p {} {}'.format(shesc(choice), shesc(root)))
                if status:
                    d.msgbox("Error on {}:\nCould not read {}:\n{}".format(root, choice, output))
                    break
                else:
                    if not set_new_value(root, choice, placeholder=output):
                        break


if __name__ == '__main__':
    raise SystemExit(main())
