#include"TFT_eSPI.h"
#include"Seeed_FS.h"
#include"RawImage.h"

TFT_eSPI tft;
float getLabelConfidence(char *label)
{
    float value = 0;
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        ei_impulse_result_classification_t classification = currentClassification[ix];
        if (label == classification.label) {
            value = classification.value;
        }
    }
    return value;
}

void setup(){
    tft.begin();
   if (!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)) {
        while (1);
    }
  tft.setRotation(3);
  drawImage<uint8_t>("rps.bmp", 0,0);

}



void loop(){

  if ((getLabelConfidence("rock") > 0.8)) {
    tft.fillScreen(0xFFFF);
    drawImage<uint8_t>("rock.bmp", 0,0);
  } else {
    if ((getLabelConfidence("paper") > 0.8)) {
      tft.fillScreen(0xFFFF);
      drawImage<uint8_t>("paper.bmp", 0,0);
    } else {
      if ((getLabelConfidence("scissors") > 0.8)) {
        tft.fillScreen(0xFFFF);
        drawImage<uint8_t>("Scirssors.bmp", 0,0);
      } else {
        tft.fillScreen(0xFFFF);
        drawImage<uint8_t>("rps.bmp", 0,0);
      }
    }
  }

}
