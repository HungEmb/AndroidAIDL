#define LOG_TAG "ApckDemo"


#include <utils/Log.h>
#include "ApckDemo.h"

namespace aidl {
namespace apck {
namespace hardware {
namespace apckdemo {

ApckDemo::ApckDemo() {
	mCharsLen = DEF_NUM_CHARS;
	mChars = new char[mCharsLen];
}

ApckDemo::~ApckDemo() {
	delete[] mChars;
}

::ndk::ScopedAStatus ApckDemo::getChars(std::string* _aidl_return) {
	ALOGI("getChars: Sent [%s] inversed to client", mChars);
	*_aidl_return = mChars;
	return ndk::ScopedAStatus::ok();
}

::ndk::ScopedAStatus ApckDemo::putChars(const std::string& in_msg) {
	size_t msgLen = in_msg.length();
	if(msgLen > mCharsLen) {
		delete[] mChars;
		mChars = new char[msgLen];
		mCharsLen = msgLen;
	}
	memset(mChars, 0, mCharsLen);
	strcpy(mChars, in_msg.c_str());

	for(int i = 0; i < msgLen; i++) {
		if (mChars[i] >= 97 && mChars[i] <= 122)
			mChars[i] = mChars[i] - 32;
		else if (mChars[i] >= 65 && mChars[i] <= 90)
			mChars[i] = mChars[i] + 32;
		else
			continue;
	}

	ALOGI("putChars: Get [%s] from client and inversed to [%s]", in_msg.c_str(), mChars);
	return ndk::ScopedAStatus::ok();
}

}
}
}
}



