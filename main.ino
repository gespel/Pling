#include <driver/i2s.h>
#include "GouodModulesLib/instruments.h"
#include "GouodModulesLib/synths.h"

const int BUFSIZE = 2048;

float phase = 0;
uint16_t audioBuffer[BUFSIZE];

void setup_i2n(int sampleRate, int bitDepth, int i2sChannel) {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = sampleRate,
    .bits_per_sample = (i2s_bits_per_sample_t)bitDepth,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 6,
    .dma_buf_len = 1024,
    .use_apll = true,
    .tx_desc_auto_clear = true,
  };
  
  i2s_pin_config_t pin_config = {
    .bck_io_num = 26, // BCLK-Pin
    .ws_io_num = 25, // LRCLK-Pin
    .data_out_num = 18, // Daten-Ausgangspins
    .data_in_num = I2S_PIN_NO_CHANGE, // Daten-Eingangspins (kein Eingang)
  };

  i2s_driver_install((i2s_port_t)i2sChannel, &i2s_config, 0, NULL);
  i2s_set_pin((i2s_port_t)i2sChannel, &pin_config);
}

void setup() {
  Serial.begin(115200);
  pinMode(16, INPUT);
  pinMode(34, INPUT);
}

void loop() {
  double sampleRate = 48000;
  Pling pling(sampleRate);
  SawtoothSynth ss(220.f, sampleRate);
  setup_i2n(sampleRate, 16, 0);
  while(1) {
    int16_t sample;
    size_t bytes_written;
    int x = 0;
    if(digitalRead(16) == HIGH) {
      pling.trigger();
      Serial.println("Button pressed!");
    }

    for (int i = 0; i < BUFSIZE; i++) {
      double sample = pling.getSample();

      audioBuffer[i] = sample;

      
        
    }
    
    i2s_write((i2s_port_t)0, audioBuffer, sizeof(audioBuffer), &bytes_written, portMAX_DELAY);

  }
  //int a = digitalRead(16);
  //int b = analogRead(34);
  //Serial.println(a);
  //Serial.println(b);
}
