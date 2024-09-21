#include <music.h>

Music::Music() {}

void Music::playTone(int note, int duration)
{
  digitalWrite(BUZZER_PIN, HIGH);
  tone(BUZZER_PIN, note, duration);
  delay(duration);
  noTone(BUZZER_PIN);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50);
}

void Music::starWars()
{
  startWarsPartA();
  startWarsPartB();
  /*
  playTone(SW_f, 250);
  playTone(SW_gS, 500);
  playTone(SW_f, 350);
  playTone(SW_a, 125);
  playTone(SW_cH, 500);
  playTone(SW_a, 375);
  playTone(SW_cH, 125);
  playTone(SW_eH, 650);

  delay(500);

  startWarsPartB();

  playTone(SW_f, 250);
  playTone(SW_gS, 500);
  playTone(SW_f, 375);
  playTone(SW_cH, 125);
  playTone(SW_a, 500);
  playTone(SW_f, 375);
  playTone(SW_cH, 125);
  playTone(SW_a, 650);

  delay(650);
  */
}

void Music::goodMorning()
{

  playTone(GM_NOTE_C4, QUARTER_NOTE);
  playTone(GM_NOTE_E4, QUARTER_NOTE);
  playTone(GM_NOTE_G4, QUARTER_NOTE);
  playTone(GM_NOTE_E4, HALF_NOTE);
  playTone(GM_NOTE_C4, QUARTER_NOTE);
  playTone(GM_NOTE_E4, QUARTER_NOTE);
  playTone(GM_NOTE_G4, QUARTER_NOTE);
  playTone(GM_NOTE_E4, HALF_NOTE);

  playTone(GM_NOTE_G4, QUARTER_NOTE);
  playTone(GM_NOTE_A4, QUARTER_NOTE);
  playTone(GM_NOTE_C5, QUARTER_NOTE);
  playTone(GM_NOTE_A4, HALF_NOTE);
  playTone(GM_NOTE_G4, QUARTER_NOTE);
  playTone(GM_NOTE_A4, QUARTER_NOTE);
  playTone(GM_NOTE_C5, QUARTER_NOTE);
  playTone(GM_NOTE_A4, HALF_NOTE);

  playTone(GM_NOTE_C5, QUARTER_NOTE);
  playTone(GM_NOTE_E5, QUARTER_NOTE);
  playTone(GM_NOTE_G5, QUARTER_NOTE);
  playTone(GM_NOTE_E5, HALF_NOTE);
  playTone(GM_NOTE_C5, QUARTER_NOTE);
  playTone(GM_NOTE_E5, QUARTER_NOTE);
  playTone(GM_NOTE_G5, QUARTER_NOTE);
  playTone(GM_NOTE_E5, HALF_NOTE);
}

void Music::startWarsPartA()
{
  playTone(SW_a, 500);
  playTone(SW_a, 500);
  playTone(SW_a, 500);
  playTone(SW_f, 350);
  playTone(SW_cH, 150);
  playTone(SW_a, 500);
  playTone(SW_f, 350);
  playTone(SW_cH, 150);
  playTone(SW_a, 650);

  delay(500);

  playTone(SW_eH, 500);
  playTone(SW_eH, 500);
  playTone(SW_eH, 500);
  playTone(SW_fH, 350);
  playTone(SW_cH, 150);
  playTone(SW_gS, 500);
  playTone(SW_f, 350);
  playTone(SW_cH, 150);
  playTone(SW_a, 650);

  delay(500);
}

void Music::startWarsPartB()
{
  playTone(SW_aH, 500);
  playTone(SW_a, 300);
  playTone(SW_a, 150);
  playTone(SW_aH, 500);
  playTone(SW_gSH, 325);
  playTone(SW_gH, 175);
  playTone(SW_fSH, 125);
  playTone(SW_fH, 125);
  playTone(SW_fSH, 250);

  delay(325);

  playTone(SW_aS, 250);
  playTone(SW_dSH, 500);
  playTone(SW_dH, 325);
  playTone(SW_cSH, 175);
  playTone(SW_cH, 125);
  playTone(SW_b, 125);
  playTone(SW_cH, 250);

  delay(350);
}