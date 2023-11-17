#include "ApckDemo.h"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using aidl::apck::hardware::apckdemo::ApckDemo;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    std::shared_ptr<ApckDemo> apckdemo = ndk::SharedRefBase::make<ApckDemo>();

    const std::string instance = std::string() + ApckDemo::descriptor + "/default";
    binder_status_t status = AServiceManager_addService(apckdemo->asBinder().get(), instance.c_str());
    CHECK_EQ(status, STATUS_OK);

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reached
}
