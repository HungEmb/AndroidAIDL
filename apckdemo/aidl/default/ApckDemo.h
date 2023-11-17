#pragma once

#include <aidl/apck/hardware/apckdemo/BnApckDemo.h>

#define DEF_NUM_CHARS	20

namespace aidl {
namespace apck {
namespace hardware {
namespace apckdemo {

class ApckDemo : public BnApckDemo {
public:
	ApckDemo();
	~ApckDemo();
	ndk::ScopedAStatus getChars(std::string* _aidl_return);
	ndk::ScopedAStatus putChars(const std::string& in_msg);

private:
	size_t mCharsLen;
	char *mChars;
};

}
}
}
}
