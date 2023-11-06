#include "hal_st/instantiations/NucleoUi.hpp"
#include "hal_st/instantiations/StmEventInfrastructure.hpp"
#include "hal_st/stm32fxxx/DefaultClockNucleoF767ZI.hpp"
#include "services/util/DebugLed.hpp"

unsigned int hse_value = 8000000;

int main() {

  HAL_Init();

  // Configure your clock here
  ConfigureDefaultClockNucleo767ZI();

  static main_::StmEventInfrastructure eventInfrastructure;
  static main_::NUCLEO ui;
  // static services::DebugLed debugLed(ui.ledBlue);
  static services::DebugLed debugLed(ui.ledRed);
  // static services::DebugLed debugLed(ui.ledGreen);

  // static hal::OutputPin pinRed(ui.ledRed);
  // static hal::OutputPin pinGreen(ui.ledGreen);
  // static hal::InputPin button(ui.buttonOne);

  // while (true)
  // {
  //     // if (button.Status() == true) {
  //         pinRed.Set(true);
  //     // }
  //     // pinRed.Set(true);
  //     // pinGreen.Set(false);
  //     // sleep(5);
  //     // pinRed.Set(false);
  //     // pinGreen.Set(true);
  //     // sleep(5);
  // }

  eventInfrastructure.Run();
  __builtin_unreachable();
}
