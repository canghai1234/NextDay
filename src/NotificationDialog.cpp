#include "NotificationDialog.h"

void NotificationDialog::insertNotify(int type, QString string)
{
    emit sig_newNotify(type,string);
}
