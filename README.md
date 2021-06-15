



# PTM project 2020/2021

## [Idea:](https://i.pinimg.com/originals/77/ce/37/77ce3786d5a035243790f7168da7b3c5.jpg)

We are the members of the scientific association working on the [PWr Diving Crew](http://robocik.pwr.edu.pl/) research project.

We are involved in building an AUV class underwater robot - BlueNemo

Currently, preparing for international competitions, we are working on a new vehicle, for which we are preparing support for the following sensors:

* AHRS (IMU module with internal processing and filtration)
* Bar02 pressure, which among others allows for depth estimation. 

We will also use LCD screen as a control/reading panel (eventually it could be OLED screen), which will be located inside the robot.

____

The project will focus on supporting the following things:

* screen **Nokia 5110** (84x48 px).
  * communication protocol: **SPI**.
  * the library will be written from scratch using information from the catalog note
  * [product page](https://botland.com.pl/wyswietlacze-alfanumeryczne-i-graficzne/2650-wyswietlacz-lcd-graficzny-84x48px-nokia-5110-niebieski.html)
  * [documentation](https://botland.com.pl/index.php?controller=attachment&id_attachment=552) 
  
* sensor **Bar02**:
  * [product page](https://bluerobotics.com/store/sensors-sonars-cameras/sensors/bar02-sensor-r1-rp/?fbclid=IwAR1OrarpIVQRmMD04arDhxaLX52zNftKDEgKdB-qMfzaiU9inliZ1wjkOcQ)
  * [Datasheet](https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=MS5837-02BA01&DocType=Data+Sheet&DocLang=English&DocFormat=pdf&PartCntxt=CAT-BLPS0059)
  * it is a resistive sensor (ADC usage)




## Hardware:

The **Nucleo F103RB** evaluation board will be used as a test software and debugging tool.

Ultimately the code will be ported to **"Bluepill "**.

## Software:

* libraries: **HAL**
* IDE: **Cube IDE**
## Authors/developers:

- [@PanPeople](https://github.com/PanPeople)
- [@Dako99](https://github.com/Dako99)



## Aktualne funkcje:

- LCD library:
  - buffer refresh
  - drawing a pixel
  - caption generation
  - loading tables with full buffer
  - drawing of bitmaps
- BAR02 library:

  - ass
  - makes coffee
  - stinks because of Damian's hands? <3
## Problems and workarounds:
- flashing of fake **Bluepill**:

  > [useful links](https://os.mbed.com/users/hudakz/code/STM32F103C8T6_Hello/)
  >
  > The software used was `STM32 ST-LINK Utility`.
  >
  > <img src="assets/image-20210610010410806.png" alt="image-20210610010410806" style="zoom: 50%;" /> 
  >
  > <img src="assets/image-20210610010740086.png" alt="image-20210610010740086" style="zoom:50%;" /> 
  
- jak chińczyk zjebał pcb:

  > Dako69 historia prawdziwa
## Future ideas:

- Reading converted bitmaps from SD (with another SPI interface) card to open movie.
  
  > ![yo235](assets/yo235.bmp)  
  >
  > "Bad apple" 48x84 pixels resolution
## Branch description

#### Nokia screen branch


| Name      | Owner     | Description              |
| :-------- | :------- | :------------------------- |
| `lcd_PanPeople` | `PanPeople` |Base code for Nokia 5110 screen |

All required library files are in ` lcd_5110_library `folder. 

`lcd_5110.h` is a header file which consist few essential defines:

>Resolution of used display
>
>```C
>#define LCD_X 84
>#define LCD_Y 48
>```
>
>____
>
>Macro for passing **command** or **data** to the display
>
>```C
>#define LCD_C GPIO_PIN_RESET//<- command
>#define LCD_D GPIO_PIN_SET// <- data
>```
>
>Declaration of used pins
>
>```C
>#define LCD_DC_PIN GPIO_PIN_1
>#define LCD_CE_PIN GPIO_PIN_6
>#define LCD_RST_PIN GPIO_PIN_0
>
>#define LCD_DC_PORT GPIOB
>#define LCD_CE_PORT GPIOA
>#define LCD_RST_PORT GPIOB
>```
>
>- **RST** - A line that resets the display registers. Before operating the display, generate a zero state on this line for at least 100ns. During normal display operation, there should be a continuous high state on this line.
>- **CE** - is the CS line of the SPI interface, the name comes from *Chip Enable*
>- **DC** - line determining whether we send data (high state) or commands for the display (low state)

`lcd_5110.c` main library file with:

> Spark fun font  table which contains the hex values that represent pixels for a font that is 5 pixels wide and 8 pixels high (Beerware license)
>
> ```c
> const uint8_t font_ASCII[][5] = {
>   {0x00, 0x00, 0x00, 0x00, 0x00} // 20
>  ,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
>  ,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
>  ,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
>  ,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
> //... more data in code ...
> };
> ```
>
> ____
>
> PWr Diving Crew bitmap logo
>
> ```C
> const uint8_t logo []=
> {
> 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
> //... more data in code ...
> };
> ```
>
> ____
>
> Function for initializing communication with the screen and additional command for setting contrast
>
> parameters:
>
> > `SPI_HandleTypeDef *spi` - handler for SPI structure (can be found in spi.c)
>
> ```C
> void LCD_Initialize(SPI_HandleTypeDef *spi);
> ```
>
> ____
>
> Function for sending a command, all commands code (binary values) are available in documentation
>
> parameters:
>
> > `SPI_HandleTypeDef *spi` - handler for SPI structure (can be found in spi.c)
> >
> > `uint8_t cmd`- command as hexadecimal value
>
> ```C
> void LCD_Command(SPI_HandleTypeDef* spi,uint8_t cmd);
> ```
>
> ____
>
> Function for sending data, in this library it is used for pushing whole data buffer
>
> parameters:
>
> > `SPI_HandleTypeDef *spi` - handler for SPI structure (can be found in spi.c)
> >
> > `uint8_t cmd`- used for sending whole buffer of data
>
> ```C
> void LCD_Data(SPI_HandleTypeDef *spi,uint8_t* cmd);
> ```
>
> ____
>
> Kinda useless function but it is used for sending just one byte of data,(may be used function in *for* loop for example to fill whole screen or make it blank)
>
> parameters:
>
> > `SPI_HandleTypeDef *spi` - handler for SPI structure (can be found in spi.c)
> >
> > `uint8_t cmd`- used for sending whole buffer of data
>
> ```C
> void LCD_Data_Byte(SPI_HandleTypeDef *spi,uint8_t* cmd);
> ```
>
> ____
>
> Function is used to clear whole screen, NOT buffer, can be handy in flashing animations
>
> parameters:
>
> > `SPI_HandleTypeDef *spi` - handler for SPI structure (can be found in spi.c)
>
> ```C
> void LCD_Clear(SPI_HandleTypeDef *spi);
> ```
>
> ____
>
> Just filling up whole screen
>
> buffer stays untouched.
>
> parameters:
>
> > `SPI_HandleTypeDef *spi` - handler for SPI structure (can be found in spi.c)
>
> ```C
> void LCD_Fill(SPI_HandleTypeDef *spi)
> ```


#### Bar02 sensor branch


| Name      | Owner     | Description              |
| :-------- | :------- | :------------------------- |
| `bar_Dako99` | `Dako99` | Base code for communication with Bar02 sensor |





**Dako69 tutaj dawaj opis jak ja!!!!!!**











## Used pins:

<img src="assets/image-20210615182721677.png" alt="image-20210615182721677" style="zoom:80%;" />   

<img src="assets/stm32f103c8t6_pinout_voltage01.png" alt="img" style="zoom: 50%;" /> 

### Table of functions with descriptions of particular pins:

|  Function:  | GPIO pin: |          Additional info:           |
| :---------: | :-------: | :---------------------------------: |
|     CS      |  PA6 A0   |           CS line for SPI           |
|     RST     |  PB0 A1   |         RST line for screen         |
|     DC      |  PB1 A4   |         DC line for screen          |
|  SPI1 MOSI  |    PB5    |                  -                  |
|  SPI1 MISO  |    PB4    |                  -                  |
| GPIO_Output |   PC13    | led for debugging/status indicating |
|  I2C2 SCL   |   PB_10   |                                     |
|  I2C2 SDA   |   PB_11   |                                     |
|  UART1_TX   |   PA_9    |                  -                  |
|  UART1_RX   |   PA_10   |                  -                  |
|             |           |                                     |

## Installation:

In the repository there are two folders called `F103C8TX` and `F103RB`, just download one of the folder and lunch the project from **CubeIDIE**, not tested with **Keil ** Virtual uC.

For more info search: *opening project in Cube IDE* 

For more info, just ask a question via email or Github.



## Example usage:

jeszcze bedzie 

## Licence

```
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Mikołaj Czerniak and Damian Kociołek wrote this files. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy us a beer in return Mikołaj Czerniak and Damian Kociołek
 * ----------------------------------------------------------------------------
```

## Lorem Ipsum

Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Praesent hendrerit, tellus sed condimentum **placed** pharetra, justo ipsum interdum felis, at laoreet erat lorem sed nibh. Aenean sodales odio at blandit ultricies. Nullam et suscipit mauris. Morbi et diam felis. Curabitur nec ante id neque imperdiet semper. Donec **just** hendrerit, libero ut fringilla ultrices, est nibh imperdiet arcu, id hendrerit neque felis euismod tellus. Nam faucibus erat id ultrices tempor. Orci varius natoque penatibus **for** et magnis dis parturient montes, **fun** nascetur ridiculus mus. Integer ut cursus est, vel pharetra dolor. Cras sit amet dapibus nunc. Morbi bibendum maximus justo, vitae consequat nibh ultricies nec. Etiam luctus, arcu cursus feugiat viverra, enim mauris ornare orci, et efficitur lacus sem eu lorem. Fusce risus eros, cursus sed arcu ut, tempor tincidunt nunc.

