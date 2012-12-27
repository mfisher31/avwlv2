#include <gtkmm-2.4/gtkmm.h>

#include <lvtk-1/lvtk/plugin.hpp>
#include <lvtk-1/lvtk/gtkui.hpp>

#include "vco2_gui.hpp"
#include "vco2.hpp"

Vco2GUI::Vco2GUI(const char* plugin_uri)
{
	EventBox *p_background = manage(new EventBox());
	Gdk::Color* color = new  Gdk::Color();
	color->set_rgb(7710, 8738, 9252);
	p_background->modify_bg(Gtk::STATE_NORMAL, *color);



	VBox *p_mainWidget = manage(new VBox(false, 5));



	Label *p_labeWaveForm = manage (new Label("Wave Form"));
	p_mainWidget->pack_start(*p_labeWaveForm);

	m_comboWaveForm = manage (new ComboBoxText());
	m_comboWaveForm->append_text("Sine");
	m_comboWaveForm->append_text("Triangle");
	m_comboWaveForm->append_text("Sawtooth");
	m_comboWaveForm->append_text("Rectangle");
	m_comboWaveForm->append_text("Aux Saw 1");
	m_comboWaveForm->append_text("Aux Saw 2");
	m_comboWaveForm->append_text("Aux Saw 3");

	slot<void> p_slotWaveForm = compose(bind<0> (mem_fun(*this, &Vco2GUI::write_control), p_waveForm), mem_fun(*m_comboWaveForm, &ComboBoxText::get_active_row_number));
	m_comboWaveForm->signal_changed().connect(p_slotWaveForm);
	p_mainWidget->pack_start(*m_comboWaveForm);



	Frame *p_freqFrame = manage(new Frame("Frequency"));
	//p_gainFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_freqBox = manage(new HBox(true));

	slot<void> p_slotOctave = compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_octave), mem_fun(*this,  &Vco2GUI::get_octave));
	m_scaleOctave = new LabeledDial("Octave", p_slotOctave, p_octave, 0, 6, false, 1, 0);
	p_freqBox->pack_start(*m_scaleOctave);

	slot<void> p_slotTune = compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_tune), mem_fun(*this,  &Vco2GUI::get_tune));
	m_scaleTune = new LabeledDial("Tune", p_slotTune, p_tune, 0, 1, true, 0.0001, 4);
	p_freqBox->pack_start(*m_scaleTune);

	slot<void> p_slotHarmonic = compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_harmonic), mem_fun(*this,  &Vco2GUI::get_harmonic));
	m_scaleHarmonic = new LabeledDial("Harmonic", p_slotHarmonic, p_harmonic, 1, 16, false, 1, 0);
	p_freqBox->pack_start(*m_scaleHarmonic);

	slot<void> p_slotSubharmonic = compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_subharmonic), mem_fun(*this,  &Vco2GUI::get_subharmonic));
	m_scaleSubHarmonic = new LabeledDial("Subharmonic", p_slotSubharmonic, p_subharmonic, 1, 16, false, 1, 0);
	p_freqBox->pack_start(*m_scaleSubHarmonic);

	p_freqFrame->add(*p_freqBox);
	p_mainWidget->pack_start(*p_freqFrame);



	Frame *p_pwpFrame = manage(new Frame("Pulse Width / Phase"));
	//p_gainFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_pwpBox = manage(new HBox(true));

	slot<void> p_slotPw0 = compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_pw0), mem_fun(*this,  &Vco2GUI::get_pw));
	m_scalePW = new LabeledDial("PW", p_slotPw0, p_pw0, 0.1, 0.9, false, 0.001, 3);
	p_pwpBox->pack_start(*m_scalePW);

	slot<void> p_slotPwGain = compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_pwGain), mem_fun(*this,  &Vco2GUI::get_pwGain));
	m_scalePWGain = new LabeledDial("PW Gain", p_slotPwGain, p_pwGain, 0, 1, true, 0.0001, 4);
	p_pwpBox->pack_start(*m_scalePWGain);

	slot<void> p_slotPhi0 = compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_phi0), mem_fun(*this,  &Vco2GUI::get_phi0));
	m_scalePhi0 = new LabeledDial("Phi0", p_slotPhi0, p_phi0, 0, 6.28, true, 0.0001, 4);
	p_pwpBox->pack_start(*m_scalePhi0);

	p_pwpFrame->add(*p_pwpBox);
	p_mainWidget->pack_start(*p_pwpFrame);



	Frame *p_modulationFrame = manage(new Frame("Modulation"));
	//p_gainFrame->set_shadow_type(Gtk::SHADOW_NONE);
	HBox *p_modulationBox = manage(new HBox(true));

	slot<void> p_slotExpFMGain = compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_expFMGain), mem_fun(*this,  &Vco2GUI::get_expFMGain));
	m_scaleExpFMGain = new LabeledDial("Exp FM Gain", p_slotExpFMGain, p_expFMGain, 0, 10, true, 0.001, 3);
	p_modulationBox->pack_start(*m_scaleExpFMGain);

	slot<void> p_slotLinFMGain = compose(bind<0>(mem_fun(*this, &Vco2GUI::write_control), p_linFMGain), mem_fun(*this,  &Vco2GUI::get_linFMGain));
	m_scaleLinFMGain = new LabeledDial("Lin FM Gain", p_slotLinFMGain, p_linFMGain, 0, 10, true, 0.001, 3);
	p_modulationBox->pack_start(*m_scaleLinFMGain);

	p_modulationFrame->add(*p_modulationBox);
	p_mainWidget->pack_start(*p_modulationFrame);



	p_mainWidget->set_size_request(200, 320);

	p_background->add(*p_mainWidget);
	add(*p_background);

	Gtk::manage(p_mainWidget);
}

float Vco2GUI::get_octave() 		{ return m_scaleOctave->get_value(); }
float Vco2GUI::get_tune() 			{ return m_scaleTune->get_value(); }
float Vco2GUI::get_harmonic() 		{ return m_scaleHarmonic->get_value(); }
float Vco2GUI::get_subharmonic() 	{ return m_scaleSubHarmonic->get_value(); }
float Vco2GUI::get_pw() 			{ return m_scalePW->get_value(); }
float Vco2GUI::get_pwGain() 		{ return m_scalePWGain->get_value(); }
float Vco2GUI::get_phi0() 			{ return m_scalePhi0->get_value(); }
float Vco2GUI::get_expFMGain() 		{ return m_scaleExpFMGain->get_value(); }
float Vco2GUI::get_linFMGain()		{ return m_scaleLinFMGain->get_value(); }

void Vco2GUI::port_event(uint32_t port, uint32_t buffer_size, uint32_t format, const void* buffer)
{
	if (port == p_waveForm)
	{
		int p_waveFormValue = (int) (*static_cast<const float*> (buffer));
		if (p_waveFormValue >= 0 && p_waveFormValue <= 6)
		{
			m_comboWaveForm->set_active((int) p_waveFormValue);
		}
	}
	else if (port == p_octave)
	{
		m_scaleOctave->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_tune)
	{
		m_scaleTune->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_harmonic)
	{
		m_scaleHarmonic->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_subharmonic)
	{
		m_scaleSubHarmonic->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_pw0)
	{
		m_scalePW->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_pwGain)
	{
		m_scalePWGain->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_phi0)
	{
		m_scalePhi0->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_expFMGain)
	{
		m_scaleExpFMGain->set_value(*static_cast<const float*> (buffer));
	}
	else if (port == p_linFMGain)
	{
		m_scaleLinFMGain->set_value(*static_cast<const float*> (buffer));
	}
}

static int _ = Vco2GUI::register_class("http://avwlv2.sourceforge.net/plugins/avw/vco2/gui");
