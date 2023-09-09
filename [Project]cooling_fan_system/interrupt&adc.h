#define interrupt&adc_H_
#ifndef interrupt&adc_H_

void INIT_PORT(void);
void INIT_INT0(void);
void INIT_INT1(void);
void INIT_INT2(void);
void ADC_init(unsigned char channel);
int read_ADC(void);

#endif
