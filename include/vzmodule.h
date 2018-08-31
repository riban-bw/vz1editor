#ifndef VZMODULE_H
#define VZMODULE_H

//(*Headers(VZModule)
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
//*)
#include "vzvoice.h"

class VZModule: public wxPanel
{
	public:

		VZModule(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~VZModule();

        /** @brief  Set the voice data to which this module belongs
		*   @param  pVoice Pointer to voice data
		*/
		void SetVoice(vzvoice* pVoice);

		/** @brief  Set the module index
		*   @param  nModule Index of this module [0..7]
		*/
		void SetModule(wxByte nModule);

		/** @brief  Update the GUI from the voice data
		*/
		void UpdateGui();


		//(*Declarations(VZModule)
		wxCheckBox* m_pChkEnable;
		wxCheckBox* m_pChkExtPhase;
		wxCheckBox* m_pChkFixedFreq;
		wxCheckBox* m_pChkX16;
		wxCheckBox* m_pEnvRange;
		wxChoice* m_pCmbCurve;
		wxChoice* m_pCmbWaveform;
		wxSlider* m_pSliderAmpSens;
		wxSlider* m_pSliderDetuneFine;
		wxSlider* m_pSliderDetuneOctave;
		wxSlider* m_pSliderEnvDepth;
		wxSlider* m_pSliderVelSensitivity;
		wxStaticBitmap* m_pBmpKeyboard;
		wxStaticText* StaticText3;
		wxStaticText* StaticText4;
		wxStaticText* StaticText5;
		wxStaticText* StaticText6;
		wxStaticText* m_pLblDepth;
		wxStaticText* m_pLblTitle;
		wxStaticText* m_pLblWaveform;
		//*)

	protected:

		//(*Identifiers(VZModule)
		static const long ID_STATICTEXT3;
		static const long ID_CHKENABLE;
		static const long ID_CHKEXTPHASE;
		static const long ID_STATICTEXT4;
		static const long ID_CHOICE3;
		static const long ID_STATICTEXT5;
		static const long ID_SLIDER8;
		static const long ID_STATICTEXT6;
		static const long ID_SLIDER1;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_STATICTEXT8;
		static const long ID_STATICTEXT15;
		static const long ID_SLIDER11;
		static const long ID_CHECKBOX4;
		static const long ID_STATICBITMAP1;
		static const long ID_STATICTEXT7;
		static const long ID_CHOICE4;
		static const long ID_SLIDER9;
		static const long ID_SLIDER10;
		//*)

	private:

	    wxByte m_nModule;
	    vzvoice* m_pVoice;

		//(*Handlers(VZModule)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
