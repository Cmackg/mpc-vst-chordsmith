/* MIDI out through an ALSA sequencer port. MPC OS ignores VST MIDI output, so the chords leave the
 * plugin here and another track picks the port as its MIDI input (mpc-vst-plugins docs/NOTES.md,
 * "MIDI-output plugins"). libasound is dlopen'd, so the plugin builds without ALSA headers and still
 * loads (with no MIDI out) where the library is missing. Two ports, shared by every instance: 0 "MIDI Out"
 * (the chords) and 1 "Bass Out" (the bass note, when it has its own port: MPC's track filter ignores the
 * channel of a plugin port's notes on OS 3.10.1, so tracks tell chords and bass apart by port). */
#pragma once

int seq_out_acquire(void);          /* 1 if the ports are up; call once per instance */
void seq_out_release(void);
void seq_out_note(int port, int ch, int note, int vel);   /* port 0 or 1; vel 0 = note off; never blocks */
const char *seq_out_status(void);   /* short text for the skin */

/* Tests: capture events instead of sending them (call before the first acquire). */
typedef void (*seq_out_sink_t)(int port, int ch, int note, int vel);
void seq_out_set_sink(seq_out_sink_t sink);
