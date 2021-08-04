/*
 * STD_marcos.h
 *
 * Created: 6/15/2020 9:56:10 PM
 *  Author: Arafa
 */ 


#ifndef STD_MARCOS_H_
#define STD_MARCOS_H_

#define REGISTER_SIZE 8

#define SET_BIT(reg,bit) reg|=(1<<bit)
#define CLR_BIT(reg,bit) reg&=(~(1<<bit))
#define TOG_BIT(reg,bit) reg^=(1<<bit)
#define READ_BIT(reg,bit) (reg&(1<<bit))>>bit
#define IS_BIT_SET(reg,bit) (reg&(1<<bit))>>bit
#define IS_BIT_CLR(reg,bit)  !((reg&(1<<bit))>>bit)
#define ROR(reg,num) reg=(reg<<(REGISTER_SIZE-num))|(reg>>num)
#define ROL(reg,num) reg=(reg>>(REGISTER_SIZE-num))|(reg<<num)


#endif /* STD_MARCOS_H_ */