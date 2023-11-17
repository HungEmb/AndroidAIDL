#define LOG_TAG "apck_testapp"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <aidl/apck/hardware/apckdemo/IApckDemo.h>
#include <android/log.h>

#include <unistd.h>
#include <set>

#define SERVICE_NAME "apck.hardware.apckdemo.IApckDemo/default"

using aidl::apck::hardware::apckdemo::IApckDemo;
using ndk::ScopedAStatus;
using ndk::SpAIBinder;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("How to use: apck_client msg\n");
        return -1;
    }
    std::shared_ptr<IApckDemo> apckdemo;
    std::string retMsg = argv[1];
    apckdemo = IApckDemo::fromBinder(
                SpAIBinder(AServiceManager_waitForService(SERVICE_NAME)));
    if (apckdemo == nullptr) {
        printf("Can't get the ApckDemo service\n");
    }

    if (!apckdemo->putChars(argv[1]).isOk()) {
        printf("Can't request the ApckDemo service");
    }
    printf("Requested the ApckDemo service with message [%s]\n", argv[1]);

    if (!apckdemo->getChars(&retMsg).isOk()) {
        printf("Can't get message from the ApckDemo service\n");
    }
    printf("Get message from ApckDemo service [%s]\n", retMsg.c_str());

    return 0;
}
