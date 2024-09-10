#include <imperialMarch.h>

int counter = 0;

ImperialMarch::ImperialMarch() {}

void ImperialMarch::beep(int note, int duration)
{
  digitalWrite(BUZZER_PIN, HIGH);
  tone(BUZZER_PIN, note, duration);
  delay(duration);
  noTone(BUZZER_PIN);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50);
}

void ImperialMarch::firstSection()
{
  beep(im_a, 500);
  beep(im_a, 500);
  beep(im_a, 500);
  beep(im_f, 350);
  beep(im_cH, 150);
  beep(im_a, 500);
  beep(im_f, 350);
  beep(im_cH, 150);
  beep(im_a, 650);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);

  beep(im_eH, 500);
  beep(im_eH, 500);
  beep(im_eH, 500);
  beep(im_fH, 350);
  beep(im_cH, 150);
  beep(im_gS, 500);
  beep(im_f, 350);
  beep(im_cH, 150);
  beep(im_a, 650);

  digitalWrite(BUZZER_PIN, HIGH);

  delay(500);
}

void ImperialMarch::secondSection()
{
  beep(im_aH, 500);
  beep(im_a, 300);
  beep(im_a, 150);
  beep(im_aH, 500);
  beep(im_gSH, 325);
  beep(im_gH, 175);
  beep(im_fSH, 125);
  beep(im_fH, 125);
  beep(im_fSH, 250);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(325);

  beep(im_aS, 250);
  beep(im_dSH, 500);
  beep(im_dH, 325);
  beep(im_cSH, 175);
  beep(im_cH, 125);
  beep(im_b, 125);
  beep(im_cH, 250);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(350);
}

void ImperialMarch::starWars()
{

  firstSection();

  secondSection();

  beep(im_f, 250);
  beep(im_gS, 500);
  beep(im_f, 350);
  beep(im_a, 125);
  beep(im_cH, 500);
  beep(im_a, 375);
  beep(im_cH, 125);
  beep(im_eH, 650);

  delay(500);
  secondSection();

  beep(im_f, 250);
  beep(im_gS, 500);
  beep(im_f, 375);
  beep(im_cH, 125);
  beep(im_a, 500);
  beep(im_f, 375);
  beep(im_cH, 125);
  beep(im_a, 650);
}
