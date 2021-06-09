
# Projekt PTM

## Pomysł:

Jesteśmy członkami koła pracującymi przy projekcie naukowo-badawczym PWr Diving Crew.

Zajmujemy się budową robota podwodnego klasy AUV – BlueNemo

Aktualnie przygotowując się pod międzynarodowe zawody pracujemy nad nowym pojazdem, dla którego wspólnie przygotowujemy obsługę poniższych czujników:

* AHRS (moduł IMU wraz z  wewnętrznym przetwarzaniem i filtracją)
* ciśnienia Bar02, który min. pozwala na estymację głębokości 

Wykorzystamy również ekran LCD jako panel kontrolny/odczytowy (docelowo mógłby być to ekran OLED), który będzie się znajdował we wnętrzu robota.



____

Projekt skupiać się będzie na obsłudze następujących elementów:

* ekran **Nokia 5110** (84x48 px)
    * protokół komunikacji: **SPI**
    * biblioteka będzie napisana od zera przy pomocy informacji z noty katalogowej
    * [strona produktu](https://botland.com.pl/wyswietlacze-alfanumeryczne-i-graficzne/2650-wyswietlacz-lcd-graficzny-84x48px-nokia-5110-niebieski.html)

* czujnik **Bar02**:
    * [strona produktu](https://bluerobotics.com/store/sensors-sonars-cameras/sensors/bar02-sensor-r1-rp/?fbclid=IwAR1OrarpIVQRmMD04arDhxaLX52zNftKDEgKdB-qMfzaiU9inliZ1wjkOcQ)
    * [Datasheet](https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=MS5837-02BA01&DocType=Data+Sheet&DocLang=English&DocFormat=pdf&PartCntxt=CAT-BLPS0059)
    * jest to czujnik rezystancyjny (wykorzystanie ADC)




## Hardware

Wykorzystana zostanie płytka ewaluacyjna **Nucleo F103RB** jako narzędzie do testowego oprogramowania i debugowania. Docelowo kod zostanie przeportowany na  **"Bluepill"**

## Software

* biblioteki: **HAL**
* IDE: **Cube IDE**
## Autorzy

- [@PanPeople](https://github.com/PanPeople)
- [@Dako99](https://github.com/Dako99)



## Aktualne funkcje:

- biblioteka LCD:

  - odświeżanie bufora
  - rysowanie pixela
  - generowanie napisów
  - wczytywanie tablic z zapełnionym buforem
  - rysowanie bitmap
  
- biblioteka BAR02:

  - dupa
  - robi kawę
  - śmierdzi bo z rąk Damiana <3
## Problems and workarounds:
- programowanie nieoryginalnego **Bluepilla**:

  > [przydatne linki](https://os.mbed.com/users/hudakz/code/STM32F103C8T6_Hello/)
  >
  > Wykorzystano oprogramowanie `STM32 ST-LINK Utility`
  >
  > <img src="assets/image-20210610010410806.png" alt="image-20210610010410806" style="zoom: 50%;" /> 
  >
  > <img src="assets/image-20210610010740086.png" alt="image-20210610010740086" style="zoom:50%;" /> 
## Przyszłe pomysły:
- odczyt przekonwertowanych bitmap z karty SD w celu otworzenia filmu.
  
  
## Opis branchy

#### Nokia screen branch


| Name      | Owner     | Description              |
| :-------- | :------- | :------------------------- |
| `lcd_PanPeople` | `PanPeople` |Base code for Nokia 5110 screen |

#### Bar02 sensor branch


| Name      | Owner     | Description              |
| :-------- | :------- | :------------------------- |
| `bar_Dako99` | `Dako99` | Base code for Bar02 sensor |


## Wykorzystane piny:

<img src="assets/image-20210519102614383.png" alt="image-20210519102614383" style="zoom:80%;" />  

**Wkleić zdjecie STM32F103C8TX** 

<img src="assets/stm32f103c8t6_pinout_voltage01.png" alt="img" style="zoom: 50%;" /> 

### Opis poszczególnych wyprowadzeń:

| Function: | GPIO pin: |          Additional info:          |
| :-------: | :-------: | :--------------------------------: |
|    CS     |  PA6 A0   |          CS line for SPI           |
|    RST    |  PB0 A1   |                                    |
|    DC     |  PB1 A4   |                                    |
| SPI1 MOSI |    PB5    |                                    |
| SPI1 MISO |    PB4    |                                    |
| GreenLed  |   PC13    | led for debuging/status indicating |
| I2C2 SCL  |   PB_10   |                                    |
| I2C2 SDA  |   PB_11   |                                    |
| UART1_TX  |   PA_9    |       uart for comunnication       |
| UART1_RX  |   PA_10   |                                    |
|           |           |                                    |

## Lorem Ipsum

Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Praesent hendrerit, tellus sed condimentum pharetra, justo ipsum interdum felis, at laoreet erat lorem sed nibh. Aenean sodales odio at blandit ultricies. Nullam et suscipit mauris. Morbi et diam felis. Curabitur nec ante id neque imperdiet semper. Donec hendrerit, libero ut fringilla ultrices, est nibh imperdiet arcu, id hendrerit neque felis euismod tellus. Nam faucibus erat id ultrices tempor. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Integer ut cursus est, vel pharetra dolor. Cras sit amet dapibus nunc. Morbi bibendum maximus justo, vitae consequat nibh ultricies nec. Etiam luctus, arcu cursus feugiat viverra, enim mauris ornare orci, et efficitur lacus sem eu lorem. Fusce risus eros, cursus sed arcu ut, tempor tincidunt nunc.