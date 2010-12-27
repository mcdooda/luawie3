#ifndef DEVICES_H
 #define DEVICES_H

#include "wiiuse_v0.12/src/wiiuse.h"

void devices_connect    (int num_wiimotes);
void devices_disconnect ();
void devices_poll       ();

int current_wiimote_id (int current);

int num_devices (int num);

struct wiimote_t*** get_devices ();

struct wiimote_t*       get_wiimote ();
struct nunchuk_t*       get_nunchuk ();
struct classic_ctrl_t*  get_classic ();
struct guitar_hero_3_t* get_guitar  ();

#endif


