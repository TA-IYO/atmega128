#ifndef motor_H_
#define motor_H_

void InitializeTimer3(void);
void motermain(int read);
void motersub(void);
uint8_t stepForward(void);
uint8_t stepBackward(void);
void fan(int read);
void rotator(int rot_state, int rot_cnt);

#endif /* INCFILE1_H_ */
