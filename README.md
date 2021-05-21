
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

Wykorzystana zostanie płytka ewaluacyjna **Nucleo F103RB** oraz **"Bluepill"**

## Software

* biblioteki: **HAL**
* IDE: **Cube IDE**
## Autorzy

- [@PanPeople](https://github.com/PanPeople)
- [@Dako99](https://github.com/Dako99)



## Aktualne funkcje:

- work in progress

  
## Opis branchy

#### Nokia screen branch


| Name      | Owner     | Description              |
| :-------- | :------- | :------------------------- |
| `screen_dev` | `PanPeople` |Base code for Nokia 5110 screen |

#### Bar02 sensor branch


| Name      | Owner     | Description              |
| :-------- | :------- | :------------------------- |
| `bar_dev` | `Dako99` | Base code for Bar02 sensor |


## Wykorzystane piny:

<img src="assets/image-20210519102614383.png" alt="image-20210519102614383" style="zoom:80%;" /> 

F103C8TX

### Opis poszczególnych wyprowadzeń:

| Function: | GPIO pin: | Additional info: |
| :-------: | :-------: | :--------------: |
|    CS     |    PA6    | CS line for SPI  |
|    RST    |    PB0    |                  |
|    DC     |    PB1    |                  |

