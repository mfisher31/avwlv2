#ifndef ADVENV_GUI_H
#define ADVENV_GUI_H

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

using namespace lvtk;
using namespace sigc;
using namespace Gtk;

#include "advenv_gui_scope.hpp"
#include "labeleddial.hpp"

class AdvEnvGUI: public UI<AdvEnvGUI, GtkUI<true>>
{
	public:
		AdvEnvGUI(const std::string& URI);
		void port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer);

	private:
		float m_valueTimeScale;
		float m_valueSustain;
		float m_valueDelay;

		float m_valueAttackTime1;
		float m_valueAttackTime2;
		float m_valueAttackTime3;
		float m_valueAttackTime4;

		float m_valueAttackLevel1;
		float m_valueAttackLevel2;
		float m_valueAttackLevel3;

		float m_valueReleaseTime1;
		float m_valueReleaseTime2;
		float m_valueReleaseTime3;

		float m_valueReleaseLevel1;
		float m_valueReleaseLevel2;

		AdvEnvGUIScope* m_envScope;

	protected:
		LabeledDial* m_scaleTimeScale;
		LabeledDial* m_scaleSustain;
		LabeledDial* m_scaleDelay;

		LabeledDial* m_scaleAttackTime1;
		LabeledDial* m_scaleAttackTime2;
		LabeledDial* m_scaleAttackTime3;
		LabeledDial* m_scaleAttackTime4;

		LabeledDial* m_scaleAttackLevel1;
		LabeledDial* m_scaleAttackLevel2;
		LabeledDial* m_scaleAttackLevel3;

		LabeledDial* m_scaleReleaseTime1;
		LabeledDial* m_scaleReleaseTime2;
		LabeledDial* m_scaleReleaseTime3;

		LabeledDial* m_scaleReleaseLevel1;
		LabeledDial* m_scaleReleaseLevel2;

		float get_timeScale();
		float get_sustain();
		float get_delay();

		float get_attackTime1();
		float get_attackTime2();
		float get_attackTime3();
		float get_attackTime4();

		float get_attackLevel1();
		float get_attackLevel2();
		float get_attackLevel3();

		float get_releaseTime1();
		float get_releaseTime2();
		float get_releaseTime3();

		float get_releaseLevel1();
		float get_releaseLevel2();
};

#endif
