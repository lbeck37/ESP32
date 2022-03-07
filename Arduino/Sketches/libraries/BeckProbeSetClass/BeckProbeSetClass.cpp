const char szSystemFileName[]  = "BeckProbeSetClass.cpp";
const char szSystemFileDate[]  = "3/6/22b";

#include <BeckProbeSetClass.h>
#include <BeckProbeClass.h>
#include <BeckSampleDataClass.h>
#include <BeckE32_Defines.h>
#include <Streaming.h>

BeckProbeSetClass::BeckProbeSetClass() : _aucI2CAdresses{0, _ucI2CAddress1, _ucI2CAddress2, _ucI2CAddress3} {
  return;
} //constructor


BeckProbeSetClass::~BeckProbeSetClass() {
  Serial << "~BeckProbeSetClass(): Destructing" << endl;
} //destructor


void BeckProbeSetClass::BuildProbes(){
  double adProbeDegF[4];

  Serial << "BeckProbeSetClass::BuildProbes(): Construct probes " << endl;
  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
    uint8_t ucI2CAddress= _aucI2CAdresses[wProbe];

    Serial << "BeckProbeSetClass::BuildProbes(): Call BeckProbeClass(" << ucI2CAddress << ")" << endl;
    _aoProbes[wProbe]= BeckProbeClass(ucI2CAddress);

    Serial << "BeckProbeSetClass::BuildProbes(): Call _aoProbes[" << wProbe << "].Begin()" << endl;
    _aoProbes[wProbe].Begin();
    switch (wProbe) {
    case 1:
      _aoSampleData[wProbe]= BeckSampleDataClass(ProbePositionEnum::LeftProbe, ProbeSetLocationEnum::LeftFrontTire);
      break;
    case 2:
      _aoSampleData[wProbe]= BeckSampleDataClass(ProbePositionEnum::CenterProbe, ProbeSetLocationEnum::LeftFrontTire);
      break;
    case 3:
      _aoSampleData[wProbe]= BeckSampleDataClass(ProbePositionEnum::LeftProbe, ProbeSetLocationEnum::LeftFrontTire);
      break;
    default:
      Serial << "BuildProbes(): Hit Default switch, wProbe= " << wProbe << endl;
      break;
    } //switch
    //Serial << "BeckProbeSetClass::BuildProbes(): Do next probe in for loop" << endl;
   }
  Serial << "BeckProbeSetClass::BuildProbes(): return after 1 sec delay" << endl;
  delay(1000);
  return;
} //Handle

void BeckProbeSetClass::PrintProbeSetData(void) {
  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
    _aoSampleData[wProbe].FillSampleData(_uwSampleTime, _afProbeDegF[wProbe]);
    Serial << "PrintProbeSetData(): Printing data for Probe #" << wProbe << endl;
    Serial << "PrintProbeSetData(): Sample Time= " << _aoSampleData[wProbe].uwGetSampleTime() << ", DegF= " << _aoSampleData[wProbe].fGetDegF_Value() << endl;
    //Serial << "PrintProbeSetData(): Probe Position= " << _aoSampleData[wProbe].eGetProbePosition() << ", ProbeSet Location= " << _aoSampleData[wProbe].eGetProbeSetLocation() << endl;
   }
  return;
}

void BeckProbeSetClass::Handle(uint32_t uwSampleTime) {
  _uwSampleTime= uwSampleTime;
  //Have each Probe handle itself, like read the tcouple
  for (int wProbe= 1; wProbe <= _wNumProbes; wProbe++){
    _afProbeDegF[wProbe]= _aoProbes[wProbe].Handle();
    _aoSampleData[wProbe].FillSampleData(_uwSampleTime, _afProbeDegF[wProbe]);
   }
  Serial << "BeckProbeSetClass::Handle(): " << endl <<
      "    Thermo #1= " << _afProbeDegF[1] << "F, #2= " << _afProbeDegF[2] << "F, #3=" << _afProbeDegF[3] << endl;
  return;
} //Handle
//Last line.
