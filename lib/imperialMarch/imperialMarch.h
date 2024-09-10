#ifndef _IMPERIAL_MARCH_H
#define _IMPERIAL_MARCH_H

#include <Arduino.h>
#include <pinMap.h>

#define im_c 261
#define im_d 294
#define im_e 329
#define im_f 349
#define im_g 391
#define im_gS 415
#define im_a 440
#define im_aS 455
#define im_b 466
#define im_cH 523
#define im_cSH 554
#define im_dH 587
#define im_dSH 622
#define im_eH 659
#define im_fH 698
#define im_fSH 740
#define im_gH 784
#define im_gSH 830
#define im_aH 880

class ImperialMarch
{
private:
    void beep(int note, int duration);
    void firstSection();
    void secondSection();

public:
    ImperialMarch();
    void starWars();
};

#endif
