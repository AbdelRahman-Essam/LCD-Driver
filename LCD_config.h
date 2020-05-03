#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* LCD HW Pins */
#define LCD_RS         DIO_PIN10   // Port:B Pin:2
#define LCD_RW         DIO_PIN9    // Port:B Pin:1
#define LCD_EN         DIO_PIN8    // Port:B Pin:0
#define LCD_DATA_PORT  DIO_PORTA // Port:A



/* LCD Data bits mode configuration: 4 or 8 */
#define DATA_BITS_MODE 4

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif


#endif /* LCD_CONFIG_H_ */



