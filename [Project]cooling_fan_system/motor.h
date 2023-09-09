#ifndef moter_H_
#define moter_H_

void InitializeTimer3(void);
void motermain(int read);
void motersub(void);
uint8_t stepForward(void);
uint8_t stepBackward(void);
void fan(int read);
void rotator(rot_state, rot_cnt);

#endif /* INCFILE1_H_ */