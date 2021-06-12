const char szCreateDisplayDataName[]  = "BeckCreateDisplayData.cpp";
const char szszCreateDisplayDataDate[]  = "6/10/21b";
#include <BeckCreateDisplayData.h>
#include <BeckLogLib.h>
#include <Streaming.h>

const SegmentData& CreateSegmentData(BarType eBarType, SegmentPosition eSegmentPosition){
  SegmentData*          pSegmentData        = new SegmentData;
  SegmentData           &SegData     = *pSegmentData;

  switch(eBarType) {
  case eCO2Bar:
    switch(eSegmentPosition){
    case eFirstSegment:
      strcpy(SegData.BarName  , "CO2");
      strcpy(SegData.ColorName, "Green");
      SegData.StartPercent     = 0;
      SegData.Color            = BECK_GREEN;
      SegData.fStartValue      =   0.0;
      SegData.fEndValue        = 600.0;
      SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
      SegData.XLeft            = CO2_XLEFT + CO2_GREEN_START;
      SegData.YBottom          = CO2_YBOTTOM;
      SegData.Length           = CO2_YELLOW_START - CO2_GREEN_START;
      break;
    case eSecondSegment:
      strcpy(SegData.BarName  , "CO2");
      strcpy(SegData.ColorName, "Yellow");
      SegData.StartPercent     = 33;
      SegData.Color            = BECK_YELLOW;
      SegData.fStartValue      =  600.0;
      SegData.fEndValue        = 1000.0;
      SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
      SegData.XLeft            = CO2_XLEFT + CO2_YELLOW_START;
      SegData.YBottom          = CO2_YBOTTOM;
      SegData.Length           = CO2_RED_START - CO2_YELLOW_START;
      break;
    case eThirdSegment:
      strcpy(SegData.BarName  , "CO2");
      strcpy(SegData.ColorName, "Red");
      SegData.StartPercent     = 66;
      SegData.Color            = BECK_RED;
      SegData.fStartValue      = 1000.0;
      SegData.fEndValue        = 2000.0;
      SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
      SegData.XLeft            = CO2_XLEFT + CO2_RED_START;
      SegData.YBottom          = CO2_YBOTTOM;
      SegData.Length           = BAR_LENGTH - CO2_RED_START;
      break;
    default:
      Serial << LOG0 << "CreateSegmentData(): Bad switch, eSegmentPosition= " << eSegmentPosition << endl;
      break;
    } //switch(eSegmentPosition)
    break;
    case eVOCBar:
      switch(eSegmentPosition){
      case eFirstSegment:
        strcpy(SegData.BarName  , "VOC");
        strcpy(SegData.ColorName, "Green");
        SegData.StartPercent     = 0;
        SegData.Color            = BECK_GREEN;
        SegData.fStartValue      =   0.0;               //VOC units are mg/m3, which is 3.23 * ppm
        SegData.fEndValue        = 600.0;
        SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
        SegData.XLeft            = VOC_XLEFT + VOC_GREEN_START;
        SegData.YBottom          = VOC_YBOTTOM;
        SegData.Length           = VOC_YELLOW_START - VOC_GREEN_START;
        break;
      case eSecondSegment:
        strcpy(SegData.BarName  , "VOC");
        strcpy(SegData.ColorName, "Yellow");
        SegData.StartPercent     = 33;
        SegData.Color            = BECK_YELLOW;
        SegData.fStartValue      =  600.0;
        SegData.fEndValue        = 2000.0;
        SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
        SegData.XLeft            = VOC_XLEFT + VOC_YELLOW_START;
        SegData.YBottom          = VOC_YBOTTOM;
        SegData.Length           = VOC_RED_START - VOC_YELLOW_START;
        break;
      case eThirdSegment:
        strcpy(SegData.BarName  , "VOC");
        strcpy(SegData.ColorName, "Red");
        SegData.StartPercent     = 66;
        SegData.Color            = BECK_RED;
        SegData.fStartValue      = 2000.0;
        SegData.fEndValue        = 3000.0;
        SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
        SegData.XLeft            = VOC_XLEFT + VOC_RED_START;
        SegData.YBottom          = VOC_YBOTTOM;
        SegData.Length           = BAR_LENGTH - VOC_RED_START;
        break;
      default:
        Serial << LOG0 << "CreateSegmentData(): Bad switch, eSegmentPosition= " << eSegmentPosition << endl;
        break;
      } //switch(eSegmentPosition)
      break;
      case eDegFBar:
        switch(eSegmentPosition){
        case eFirstSegment:
          strcpy(SegData.BarName  , "DEGF");
          strcpy(SegData.ColorName, "Blue");
          SegData.StartPercent     = 0;
          SegData.Color            = BECK_BLUE;
          SegData.fStartValue      =  60.0;
          SegData.fEndValue        =  68.0;
          SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
          SegData.XLeft            = DEGF_XLEFT + DEGF_GREEN_START;
          SegData.YBottom          = DEGF_YBOTTOM;
          SegData.Length           = DEGF_GREEN_START - DEGF_BLUE_START;
          break;
        case eSecondSegment:
          strcpy(SegData.BarName  , "DEGF");
          strcpy(SegData.ColorName, "Green");
          SegData.StartPercent     = 30;
          SegData.Color            = BECK_GREEN;
          SegData.fStartValue      =  68.0;
          SegData.fEndValue        =  80.0;
          SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
          SegData.XLeft            = DEGF_XLEFT + DEGF_GREEN_START;
          SegData.YBottom          = DEGF_YBOTTOM;
          SegData.Length           = DEGF_RED_START - DEGF_GREEN_START;
          break;
        case eThirdSegment:
          strcpy(SegData.BarName  , "DEGF");
          strcpy(SegData.ColorName, "Red");
          SegData.StartPercent     = 80;
          SegData.Color            = BECK_RED;
          SegData.fStartValue      =   80.0;
          SegData.fEndValue        =  100.0;
          SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
          SegData.XLeft            = DEGF_XLEFT + DEGF_RED_START;
          SegData.YBottom          = DEGF_YBOTTOM;
          SegData.Length           = BAR_LENGTH - DEGF_RED_START;
          break;
        default:
          Serial << LOG0 << "CreateSegmentData(): Bad switch, eSegmentPosition= " << eSegmentPosition << endl;
          break;
        } //switch(eSegmentPosition)
        break;
        case eRHBar:
          switch(eSegmentPosition){
          case eFirstSegment:
            strcpy(SegData.BarName  , "RH");
            strcpy(SegData.ColorName, "Green");
            SegData.StartPercent     = 0;
            SegData.Color            = BECK_BLUE;
            SegData.fStartValue      =  60.0;
            SegData.fEndValue        =  68.0;
            SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
            SegData.XLeft            = RH_XLEFT + RH_GREEN_START;
            SegData.YBottom          = RH_YBOTTOM;
            SegData.Length           = RH_YELLOW_START - RH_GREEN_START;
            break;
          case eSecondSegment:
            strcpy(SegData.BarName  , "RH");
            strcpy(SegData.ColorName, "Yellow");
            SegData.StartPercent     = 30;
            SegData.Color            = BECK_GREEN;
            SegData.fStartValue      =  68.0;
            SegData.fEndValue        =  80.0;
            SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
            SegData.XLeft            = RH_XLEFT + RH_GREEN_START;
            SegData.YBottom          = RH_YBOTTOM;
            SegData.Length           = RH_RED_START - RH_GREEN_START;
            break;
          case eThirdSegment:
            strcpy(SegData.BarName  , "RH");
            strcpy(SegData.ColorName, "Red");
            SegData.StartPercent     = 80;
            SegData.Color            = BECK_RED;
            SegData.fStartValue      =   80.0;
            SegData.fEndValue        =  100.0;
            SegData.fRange           = SegData.fEndValue - SegData.fStartValue;
            SegData.XLeft            = RH_XLEFT + RH_RED_START;
            SegData.YBottom          = RH_YBOTTOM;
            SegData.Length           = BAR_LENGTH - RH_RED_START;
            break;
          default:
            Serial << LOG0 << "CreateSegmentData(): Bad switch, eSegmentPosition= " << eSegmentPosition << endl;
            break;
          } //switch(eSegmentPosition)
          break;
  default:
    Serial << LOG0 << "CreateSegmentData(): Bad switch, eBarType= " << eBarType << endl;
    break;
  } //switch(eBarType)

  return SegData;
} //CreateSegmentData


const BarData& CreateBarData(BarType eBarType){
  Serial << endl<< LOG0 << "CreateBarData(): " << szCreateDisplayDataName << ", " << szszCreateDisplayDataDate << endl;
  BarData*          pBarData              = new BarData;
  BarData           &NewBarData           = *pBarData;

  switch(eBarType) {
  case eCO2Bar:
    NewBarData.eBarType= eCO2Bar;
    NewBarData.Orientation            = eHorizontal;
    NewBarData.XLeft                  = CO2_XLEFT;
    NewBarData.YBottom                = CO2_YBOTTOM;
    NewBarData.Thickness              = BAR_THICKNESS;
    NewBarData.Length                 = BAR_LENGTH;
    NewBarData.fStartValue            = CO2_START_VALUE;
    NewBarData.fEndValue              = CO2_END_VALUE;
    NewBarData.fRange                 = NewBarData.fEndValue - NewBarData.fStartValue;
    break;
  case eVOCBar:
    NewBarData.eBarType= eCO2Bar;
    NewBarData.Orientation            = eHorizontal;
    NewBarData.XLeft                  = CO2_XLEFT;
    NewBarData.YBottom                = CO2_YBOTTOM;
    NewBarData.Thickness              = BAR_THICKNESS;
    NewBarData.Length                 = BAR_LENGTH;
    NewBarData.fStartValue            = CO2_START_VALUE;
    NewBarData.fEndValue              = CO2_END_VALUE;
    NewBarData.fRange                 = NewBarData.fEndValue - NewBarData.fStartValue;
    break;
  case eDegFBar:
    NewBarData.eBarType= eCO2Bar;
    NewBarData.Orientation            = eHorizontal;
    NewBarData.XLeft                  = CO2_XLEFT;
    NewBarData.YBottom                = CO2_YBOTTOM;
    NewBarData.Thickness              = BAR_THICKNESS;
    NewBarData.Length                 = BAR_LENGTH;
    NewBarData.fStartValue            = CO2_START_VALUE;
    NewBarData.fEndValue              = CO2_END_VALUE;
    NewBarData.fRange                 = NewBarData.fEndValue - NewBarData.fStartValue;
    break;
  case eRHBar:
    NewBarData.eBarType= eCO2Bar;
    NewBarData.Orientation            = eHorizontal;
    NewBarData.XLeft                  = CO2_XLEFT;
    NewBarData.YBottom                = CO2_YBOTTOM;
    NewBarData.Thickness              = BAR_THICKNESS;
    NewBarData.Length                 = BAR_LENGTH;
    NewBarData.fStartValue            = CO2_START_VALUE;
    NewBarData.fEndValue              = CO2_END_VALUE;
    NewBarData.fRange                 = NewBarData.fEndValue - NewBarData.fStartValue;
    break;
  default:
    Serial << LOG0 << "CreateSegmentData(): Bad switch, eBarType= " << eBarType << endl;
    break;
  } //switch(eBarType)

  SegmentData   FirstSegmentData    = CreateSegmentData(eBarType, eFirstSegment);
  SegmentData   SecondSegmentData   = CreateSegmentData(eBarType, eSecondSegment);
  SegmentData   ThirdSegmentData    = CreateSegmentData(eBarType, eThirdSegment);

  Serial << LOG0 << "CreateBarData(): Save BarSegments in BarSegs array" << endl;
  NewBarData.BarSegs[0]= BarSegment(FirstSegmentData);
  NewBarData.BarSegs[1]= BarSegment(SecondSegmentData);
  NewBarData.BarSegs[2]= BarSegment(ThirdSegmentData);

  return NewBarData;
} //CreateBarData
//Last line.
