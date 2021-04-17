// 4/16/21a, BeckIncludeOptionalFiles.h
//Optional #includes for BeckE32_Biota.ino

  #if DO_OTA
    #include <BeckOTALib.h>
  #endif

  #if DO_WEB_SERVER
    #include <BeckWebPages.h>
    #include <BeckWebServer.h>
  #endif

  #if DO_ALEXA
    #include <BeckAlexaClass.h>
  #endif

  #if DO_ACCESS_POINT
    #include <BeckAccessPointLib.h>
  #endif

  #if DO_NTP
    #include <BeckNTPLib.h>
  #endif

  #if DO_FIREBASE
    #include <FirebaseArduino.h>
    #include <ArduinoJson.h>
    #include <ESP8266HTTPClient.h>

   /*
    #define FIREBASE_HOST   "//test-70884.firebaseio.com"
    #define FIREBASE_HOST   "https://test-70884.firebaseio.com"

    #define FIREBASE_HOST   "https://test-70884.firebaseio.com/"
    #define FIREBASE_AUTH   "AIzaSyD-Nm1dYBV6ehphAOQgkM5sz4oYLKF9ahg"
    */
    #define FIREBASE_HOST   "https://thermo-2b830.firebaseio.com/"
    #define FIREBASE_AUTH   "AIzaSyAkFumb-wjDUQ9HQjTOoHeXqTKztFSqf6o"
  #endif  //DO_FIREBASE

  #if USE_IMU
    //static const  uint32_t    ulMPU9150HandlerPeriodMsec  = 200;
    static const  uint32_t    ulMPU9150HandlerPeriodMsec  = 0;
    static const  uint32_t    ulMPU9150DisplayPeriodMsec  = 1000;
    static        uint32_t    ulNextMPU9150DisplayMsec    = 0;
    static        bool        bMPU9150_On;
  #endif
