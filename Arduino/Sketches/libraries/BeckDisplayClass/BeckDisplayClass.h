// BeckDisplayClass.h, 3/29/21a

#include <BeckBiotaLib.h>

class Display {
public:
	Display						  	(int wType, ProjectType eDisplayProjectType);
	virtual void  SetupDisplay		();
	virtual void  ClearDisplay		();
	virtual void  UpdateDisplay		();
	virtual void  ClearZeros		();
};  //Display


class TFT_eSPI : public Display{
	void  SetupDisplay            (ProjectType eDisplayProjectType);
	void  ClearDisplay            ();
	void  UpdateDisplay           ();
	void  ClearZeros              ();
};

void TFT_eSPI::SetupDisplay(ProjectType eDisplayProjectType){
	return;
}


void TFT_eSPI::ClearDisplay(){
	return;
}


void TFT_eSPI::UpdateDisplay(){
	return;
}


void TFT_eSPI::ClearZeros(){
	return;
}
