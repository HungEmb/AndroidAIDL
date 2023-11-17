# ApckDemo - aospcook demo for HALs AIDL
From unstable version:

### 1. Remove ```unstable: true``` and add:
```
    stability: "vintf",
    owner: "apck",
```
in aidl Android.bp

### 2. Add  ```@VintfStability``` in *.aidl file.
```
package apck.hardware.apckdemo;

@VintfStability
interface IApckDemo {
    String getChars();
    void putChars(in String msg);
}
```
### 3. Run ```mm``` to rebuild , it will gen this error:
```
FAILED: out/soong/.intermediates/hardware/interfaces/apckdemo/aidl/apck.hardware.apckdemo-api/checkapi_current.tim
estamp
echo "API dump for the current version of AIDL interface apck.hardware.apckdemo does not exist." && echo Run "m ap
ck.hardware.apckdemo-update-api", or add "unstable: true" to the build rule for the interface if it does not need 
to be versioned && false # hash of input list: e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
API dump for the current version of AIDL interface apck.hardware.apckdemo does not exist.
Run m apck.hardware.apckdemo-update-api, or add unstable: true to the build rule for the interface if it does not 
need to be versioned
00:15:22 ninja failed with: exit status 1
```
After this step, aidl_api folder is created with stable aidl files inside

### 4. Run ```m apck.hardware.apckdemo-update-api``` to fix above error
### 5. ```mm``` again. All success
Check ```ls out/soong/.intermediates/hardware/interfaces/apckdemo/aidl/```
```
apck.hardware.apckdemo-api            apck.hardware.apckdemo-V1-java         default
apck.hardware.apckdemo_interface      apck.hardware.apckdemo-V1-java-source  testapp
apck.hardware.apckdemo-V1-cpp         apck.hardware.apckdemo-V1-ndk
apck.hardware.apckdemo-V1-cpp-source  apck.hardware.apckdemo-V1-ndk-source
```
NDK, cpp and java backends version is generated.

### 6. ```apck.hardware.apckdemo-ndk``` to ```apck.hardware.apckdemo-V1-ndk``` in service Android.bp (in default/),
Build service and flash to board, VINTF error in logcat occurs:
```
01-01 00:00:10.908   153   153 E SELinux : avc:  denied  { add } for pid=258 uid=1000 name=apck.hardware.apckdemo.IApckDemo/default scontext=u:r:shell:s0 tcontext=u:object_r:default_android_service:s0 tclass=service_manager permissive=1
01-01 00:00:10.908   153   153 I servicemanager: Could not find apck.hardware.apckdemo.IApckDemo/default in the VINTF manifest.
01-01 00:00:10.909   258   258 F apck.hardware.apckdemo-service: Check failed: status == STATUS_OK (status=-3, STATUS_OK=0) 
01-01 00:00:10.910   258   258 F libc    : Fatal signal 6 (SIGABRT), code -1 (SI_QUEUE) in tid 258 (apck.hardware.a), pid 258 (apck.hardware.a)
01-01 00:00:11.405   281   281 F DEBUG   : Cmdline: /vendor/bin/hw/apck.hardware.apckdemo-service
01-01 00:00:11.405   281   281 F DEBUG   : pid: 258, tid: 258, name: apck.hardware.a  >>> /vendor/bin/hw/apck.hardware.apckdemo-service <<<
01-01 00:00:11.406   281   281 F DEBUG   :       #03 pc 00000000000027e4  /vendor/bin/hw/apck.hardware.apckdemo-service (main+644) (BuildId: a4c4a4885216e334f7f385770b17d423)
```

### 7. Add vintf manifest, the error is resolved:
```
01-01 00:00:10.991   261   261 I apck.hardware.a: type=1400 audit(0.0:11): avc: denied { open } for path="/vendor/lib64/apck.hardware.apckdemo-V1-ndk.so" dev="mmcblk0p3" ino=121 scontext=u:r:shell:s0 tcontext=u:object_r:vendor_file:s0 tclass=file permissive=1
01-01 00:00:11.083   156   156 E SELinux : avc:  denied  { add } for pid=261 uid=1000 name=apck.hardware.apckdemo.IApckDemo/default scontext=u:r:shell:s0 tcontext=u:object_r:default_android_service:s0 tclass=service_manager permissive=1
01-01 00:00:11.083   156   156 I servicemanager: Found apck.hardware.apckdemo.IApckDemo/default in device VINTF manifest.
```

### 8. Revise ```apck.hardware.apckdemo-ndk``` to ```apck.hardware.apckdemo-V1-ndk``` in testapp Android.bp and re-test.
All should works well !
