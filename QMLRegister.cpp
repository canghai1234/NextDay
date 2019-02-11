#include "QMLRegister.h"
#include "Backend.h"

void QMLRegister::registerToQML()
{
    Backend::getSingleton()->initNetworkModel();
    qmlRegisterSingletonType<Backend>("NextDay",0,1,"Backend",backendProvider);
}
