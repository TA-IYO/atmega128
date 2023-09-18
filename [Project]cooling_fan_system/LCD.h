#ifndef LCD_H_
#define LCD_H_

unsigned char LCD_rCommand(void);
char LCD_BusyCheck(unsigned char temp);
void LCD_wCommand(char cmd);
void LCD_setcursor(char col, char row);
void LCD_wBCommand(char cmd);
void LCD_Init(void);
void LCD_wData(char dat);
void LCD_wString(char *str);
void timer(int* tim_state);
void LCD_IDLE(void);
void LCD_RUN(void);

#endif /* LCD_H_ */
