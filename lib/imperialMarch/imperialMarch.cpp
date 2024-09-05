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
  beep(a, 500);
  beep(a, 500);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);

  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  digitalWrite(BUZZER_PIN, HIGH);

  delay(500);
}

void ImperialMarch::secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);
  beep(fSH, 250);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(325);

  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);
  beep(cSH, 175);
  beep(cH, 125);
  beep(b, 125);
  beep(cH, 250);

  digitalWrite(BUZZER_PIN, HIGH);
  delay(350);
}

void ImperialMarch::starWars()
{

  firstSection();

  secondSection();

  beep(f, 250);
  beep(gS, 500);
  beep(f, 350);
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);
  beep(cH, 125);
  beep(eH, 650);

  delay(500);
  secondSection();

  beep(f, 250);
  beep(gS, 500);
  beep(f, 375);
  beep(cH, 125);
  beep(a, 500);
  beep(f, 375);
  beep(cH, 125);
  beep(a, 650);
}
