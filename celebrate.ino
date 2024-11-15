#include <MeMCore.h>
MeBuzzer buzzer; // create the buzzer object
void celebrate() {
buzzer.tone(659, 200); 
buzzer.tone(587,200); 
buzzer.tone(369,400); 
buzzer.tone(415,400); 
buzzer.tone(554,200); 
buzzer.tone(493,200); 
buzzer.tone(293,400); 
buzzer.tone(329,400); 
buzzer.tone(493,200); 
buzzer.tone(440,200); 
buzzer.tone(277,400); 
buzzer.tone(329,400); 
buzzer.tone(440,800); 
buzzer.noTone();
}

/*E 200     659  
D 200     587
Gflat 400  369
Aflat 400  415
Dflat 200 554
B 200    493
D 400  293
E 400 329
B 200 493
A 200 440
dflat 400 277
e 400 329
A 800 440
  */
